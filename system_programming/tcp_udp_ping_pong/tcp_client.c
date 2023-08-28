/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   UDP TCP Ping-Pong       */
/*   Date:      06/05/23                */
/*   Reviewer:  Tal                     */
/*                                      */
/****************************************/

#include <stdio.h>  			/* printf() */
#include <stdlib.h> 			/* atoi() */
#include <string.h> 			/* strlen() */
#include <unistd.h> 			/* sleep() */
#include <netinet/in.h>			/* sockaddr_in */

#include "tcp_udp_ping_pong.h"  /* header file */

#define MAXLINE (1024)
#define PORT_SIZE (6)

enum status
{
    FAIL = -1,
    SUCCESS
};

static int TCPClient(char *ip, int port);

int main(int argc, char *argv[])
{
    char port[PORT_SIZE] = {0};
    
    printf("please insert port number: ");
    fgets(port, PORT_SIZE, stdin);

    TCPClient(argv[argc - 1], atoi(port));
    
	return 0;
}

static int TCPClient(char *ip, int port)
{
    int socket_fd = 0; 
    char server_message[MAXLINE] = {0};
    char server_reply[MAXLINE] = {0};
    
    socket_fd = SocketCreate();
    if(FAIL == socket_fd)
    {
        printf("Could not create socket\n");
        return FAIL;
    }

    if (SocketConnect(socket_fd, ip, port) < 0)
    {
        perror("connect failed.\n");
        return FAIL;
    }

    printf("Enter the Message: ");
    fgets(server_message, MAXLINE, stdin);
    
    SocketSend(socket_fd, server_message);

    SocketReceive(socket_fd, server_reply);
    printf("Server Response: %s\n\n",server_reply);
    
    close(socket_fd);
    shutdown(socket_fd,0);
    shutdown(socket_fd,1);
    shutdown(socket_fd,2);
    
    return SUCCESS;
}
