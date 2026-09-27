import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 12345))

print("Server is listening on port 12345 ...")

server.listen(5)

conn, clientAdress = server.accept()

with open(r"C:\Users\GH Tech\Documents\1University\Semester 3\QUIZ1\clientREV.py", "wb") as file:
    while True:
        data = conn.recv(1024)
        if not data: 
            break
        file.write(data)



print("File Recieved.")

conn.close()
server.close()
