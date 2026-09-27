import socket
import cv2
import numpy as np
import struct

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 9999))  # change IP

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 50]
    result, frame = cv2.imencode('.jpg', frame, encode_param)

    data = frame.tobytes()
    size = len(data)

    client.sendall(struct.pack("L", size) + data)

    cv2.imshow("Client Video", frame)

    if cv2.waitKey(1) == 27:  # ESC
        break

cap.release()
client.close()
cv2.destroyAllWindows()