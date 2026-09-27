import socket
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind(('localhost', 12345))
data, clientAdd = server.recvfrom(1024)
if data.decode() == "ping":
    server.sendto(b"pong", clientAdd)
else:
    print("Error!")

with open(r"C:\Users\GH Tech\Documents\1University\Semester 3\Semester3\CN Lab\Practice\UDP\recvFile.py", "wb") as file:
    while True:
        data, clientAdd = server.recvfrom(1024)
        if data == b"EOF":
            break
        file.write(data)

print("File Recived!")
    
server.close()