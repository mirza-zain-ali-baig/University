import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(('localhost',12345))

with open(r"C:\Users\GH Tech\Documents\1University\Semester 3\QUIZ1\client2.py", "rb") as file:
    while True:
        data = file.read(1024)
        if not data:
            break
        client.send(data)

print("File Sended.")

client.close()