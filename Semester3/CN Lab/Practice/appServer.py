import socket

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind(('localhost',12345))
serverSocket.listen(4)
print("Server is Listening on the port 12345 ...")

conn, clientAdd = serverSocket.accept()

while True:
    data = conn.recv(1024)
    print("Client: ", data.decode())
    sendingMessage = input("Server: ")
    if sendingMessage != "exit":
       conn.send(sendingMessage.encode())
    else:
        break
serverSocket.close()