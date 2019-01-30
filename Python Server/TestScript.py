#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      Lordy
#
# Created:     12/01/2019
# Copyright:   (c) Lordy 2019
# Licence:     <your licence>
#-------------------------------------------------------------------------------

def main():
    import socket

    UDP_IP = "127.0.0.1"
    UDP_PORT = 5005
    MESSAGE = b'Hello, World!'

    print "UDP target IP:", UDP_IP
    print "UDP target port:", UDP_PORT
    print "message:", MESSAGE

    sock = socket.socket(socket.AF_INET, # Internet
                         socket.SOCK_DGRAM) # UDP
    sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
    pass

if __name__ == '__main__':
    main()
