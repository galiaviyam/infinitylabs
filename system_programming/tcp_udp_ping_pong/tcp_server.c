/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   UDP TCP Ping-Pong       */
/*   Date:      06/05/23                */
/*   Reviewer:  Tal                     */
/*                                      */
/****************************************/

#include <stdio.h>  		/* printf() */
#include <string.h> 		/* strlen() */
#include <unistd.h> 		/* sleep() */
#include <netinet/in.h>		/* sockaddr_in */

#include "tcp_udp_ping_pong.h"  /* header file */

#define MAXLINE (1024)

enum status
{
    FAIL = -1,
    SUCCESS
};

int TCPServer(int port);

int main(int argc, char *argv[])
{
    int port = 0;
    
    printf("please insert port number: ");
    scanf("%d", &port);
    
    TCPServer(port);

    (void)argc;
    (void)argv;

    return 0;
}

int TCPServer(int port)
{
    int socket_fd = 0;
    int socket = 0;
    int client_len = 0;
    struct sockaddr_in client = {0};
    char client_message[MAXLINE]= {0};
    char message[MAXLINE] = "ping sent from server";
    
    socket_fd = SocketCreate();
    if (FAIL == socket_fd)
    {
        return FAIL;
    }
    
    if(BindCreatedSocket(socket_fd, NULL, port) < 0)
    {
        return FAIL;
    }
    printf("bind done\n");
    
    listen(socket_fd, 3);
    
    while(1)
    {
        printf("Waiting for connections\n");
        client_len = sizeof(struct sockaddr_in);
        
        socket = accept(socket_fd,(struct sockaddr *)&client,
                (socklen_t*)&client_len);
        if (socket < 0)
        {
            return FAIL;
        }

        printf("Connection accepted\n");
        if( recv(socket, client_message, MAXLINE, 0) < 0)
        {
           return FAIL;
        }

        printf("Client message: %s\n", client_message);

        if(send(socket, message, strlen(message), 0) < 0)
        {
            return FAIL;
        }

        close(socket);
        sleep(1);
    }
    
    return SUCCESS;
}
