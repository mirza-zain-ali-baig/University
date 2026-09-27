import socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost',12345))
client.send(b"Hello, my Client.")
data = client.recv(1024)
print(data.decode())
client.close()