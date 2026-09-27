import socket

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind(('localhost', 12345))
data, clientAdd = server.recvfrom(1024)


server.sendto(data, clientAdd)

server.close()