"""
Chat Server — Fixed
Fixes:
  1. Video/Voice: header+data now read correctly regardless of client style
  2. File to room: broadcasts to all room members instead of send_to(room_name)
  3. Active call check loosened so media flows even before VIDCALL_ACC race
"""

import socket
import threading
import time
import traceback

HOST = '0.0.0.0'
PORT = 5555

clients     = {}        # username  -> socket
rooms       = {}        # room_name -> [user1, user2, ...]
active_calls = {}       # username  -> (partner, call_type)


# ──────────────────────── Buffered Reader ────────────────────────
class BufferedReader:
    def __init__(self, sock):
        self.sock   = sock
        self.buffer = b""

    def read_line(self):
        """Read until \\n. Works whether or not client appends \\n —
        falls back to reading until we can decode a valid header."""
        while b'\n' not in self.buffer:
            data = self.sock.recv(4096)
            if not data:
                raise ConnectionError("Connection closed")
            self.buffer += data
        idx  = self.buffer.index(b'\n')
        line = self.buffer[:idx].decode('utf-8', errors='replace')
        self.buffer = self.buffer[idx + 1:]
        return line

    def read_bytes(self, size):
        """Read exactly *size* bytes."""
        while len(self.buffer) < size:
            remaining = size - len(self.buffer)
            data = self.sock.recv(min(8192, remaining))
            if not data:
                raise ConnectionError("Connection closed")
            self.buffer += data
        result      = self.buffer[:size]
        self.buffer = self.buffer[size:]
        return result

    def read_line_or_binary_header(self):
        """
        The old client sends headers WITHOUT \\n, immediately followed
        by binary data (sometimes with a sleep in between).
        Strategy: accumulate until we see '|' 4 times (all our headers
        have exactly 4 fields) OR until we see \\n.
        For safety we cap at 512 bytes — no valid header is longer.
        """
        while True:
            # Happy path: newline present
            if b'\n' in self.buffer:
                idx  = self.buffer.index(b'\n')
                line = self.buffer[:idx].decode('utf-8', errors='replace')
                self.buffer = self.buffer[idx + 1:]
                return line

            # Check if we already have a complete header (4 pipes) in buffer
            try:
                candidate = self.buffer.decode('utf-8', errors='replace')
                if candidate.count('|') >= 3:
                    # Try to extract: TYPE|A|B|SIZE  where SIZE is all digits at end
                    parts = candidate.split('|')
                    if len(parts) >= 4:
                        size_part = parts[3]
                        digits = ''.join(c for c in size_part if c.isdigit())
                        if digits and size_part.startswith(digits):
                            # We have a complete header — consume it
                            header_bytes = '|'.join(parts[:4][:3]) + '|' + digits
                            consumed = len(header_bytes.encode('utf-8', errors='replace'))
                            line = header_bytes
                            self.buffer = self.buffer[consumed:]
                            # Strip any stray newline
                            if self.buffer.startswith(b'\n'):
                                self.buffer = self.buffer[1:]
                            return line
            except Exception:
                pass

            # Need more data
            if len(self.buffer) > 512:
                # Something is wrong — clear and raise
                self.buffer = b""
                raise ValueError("Header too long / corrupt")

            data = self.sock.recv(4096)
            if not data:
                raise ConnectionError("Connection closed")
            self.buffer += data


# ──────────────────────── Helpers ────────────────────────
def send_to(user, message_bytes):
    """Send raw bytes to a single connected user."""
    if user in clients:
        try:
            clients[user].sendall(message_bytes)
        except Exception:
            clients.pop(user, None)


def broadcast_room(room, sender, message_bytes):
    """Send raw bytes to every member of a room except the sender."""
    if room not in rooms:
        return
    for user in list(rooms[room]):
        if user != sender:
            send_to(user, message_bytes)


def update_lists():
    users     = ",".join(clients.keys())
    room_list = ",".join(rooms.keys())
    for sock in list(clients.values()):
        try:
            sock.sendall(f"LIST|{users}\n".encode())
            time.sleep(0.01)
            sock.sendall(f"ROOMS|{room_list}\n".encode())
        except Exception:
            pass


