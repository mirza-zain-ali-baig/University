# 1- Create socket
# 2- Bind IP + port
# 3- Receive data (recvfrom)/ Send reply (sendto)

import socket
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server.bind(('localhost', 12345))

data, clientAdd = server.recvfrom(1024)
print("Source: ",data.decode())

message = input("Enter you message: ")
server.sendto(message.encode(), clientAdd)
server.close()