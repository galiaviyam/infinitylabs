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
#include <stdlib.h>     /* rand */
#include <strings.h>    /* bzero */
#include <string.h>     /* memset */
#include <unistd.h>     /* close */
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

int UDPClient(char *server_ip, int port);
void ServerAddrInit(struct sockaddr_in *servaddr, size_t port, char *ip);

int main(int argc, char *argv[]) 
{
	char port[PORT_SIZE] = {0};
    
    printf("Insert port number: ");
    fgets(port, PORT_SIZE, stdin);
    
	return UDPClient(argv[argc - 1], atoi(port));
}

int UDPClient(char *server_ip, int port)
{
    int sockfd;
    char buffer[MAXLINE];
    char *message = "ping";
    struct sockaddr_in servaddr;
    int num_pings = 0;
    int sec_to_sleep = 0;
    int len = 0;
    int i = 0;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("socket creation failed");
        return FAIL;
    }
    memset(&servaddr, 0, sizeof(servaddr));

    ServerAddrInit(&servaddr, port, server_ip);

    srand(time(NULL));
    num_pings = rand() % (MAX_PINGS - MIN_PINGS + 1) + MIN_PINGS;

    for (i = 0; i < num_pings; ++i)
    {
        sendto(sockfd, (const char *)message, strlen(message),
            0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        
        recvfrom(sockfd, (char *)buffer, MAXLINE, 0, 
                    (struct sockaddr *)&servaddr, (socklen_t *)&len);
        
        printf("Message from server: %s\n\n", buffer);

        sec_to_sleep = rand() % (MAX_PINGS - MIN_PINGS + 1) + MIN_PINGS;
        sleep(sec_to_sleep);
    }

    close(sockfd);

    return 0;
}

void ServerAddrInit(struct sockaddr_in *servaddr, size_t port, char *ip)
{
    bzero(servaddr, sizeof(struct sockaddr_in));
    servaddr->sin_family = AF_INET;
    servaddr->sin_port = htons(port);
    servaddr->sin_addr.s_addr = inet_addr(ip);
}

