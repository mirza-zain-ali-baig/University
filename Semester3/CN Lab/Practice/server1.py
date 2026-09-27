from datetime import datetime
import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
port = 12345
server.bind(('localhost', port))

server.listen(3)

print("Server is listening on this port",port)
conn, clientAdd = server.accept()

data = conn.recv(1024)
print( "Client: ", data.decode())
currentTime = datetime.now().strftime("%d-%m-%Y %H-%M-%S")
conn.send(currentTime.encode())
conn.close()
server.close()