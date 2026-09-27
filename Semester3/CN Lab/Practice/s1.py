import socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind(('localhost', 12345))
server.listen(5)
print("server is listening on port 112345...")
conn, clientAddress = server.accept()
data = conn.recv(1024)
print(data.decode())
conn.send(b"I am Server.")

conn.close()
server.close()