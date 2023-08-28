/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   UDP TCP Ping-Pong       */
/*   Date:      06/05/23                */
/*   Reviewer:  Tal                     */
/*                                      */
/****************************************/
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/time.h>

#include "tcp_udp_ping_pong.h"  /* header file */

#define MAXLINE (1024)
#define TIMEOUT (20)

enum status
{
    FAIL = -1,
    SUCCESS
};

void ServerAddrInit(struct sockaddr_in *servaddr, size_t port, char *ip)
{
	if (NULL != ip)
	{
		servaddr->sin_addr.s_addr = inet_addr(ip);	
	}
	else
	{
		servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
	}

	servaddr->sin_family = AF_INET;
	servaddr->sin_port = htons(port);
}

int SocketCreate(void)
{
    return (socket(AF_INET, SOCK_STREAM, 0));
}

int BindCreatedSocket(int socket_fd, char *server_ip, int port)
{
    struct sockaddr_in servaddr = {0};
    
    ServerAddrInit(&servaddr, port, server_ip);
    
    return bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
}

int SocketConnect(int socket_fd, char *server_ip, int port)
{
    struct sockaddr_in servaddr= {0};

    ServerAddrInit(&servaddr, port, server_ip);
    
    return connect(socket_fd, (struct sockaddr *)&servaddr, 
                    sizeof(struct sockaddr_in));
}

int SocketSend(int socket_fd, const char *message)
{
    struct timeval tv = {0};
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_SNDTIMEO,(char *)&tv, 
        sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return FAIL;
    }

    return send(socket_fd, message, MAXLINE, 0);
}

int SocketReceive(int socket_fd, char* message)
{
    int status = FAIL;
    struct timeval tv = {0};
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, 
        sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return FAIL;
    }

    status = recv(socket_fd, message, MAXLINE, 0);
    printf("Response %s\n",message);
    
    return status;
}
