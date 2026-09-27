import socket
import time
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

startTime = time.time()

client.sendto(b"Hello bro.", ('localhost', 12345))

data, serverAddress = client.recvfrom(1024)

endTime = time.time()

rtt = (endTime - startTime) * 1000

print(f"RTT: {rtt:.5f} ms")

client.close()
