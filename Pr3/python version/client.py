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
debug = False

# in clojure: (partial merge-with +)
def max_clocks(c1, c2):
    new_clock = c1
    for k1 in c1:
        if k1 in c2 and c1[k1] >= c2[k1]:
            new_clock[k1] = c1[k1]
    for k2 in c2:
        if k2 and c2[k2] > c1[k2]:
            new_clock[k2] = c2[k2]
    return new_clock


class Client(Mosquitto):
    def __init__(self, host, port, client_id):
        super(Client, self).__init__(client_id)

        # we have to do this stuff, because these calls will be set to None explicit
        self.on_connect = self._on_connect
        self.on_subscribe = self._on_subscribe
        self.on_message = self._on_message

        self.connect_async(host, port)

        # I don't know yet, where the id is stored
        self.client_id = client_id
        # we use a hash_array where the keys are the ids of the clients
        self.vector_clock = {self.client_id: 0}
        # queue to save messages
        self.queue = []

    def _on_connect(self, mosq, userdata, rc):
        print("Connect : %s" % rc)
        self.subscribe(topic, 2)

    def _on_subscribe(self, mosq, userdata, mid, granted_qos):
        print("Subscribed: mid %s granted_qos %s" % (mid, granted_qos))

    def _on_message(self, mosq, userdata, message):
        # we don't increment when receiving!
        # very very unsecure :D
        m, i, c = eval(message.payload)
        # Don't process own messages
        if i == self.client_id:
            return
        if i not in self.vector_clock:
            self.vector_clock[i] = 0
        # check if there are any messages preceeding this one
        if self.vector_clock[i] + 1 != c[i]:
            self.queue.append(message)
            if debug:
                print('waiting for message...')
        else:
            print("%s: %s" % (i, m))
            self.vector_clock = max_clocks(self.vector_clock, c)
            # we received a message, are there any messages that followed this message?
            # could use a sorted list
            for me in self.queue:
                for mes in self.queue:
                    m, i, c = eval(mes.payload)
                    if self.vector_clock[i] + 1 == c[i]:
                        self.vector_clock = max_clocks(self.vector_clock, c)
                        print("%s: %s" % (i, m))


    def on_stdin(self, message):
        self.vector_clock[self.client_id] += 1
        self.publish(topic, str([message,self.client_id, self.vector_clock]), 0)

if __name__ == '__main__':
    # register signal handler for strg-c
    def signal_handler(signal, frame):
        print('')
        print('STRG-C pressed -> exit now')
        sys.exit(0)
    signal.signal(signal.SIGINT, signal_handler)

    # default values
    client_id = '0'
    host = '127.0.0.1'
    port = 1883

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