import socket
import threading
HOST = '0.0.0.0'
PORT = 12345
MAX_CLIENTS = 4
clients = {}
clients_lock = threading.Lock()
def broadcast_user_list():
    with clients_lock:
        user_list = ','.join(clients.keys())
        for conn in clients.values():
            try:
                conn.sendall(f'USERLIST:{user_list}'.encode())
            except:
                pass

def handle_client(conn, addr):
    try:
        username = conn.recv(1024).decode()
        with clients_lock:
            clients[username] = conn
        broadcast_user_list()
        while True:
            data = conn.recv(4096)
            if not data:
                break
            if data.startswith(b'SENDFILE:'):
                header, filedata = data.split(b'\n', 1)
                _, recipient, filename, filesize = header.decode().split(':')
                filesize = int(filesize)
                with clients_lock:
                    recipient_conn = clients.get(recipient)
                if recipient_conn:
                    try:
                        recipient_conn.sendall(f'RECVFILE:{username}:{filename}:{filesize}\n'.encode())
                        sent = 0
                        recipient_conn.sendall(filedata)
                        sent += len(filedata)
                        while sent < filesize:
                            chunk = conn.recv(min(4096, filesize - sent))
                            if not chunk:
                                break
                            recipient_conn.sendall(chunk)
                            sent += len(chunk)
                    except:
                        pass
            else:
                pass 
    except Exception as e:
        print(f'Error: {e}')
    finally:
        with clients_lock:
            for user, c in list(clients.items()):
                if c == conn:
                    del clients[user]
        conn.close()
        broadcast_user_list()
def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(MAX_CLIENTS)
    print(f'Server listening on {HOST}:{PORT}')
    while True:
        conn, addr = s.accept()
        with clients_lock:
            if len(clients) >= MAX_CLIENTS:
                conn.sendall(b'SERVERFULL')
                conn.close()
                continue
        threading.Thread(target=handle_client, args=(conn, addr), daemon=True).start()
if __name__ == '__main__':
    main()
