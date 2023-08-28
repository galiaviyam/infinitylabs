/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   UDP TCP Ping-Pong       */
/*   Date:      06/05/23                */
/*   Reviewer:  Tal                     */
/*                                      */
/****************************************/

#include <stdio.h>				/* printf() */
#include <stdlib.h>				/* atoi() */
#include <string.h>				/* strlen() */
#include <unistd.h>				/* sleep() */
#include <netinet/in.h>			/* sockaddr_in */

#include "tcp_udp_ping_pong.h"  /* header file */

enum status
{
    FAIL = -1,
    SUCCESS
};

#define PORT_SIZE (6)
#define MAXLINE (1024)
#define MAX_MSGS (5)

static int UDPClient(char *server_ip, int port);

int main(int argc, char *argv[]) 
{
	char port[PORT_SIZE] = {0};
    
    printf("Insert port number: ");
    fgets(port, PORT_SIZE, stdin);
    
    UDPClient(argv[argc - 1], atoi(port));

	return 0;
}

static int UDPClient(char *server_ip, int port)
{
	int socket_fd = 0;
	char buffer[MAXLINE] = {0};
	const char *msg = "Ping";
	struct sockaddr_in servaddr = {0};
	int n = 0;
	int len = 0;
	size_t i = 0;

	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		return FAIL;
	}

	ServerAddrInit(&servaddr, port, server_ip);

	for (i = 0; i < MAX_MSGS; ++i)
	{
		sendto(socket_fd, (const char *)msg, strlen(msg), MSG_CONFIRM,
			   (const struct sockaddr *)&servaddr, sizeof(servaddr));

		n = recvfrom(socket_fd, (char *)buffer, MAXLINE, MSG_WAITALL,
					 (struct sockaddr *)&servaddr, (socklen_t *)&len);
		buffer[n] = '\0';
		sleep(1);
		printf("Server: %s\n", buffer);
	}

	close(socket_fd);

	return SUCCESS;
}
