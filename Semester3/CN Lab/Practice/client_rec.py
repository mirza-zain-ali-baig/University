import socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(('localhost',12345))

client.send(b"I am client")

data = client.recv(1024)

print("SERVER stops.")

client.close()