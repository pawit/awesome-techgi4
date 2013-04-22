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

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in their_addr; // connector's address information
    struct hostent *he;
    int numbytes;
    int serverPort;
    int a = 0;
    int b = 0;

    printf("TCP client example\n\n");
    
    if (argc != 5) {
        fprintf(stderr,"Usage: tcpClient serverName serverPort int1 int2\n");
        exit(1);
    }
    
    serverPort = atoi(argv[2]);
    a = atoi(argv[3]);
    b = atoi(argv[4]);    

    // Resolve hostname to IP Address
    if ((he=gethostbyname(argv[1])) == NULL) {  // get the host info
        herror("gethostbyname");
        exit(1);
    }

    /* ******************************************************************
    TO BE DONE: Create socket
    ******************************************************************* */
    sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    //setup transport address
    their_addr.sin_family = AF_INET;     
    their_addr.sin_port = htons(serverPort);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);
    
    unsigned char buffer[4];

    packData(&buffer, a, b);

    /* ******************************************************************
    TO BE DONE:  Send data
    ******************************************************************* */
    int i = 0;
    for (i = 0; i < 1; i++) {
        if (-1 == sendto(sockfd, buffer, 4, 0, (struct sockaddr*) &their_addr, sizeof their_addr)) {
            perror("sending data failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }

    /* ******************************************************************
    TO BE DONE:  Close socket
    ******************************************************************* */
    close(sockfd);
    // printf("GCD von %d und %d ist: %d\n", a, b, (int) *buffer);
    
    return 0;
}

int packData(unsigned char *buffer, unsigned int a, unsigned int b) {
    /* ******************************************************************
    TO BE DONE:  pack data
    ******************************************************************* */
    buffer[1] = (unsigned char) (255 & a);
    buffer[0] = (unsigned char) (((255 << 8) & a) >> 8);
    buffer[3] = (unsigned char) (255 & b);
    buffer[2] = (unsigned char) (((255 << 8) & b) >> 8);
    printf("SENDING: %d, %d, %d, %d \n", buffer[0], buffer[1], buffer[2], buffer[3]);
    return 0;
}
