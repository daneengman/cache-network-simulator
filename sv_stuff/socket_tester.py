# echo-client.py

import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 12345  # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    for i in range(5):
        print("\t\tPython: Sending tick...")
        s.sendall(b"tick\n")
        data = s.recv(1024)
        print(f"\t\tPython: Received {data!r}")
    print("\t\tPython: Sending quit...")
    s.sendall(b"quit\n")