/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   UDP TCP Ping-Pong       */
/*   Date:      06/05/23                */
/*   Reviewer:  Tal                     */
/*                                      */
/****************************************/

#include <stdio.h>  			/* printf() */
#include <string.h> 			/* strlen() */
#include <unistd.h> 			/* sleep() */
#include <netinet/in.h>			/* sockaddr_in */

#include "tcp_udp_ping_pong.h"  /* header file */
	
#define MAXLINE (1024)
#define MAX_MSGS (5)

enum status
{
    FAIL = -1,
    SUCCESS
};

static int UDPServer(int port);
	
int main(void) 
{
	int port_num = 0;
    
    printf("please insert port number: ");
    scanf("%d", &port_num);
	
	UDPServer(port_num);

	return 0;
}

static int UDPServer(int port)
{
	int socket_fd = 0;
	char buffer[MAXLINE] = {0};
	const char *message = "Pong";
	struct sockaddr_in cliaddr = {0};
	int len = 0;
    int n = 0;
    size_t i = 0;

	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
    {
		perror("socket creation failed");
		return FAIL;
	}
		
	if (BindCreatedSocket(socket_fd, NULL, port) < 0)
	{
		perror("bind failed");
		return FAIL;
	}
		
	len = sizeof(cliaddr);
	
    for (i = 0; i < MAX_MSGS; ++i)
    {
        n = recvfrom(socket_fd, (char *)buffer, MAXLINE, MSG_WAITALL, 
                    (struct sockaddr *)&cliaddr, (socklen_t *)&len);
        buffer[n] = '\0';
		sleep(1);
        printf("message from client: %s\n", buffer);
        sendto(socket_fd, (const char *)message, strlen(message), MSG_CONFIRM, 
              (const struct sockaddr *)&cliaddr, len);
    }

	return SUCCESS;
}