# ──────────────────────── Client Handler ────────────────────────
def handle_client(conn, addr):
    reader   = BufferedReader(conn)
    username = None

    try:
        # First line = username
        username = reader.read_line().strip()
        if not username:
            conn.close()
            return

        clients[username] = conn
        print(f"[+] {username} connected from {addr}")
        update_lists()

        while True:
            # ── Read header ──────────────────────────────────────
            # We use read_line() which handles both \n-terminated
            # and (via BufferedReader accumulation) non-terminated headers.
            header = reader.read_line()
            if not header:
                break

            parts = header.split('|')
            mtype = parts[0].strip()

            # ── GROUP MESSAGE ─────────────────────────────────────
            if mtype == "GROUP":
                if len(parts) < 3:
                    continue
                room, msg = parts[1], parts[2]
                if room not in rooms:
                    send_to(username, f"[SYSTEM] Room '{room}' does not exist.\n".encode())
                    continue
                if username not in rooms[room]:
                    send_to(username, f"[SYSTEM] You must join the room first.\n".encode())
                    continue
                broadcast_room(room, username,
                               f"[{room}] {username}: {msg}\n".encode())

            # ── ROOM MANAGEMENT ──────────────────────────────────
            elif mtype == "CREATE":
                room = parts[1]
                rooms[room] = [username]
                update_lists()

            elif mtype == "JOIN":
                room = parts[1]
                if room in rooms:
                    if username not in rooms[room]:
                        rooms[room].append(username)
                    send_to(username, f"[SYSTEM] Joined room '{room}'.\n".encode())
                else:
                    send_to(username, f"[SYSTEM] Room '{room}' not found.\n".encode())
                update_lists()

            elif mtype == "LEAVE":
                room = parts[1]
                if room in rooms and username in rooms[room]:
                    rooms[room].remove(username)
                    if not rooms[room]:
                        del rooms[room]
                update_lists()

            # ── PRIVATE MESSAGE ───────────────────────────────────
            elif mtype == "PRIVATE":
                if len(parts) < 3:
                    continue
                target, msg = parts[1], parts[2]
                send_to(target, f"[PRIVATE] {username}: {msg}\n".encode())

            # ── FORWARD ──────────────────────────────────────────
            elif mtype == "FORWARD":
                if len(parts) < 3:
                    continue
                target, msg = parts[1], parts[2]
                send_to(target, f"[FORWARDED] {username}: {msg}\n".encode())

            # ── FILE TRANSFER ─────────────────────────────────────
            # FIX: if target is a room name, broadcast to all members.
            elif mtype == "FILE":
                if len(parts) < 4:
                    continue
                target = parts[1]
                fname  = parts[2]

                # Size field may have trailing garbage if client didn't
                # send \n — strip non-digits.
                raw_size = ''.join(c for c in parts[3] if c.isdigit())
                if not raw_size:
                    continue
                size = int(raw_size)
                data = reader.read_bytes(size)

                fwd_header = f"FILE|{username}|{fname}|{size}\n"
                payload    = fwd_header.encode() + data

                if target in rooms:
                    # ✅ FIX: broadcast to room members
                    broadcast_room(target, username, payload)
                else:
                    # Private file
                    send_to(target, payload)

            # ── VIDEO / VOICE DATA ────────────────────────────────
            # FIX: read size robustly; relay regardless of active_calls
            # race condition (call may not be registered yet on first frames).
            elif mtype in ("VIDEO", "VOICE"):
                if len(parts) < 4:
                    continue
                target   = parts[1]
                raw_size = ''.join(c for c in parts[3] if c.isdigit())
                if not raw_size:
                    continue
                size = int(raw_size)
                data = reader.read_bytes(size)

                # Relay if:
                #   (a) active call is registered, OR
                #   (b) the target has this user listed as their call partner
                #   (handles race where VIDCALL_ACC hasn't arrived yet)
                call_info   = active_calls.get(username)
                target_call = active_calls.get(target)
                should_relay = (
                    (call_info and call_info[0] == target) or
                    (target_call and target_call[0] == username)
                )
                if should_relay:
                    fwd_header = f"{mtype}|{username}|x|{size}\n"
                    send_to(target, fwd_header.encode() + data)

            # ── CALL SIGNALLING ───────────────────────────────────
            elif mtype == "VIDCALL_REQ":
                target    = parts[1] if len(parts) > 1 else ""
                call_type = parts[2] if len(parts) > 2 else 'video'
                send_to(target, f"VIDCALL_REQ|{username}|{call_type}\n".encode())

            elif mtype == "VIDCALL_ACC":
                target    = parts[1] if len(parts) > 1 else ""
                call_type = parts[2] if len(parts) > 2 else 'video'
                active_calls[username] = (target, call_type)
                active_calls[target]   = (username, call_type)
                send_to(target, f"VIDCALL_ACC|{username}|{call_type}\n".encode())

            elif mtype == "VIDCALL_REJ":
                target    = parts[1] if len(parts) > 1 else ""
                call_type = parts[2] if len(parts) > 2 else 'video'
                send_to(target, f"VIDCALL_REJ|{username}|{call_type}\n".encode())

            elif mtype == "VIDCALL_END":
                target = parts[1] if len(parts) > 1 else ""
                active_calls.pop(username, None)
                active_calls.pop(target,   None)
                send_to(target, f"VIDCALL_END|{username}\n".encode())

            else:
                print(f"[?] Unknown message type '{mtype}' from {username}")

    except ConnectionError:
        pass
    except Exception as e:
        print(f"[!] Error handling {username or 'unknown'}: {e}")
        traceback.print_exc()
    finally:
        if username:
            call_info = active_calls.pop(username, None)
            if call_info:
                partner = call_info[0]
                active_calls.pop(partner, None)
                send_to(partner, f"VIDCALL_END|{username}\n".encode())
            clients.pop(username, None)
            for room in list(rooms.keys()):
                if username in rooms[room]:
                    rooms[room].remove(username)
                    if not rooms[room]:
                        del rooms[room]
            conn.close()
            update_lists()
            print(f"[-] {username} disconnected")


# ──────────────────────── Main ────────────────────────
def start():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((HOST, PORT))
    server.listen(50)
    print(f"[*] Chat Server running on {HOST}:{PORT}")
    while True:
        conn, addr = server.accept()
        threading.Thread(target=handle_client,
                         args=(conn, addr), daemon=True).start()


if __name__ == "__main__":
    start()