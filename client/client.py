import socket
import sys
from reprlib import Repr

HOST = '192.168.1.10'
PORT = 17777
CONNECT_TIMEOUT = 1

with socket.create_connection((HOST, PORT), CONNECT_TIMEOUT) as s:
    s.sendall(bytearray(sys.argv[1] + '\0', 'ascii')) # todo check without zero
    data = s.recv(1024)
print('Received', repr(data))
