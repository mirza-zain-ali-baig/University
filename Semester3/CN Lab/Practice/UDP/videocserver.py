import socket
import cv2
import numpy as np
import struct

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('0.0.0.0', 9999))
server.listen(1)

print("Waiting for connection...")
conn, addr = server.accept()
print("Connected:", addr)

data = b""
payload_size = struct.calcsize("L")

while True:
    while len(data) < payload_size:
        packet = conn.recv(4096)
        if not packet:
            break
        data += packet

    if not data:
        break

    packed_msg_size = data[:payload_size]
    data = data[payload_size:]

    msg_size = struct.unpack("L", packed_msg_size)[0]

    while len(data) < msg_size:
        data += conn.recv(4096)

    frame_data = data[:msg_size]
    data = data[msg_size:]

    frame = np.frombuffer(frame_data, dtype=np.uint8)
    frame = cv2.imdecode(frame, cv2.IMREAD_COLOR)

    cv2.imshow("Server Video", frame)

    if cv2.waitKey(1) == 27:  # ESC
        break

conn.close()
server.close()
cv2.destroyAllWindows()