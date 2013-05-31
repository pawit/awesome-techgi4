#!/usr/bin/env python
# Alexander Couzens <lynxis@c-base.org>
# apache2 license
#
# python3 !

import select
import signal
import sys
from mosquitto import Mosquitto

topic = 'techgi4/msgboard'

class Client(Mosquitto):
    def __init__(self, host, port, client_id):
        super(Client, self).__init__(client_id)

        # we have to do this stuff, because these calls will be set to None explicit
        self.on_connect = self._on_connect
        self.on_subscribe = self._on_subscribe
        self.on_message = self._on_message

        self.connect_async(host, port)

    def _on_connect(self, mosq, userdata, rc):
        print("Connect : %s" % rc)
        self.subscribe(topic, 2)
    
    def _on_subscribe(self, mosq, userdata, mid, granted_qos):
        print("Subscribed: mid %s granted_qos %s" % (mid, granted_qos) )

    def _on_message(self, mosq, userdata, message):
        # see class MosquittoMessage for message type
        print("TODO message received callback")

    def on_stdin(self, message):
        print("TODO stdin mesg : %s" % message)

if __name__ == '__main__':
    # register signal handler for strg-c
    def signal_handler(signal, frame):
        print('')
        print('STRG-C pressed -> exit now')
        sys.exit(0)
    signal.signal(signal.SIGINT, signal_handler)

    # default values
    client_id = ''
    host = 'localhost'
    port = 9999

    if len(sys.argv) > 1:
        host = sys.argv[1]

    if len(sys.argv) > 2:
        port = int(sys.argv[2])

    if len(sys.argv) > 3:
        client_id = sys.argv[3]

    client = Client(host, port, client_id)
    client.loop_start()

    epoll = select.epoll()
    epoll.register(sys.stdin.fileno(), select.EPOLLIN | select.EPOLLET)
    
    while True:
        events = epoll.poll()
        for fileno, event in events:
            if(fileno == sys.stdin.fileno()):
                # maybe this block - check if readline work with epoll
                client.on_stdin(sys.stdin.readline())