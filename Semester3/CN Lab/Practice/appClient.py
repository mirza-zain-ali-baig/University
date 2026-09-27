import socket
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket.connect(('localhost',12345))

print("++++++ WELCOME TO CHAT APPLICATION +++++++")

while True:
    message = input("Clinet: ")
    if message != "exit":
        clientSocket.send(message.encode())
        serverMessage = clientSocket.recv(1024)
        print("Server: ", serverMessage.decode())
    else:
        break

clientSocket.close()
    