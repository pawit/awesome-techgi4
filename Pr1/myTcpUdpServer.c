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

#define MAX_BUFFER_LENGTH 100

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
    struct sockaddr_in my_udp_addr;
    struct sockaddr_in my_tcp_addr;
    
    int socktcp = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int sockudp = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int tcpPort = atoi(argv[1]);
    int udpPort = atoi(argv[2]); 
    
    char buffer[4];
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
    
    memset(&my_udp_addr, 0, sizeof (my_udp_addr));
    memset(&my_tcp_addr, 0, sizeof (my_tcp_addr));
    
    my_udp_addr.sin_family = AF_INET;
    my_udp_addr.sin_port = htons(udpPort);
    my_udp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    fromlen = sizeof (my_udp_addr);
    
    my_tcp_addr.sin_family = AF_INET;
    my_tcp_addr.sin_port = htons(udpPort);
    my_tcp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    
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
    
    for (;;) {
        recsize = recvfrom(sockudp, (void *)buffer, sizeof (buffer), 0, (struct sockaddr *)&my_udp_addr, &fromlen);
        if (recsize < 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        unsigned int a,b;
        unpackData(buffer, &a, &b);
        printf("GCD of %d, %d: %d\n", a, b, gcd(a,b));
    }
    
    
}






