import socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 12345))
client.send(b"Send me the current date and time")
data = client.recv(1024)
print("Server:", data.decode())
client.close()