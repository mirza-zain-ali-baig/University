import socket
import time
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
startTime = time.time()
client.sendto(b"ping", ('localhost', 12345))

data, serverAdd = client.recvfrom(1024)
endTime = time.time()
if data.decode() == "pong":
    print("Testing is okay.")
else:
    print("Error")
rtt = (endTime - startTime) * 1000
print(f"RTT: {rtt:.3f} ms")

with open(r"C:\Users\GH Tech\Documents\1University\Semester 3\Semester3\CN Lab\Practice\UDP\server1.py", "rb") as file:
    while True:
        data = file.read(1024)
        if not data:
            break
        client.sendto(data, serverAdd)
client.sendto(b"EOF", serverAdd)
print("File Sended!")

client.close()