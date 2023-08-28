/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   ping-pong Server        */
/*   Date:      08/05/23                */
/*   Reviewer:  Noy                     */
/*                                      */
/****************************************/

#include <arpa/inet.h>  /* inet_addr */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* atoi */
#include <string.h>     /* memset */
#include <unistd.h>     /* write */
#include <sys/time.h>   /* timeval */
#include <time.h>       /* time */

#define PORT_SIZE (6)
#define MAXLINE (1024)
#define MIN_PINGS (3)
#define MAX_PINGS (10)

enum status
{
    FAIL = -1,
    SUCCESS
};

static int TCPClient(char *server_ip, int port);
int SocketSend(int sock_fd, const char *message);
int SocketReceive(int sock_fd, char *message);

int main(int argc, char *argv[]) 
{
	char port[PORT_SIZE] = {0};
    
    printf("Insert port number: ");
    fgets(port, PORT_SIZE, stdin);
    
	return TCPClient(argv[argc - 1], atoi(port));
}

int SocketSend(int sock_fd, const char *message)
{
    int status = FAIL;
    struct timeval tv = {0};
    tv.tv_sec = 20;
    tv.tv_usec = 0;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO,(char *)&tv, 
        sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return FAIL;
    }

    status = send(sock_fd, message, MAXLINE, 0);
    
    return status;
}

int SocketReceive(int sock_fd, char *message)
{
    int status = FAIL;
    struct timeval tv = {0};
    tv.tv_sec = 20;  
    tv.tv_usec = 0;

    if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, 
        sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return FAIL;
    }

    status = recv(sock_fd, message, MAXLINE, 0);
    
    return status;
}

int TCPClient(char *server_ip, int port)
{
    int sockfd = 0;
    char buffer[MAXLINE] = {0};
    char *message = "ping 🦥 🦔";
    struct sockaddr_in servaddr = {0};
    int i = 0;
    int num_pings = 0;
    int sec_to_sleep = 0;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket creation failed");
        return FAIL;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sockfd, (struct sockaddr *)&servaddr,
                sizeof(servaddr)) < 0)
    {
        printf("\n Error: Connect Failed \n");
    }

    srand(time(NULL));
    num_pings = rand() % (MAX_PINGS - MIN_PINGS + 1) + MIN_PINGS;

    for (i = 0; i < num_pings; ++i)
    {
        SocketSend(sockfd, message);
        printf("Message sent to server\n");

        SocketReceive(sockfd, buffer);

        printf("Message from server: %s\n\n", buffer);

        sec_to_sleep = rand() % (MAX_PINGS - MIN_PINGS + 1) + MIN_PINGS;
        sleep(sec_to_sleep);

    }

    close(sockfd);

    return 0;
}
