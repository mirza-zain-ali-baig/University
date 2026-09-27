import socket
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client.sendto(b"HEllo", ("localhost", 12345))
data, message = client.recvfrom(1024)
print(data.decode())
client.close()