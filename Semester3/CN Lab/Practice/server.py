# 1- import socket
# 2- Create server socket
# 3- bind(means fixed the ip and port of server) server ip and port 
# 4- server lsiten (queued size) - Creates a waiting queue When many clients try to connect
# at the same time: Some are accepted immediately
# Others are placed in a queue (waiting line)
# 5 - server Accept the client (it gives two things - new conn object socket and ip address of client)
# 6 - Send/Recieve data
# 7 - Close server connection


import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind(('localhost', 12345))

print("Server is listening on port 12345 ...")

server.listen(5)

conn, clientAdress = server.accept()

data = conn.recv(1024)
print("Message: ", data.decode())

conn.send(b"Hello by bro.")
