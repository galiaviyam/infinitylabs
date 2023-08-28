/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   UDP TCP Ping-Pong       */
/*   Date:      06/05/23                */
/*   Reviewer:  Tal                     */
/*                                      */
/****************************************/

#include <stdio.h>			/* printf() */
#include <stdlib.h>			/* atoi() */
#include <string.h>			/* strcmp() */
#include <unistd.h>			/* close() */
#include <netinet/in.h>		/* sockaddr_in */

#include "tcp_udp_ping_pong.h"

#define MAXLINE (1024)
#define PORT_SIZE (6)

enum status
{
    FAIL = -1,
    SUCCESS
};

static int UDPBroadcast(int port);

int main(void)
{
	char port[PORT_SIZE] = {0};
    
    printf("please enter port number: ");
    fgets(port, PORT_SIZE, stdin);

	UDPBroadcast(atoi(port));

    return 0;
}

static int UDPBroadcast(int port)
{
    int socket_fd = 0;
    struct sockaddr_in broadcast_addr = {0};
    char message[MAXLINE]= {0};
    int broadcast_enable = 1;

    socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (FAIL == socket_fd) 
    {
        return FAIL;
    }

    if (FAIL == setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, 
        &broadcast_enable,sizeof(broadcast_enable))) 
    {
        return FAIL;
    }

    ServerAddrInit(&broadcast_addr, port, NULL);
    broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    while (strcmp(message, "\n")) 
    {
        printf("please enter message to broadcast: ");
        fgets(message, MAXLINE, stdin);

        if (FAIL == sendto(socket_fd, message, strlen(message), 0, 
           (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr))) 
        {
            return FAIL;
        }
    }

    close(socket_fd);

    return 0;    
}
