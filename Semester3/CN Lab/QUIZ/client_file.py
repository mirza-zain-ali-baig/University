import socket
import threading
import os

HOST = '127.0.0.1'
PORT = 12345

username = input('Enter your username: ')

def receive_thread(sock):
    while True:
        try:
            data = sock.recv(4096)
            if not data:
                break
            if data.startswith(b'USERLIST:'):
                userlist = data.decode().split(':', 1)[1]
                print(f'Connected users: {userlist}')
            elif data.startswith(b'RECVFILE:'):
                # Format: RECVFILE:sender:filename:size\n
                header, filedata = data.split(b'\n', 1)
                _, sender, filename, filesize = header.decode().split(':')
                filesize = int(filesize)
                received = len(filedata)
                with open(f"recv_{filename}", 'wb') as f:
                    f.write(filedata)
                    while received < filesize:
                        chunk = sock.recv(min(4096, filesize - received))
                        if not chunk:
                            break
                        f.write(chunk)
                        received += len(chunk)
                print(f'Received file "{filename}" from {sender}')
            elif data == b'SERVERFULL':
                print('Server is full. Try again later.')
                os._exit(0)
        except Exception as e:
            print(f'Error: {e}')
            break

def send_file(sock):
    recipient = input('Enter recipient username: ')
    filepath = input('Enter path to file: ')
    if not os.path.isfile(filepath):
        print('File does not exist.')
        return
    filename = os.path.basename(filepath)
    filesize = os.path.getsize(filepath)
    try:
        with open(filepath, 'rb') as f:
            filedata = f.read(4096)
            header = f'SENDFILE:{recipient}:{filename}:{filesize}\n'.encode()
            sock.sendall(header + filedata)
            sent = len(filedata)
            while sent < filesize:
                chunk = f.read(min(4096, filesize - sent))
                if not chunk:
                    break
                sock.sendall(chunk)
                sent += len(chunk)
        print(f'File "{filename}" sent to {recipient}')
    except Exception as e:
        print(f'Error sending file: {e}')

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    sock.sendall(username.encode())
    threading.Thread(target=receive_thread, args=(sock,), daemon=True).start()
    while True:
        cmd = input('Enter "send" to send file or "exit" to quit: ')
        if cmd == 'send':
            send_file(sock)
        elif cmd == 'exit':
            sock.close()
            break

if __name__ == '__main__':
    main()
