/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Ping-Pong Server        */
/*   Date:      08/05/23                */
/*   Reviewer:  Noy                     */
/*                                      */
/****************************************/

#include <stdio.h>			/* printf() */
#include <stdlib.h>			/* atoi() */
#include <string.h>			/* strcmp() */
#include <unistd.h>			/* close() */
#include <arpa/inet.h>      /* inet_addr() */
#include <strings.h>        /* bzero */

#define MAXLINE (1024)
#define PORT_SIZE (6)
#define NUM_MSG (6)

enum status
{
    FAIL = -1,
    SUCCESS
};

int UDPBroadcast(int port);
void ServerAddrInit(struct sockaddr_in *servaddr, int port);

int main(void)
{
	char port[PORT_SIZE] = {0};
    
    printf("please enter port number: ");
    fgets(port, PORT_SIZE, stdin);

    return UDPBroadcast(atoi(port));
}

int UDPBroadcast(int port)
{
    int socket_fd = 0;
    char buffer[MAXLINE] = {0};
    struct sockaddr_in broadcast_addr = {0};
    char *message = "BROADCAST: ping 🧚🧚🧚🧚🧚🧚";
    char *message_ping = "ping";
    int broadcast_enable = 1;
    int len = 0;
    
    socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (0 > socket_fd) 
    {
        return FAIL;
    }

    if (FAIL == setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, 
        &broadcast_enable, sizeof(broadcast_enable))) 
    {
        return FAIL;
    }

    memset(&broadcast_addr, 0, sizeof(broadcast_addr));

    ServerAddrInit(&broadcast_addr, port);

    if (FAIL == sendto(socket_fd, message, strlen(message), 0, 
        (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr))) 
    {
        return FAIL;
    }
    if (FAIL == sendto(socket_fd, message_ping, strlen(message_ping), 0, 
        (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr))) 
    {
        return FAIL;
    }
    
    recvfrom(socket_fd, (char *)buffer, MAXLINE, 0, 
                (struct sockaddr *)&broadcast_addr, (socklen_t *)&len);

    printf("Message from server: %s\n\n", buffer);

    close(socket_fd);

    return 0;    
}

void ServerAddrInit(struct sockaddr_in *servaddr, int port)
{
    bzero(servaddr, sizeof(struct sockaddr_in));
    servaddr->sin_family = AF_INET;
    servaddr->sin_port = htons(port);
    servaddr->sin_addr.s_addr = htonl(INADDR_BROADCAST);
}
