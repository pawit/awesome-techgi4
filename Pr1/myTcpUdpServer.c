/*
############################################################################
#                                                                          #
# Copyright TU-Berlin, 2011                                                #
# Die Weitergabe, Veröffentlichung etc. auch in Teilen ist nicht gestattet #
#                                                                          #
############################################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

#define MAX_BUFFER_LENGTH 100

/* plagiarized from euklid */
int gcd(int n, int m) {
    if (n == 0) return m;
    return gcd(m%n, n);
}

void unpackData(unsigned char *buffer, unsigned int *a, unsigned int *b) {
    *a = (buffer[0]<<8) | buffer[1];
    *b = (buffer[2]<<8) | buffer[3];
}



int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr,"Usage: tus tcp-port udp-port\n");
        exit(1);
    }

    struct sockaddr_in my_udp_addr;
    struct sockaddr_in my_tcp_addr;

    int socktcp = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int sockudp = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int tcpPort = atoi(argv[1]);
    int udpPort = atoi(argv[2]);

    /* We'll handle mutiple connections, especially support for upd and tcp
       fd_set will store all I/O-blocking sockets, in our case the udp/tcp socket
    */
    fd_set readfds;

    char buffer[4];

    /* recsize and fromlen are needed for the udp-socket,
       recsize will store the length of the received message
       fromlen will have the length of the udp-addr, needed for the recvfrom function
    */
    ssize_t recsize;
    socklen_t fromlen;

    if (-1 == sockudp) {
        perror("could not create udp socket");
        exit(EXIT_FAILURE);
    }

    if (-1 == socktcp) {
        perror("could not create tcp socket");
        exit(EXIT_FAILURE);
    }

    /* will set the structs to zero */
    memset(&my_udp_addr, 0, sizeof (my_udp_addr));
    memset(&my_tcp_addr, 0, sizeof (my_tcp_addr));


    my_udp_addr.sin_family = AF_INET;
    my_udp_addr.sin_port = htons(udpPort);
    my_udp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    fromlen = sizeof (my_udp_addr);

    my_tcp_addr.sin_family = AF_INET;
    my_tcp_addr.sin_port = htons(tcpPort);
    my_tcp_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int yes=1; // wtf
    // if "adress is already in use"
    if (setsockopt(socktcp,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    // if "adress is already in use"
    if (setsockopt(sockudp,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    /* Let's bind the sockets! */
    if (-1 == bind(socktcp,(struct sockaddr*) &my_tcp_addr, sizeof (my_tcp_addr))) {
        perror("could not bind");
        close(socktcp);
        exit(EXIT_FAILURE);
    }

    if (-1 == bind(sockudp,(struct sockaddr*) &my_udp_addr, sizeof (my_udp_addr))) {
        perror("could not bind");
        close(socktcp);
        exit(EXIT_FAILURE);
    }
    /* start listening, right now, up to 10 connections are supported */
    if (-1 == listen(socktcp, 10)) {
        perror("could not listen");
        close(socktcp);
        exit(EXIT_FAILURE);
    }

    unsigned int a,b;
    for (;;) {
        /* clear the fd-set that will hold all our socktes, and then add the sockets */
        FD_ZERO(&readfds);
        FD_SET(socktcp, &readfds);
        FD_SET(sockudp, &readfds);
        /* select will take a int parameter, which has to be the highest of all I/O-sockets+1, maybe it will create one */
        int fd_max = max(sockudp, socktcp) + 1;
        /* select blocks as long as nothing happns */
        select(fd_max, &readfds, NULL, NULL, NULL);
        /* select isn't blocking, something happened, check all sockets if they were the cause */
        if (FD_ISSET(sockudp, &readfds)) {
            recsize = recvfrom(sockudp, (void *)buffer, sizeof (buffer), 0, (struct sockaddr *)&my_udp_addr, &fromlen);
            if (recsize < 0) {
                fprintf(stderr, "%s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            unpackData(buffer, &a, &b);
            printf("GCD of %d, %d: %d\n", a, b, gcd(a,b));
        } else if (FD_ISSET(socktcp, &readfds)) {
            /* In tcp we'll build a connection, the socktcp functions as a master that creates new connections */
            int con = accept(socktcp, NULL, NULL);
            if (0 > con) {
                perror("error accept failed");
                close(socktcp);
                exit(EXIT_FAILURE);
            }
            read(con, buffer, 4);
            unpackData(buffer, &a, &b);
            printf("GCD of %d, %d: %d\n", a, b, gcd(a,b));

            if ( -1 == shutdown(con, SHUT_RDWR)) {
                perror("can not shutdown socket");
                close(con);
                close(socktcp);
                exit(EXIT_FAILURE);
            }
            close(con);
        } else {
            /* This should never happen */
            break;
        }
    }
}






