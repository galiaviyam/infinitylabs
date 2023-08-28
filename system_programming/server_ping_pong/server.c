/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   ping-pong Server        */
/*   Date:      08/05/23                */
/*   Reviewer:  Noy                     */
/*                                      */
/****************************************/

#include <arpa/inet.h>  /* AF_INET */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit */
#include <strings.h>    /* bzero */
#include <sys/select.h> /* timeval */
#include <unistd.h>     /* close */
#include <string.h>     /* strlen */
#include <assert.h>     /* assert */

#define MAXLINE 1024
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

enum status
{
    FAIL = -1,
    SUCCESS
};

int Server(int port);
void ServerAddrInit(struct sockaddr_in *servaddr, int port);
int TCPHandler(struct sockaddr_in *cliaddr, int listenfd, char *buffer, 
               const char *message);
void UDPHandler(struct sockaddr_in *cliaddr, int udpfd, char *buffer, 
                const char *message);

int main(int argc, char *argv[])
{
    int port = 0;
    
    printf("please insert port number: ");
    scanf("%d", &port);
    
    (void)argc;
    (void)argv;

    return Server(port);
}

int Server(int port)
{
    int listenfd = 0;
    int udpfd = 0;
    int maxfdp1 = 0;
    char buffer[MAXLINE] = {0};
    fd_set rset;
    struct sockaddr_in cliaddr, servaddr;
    char *message = "pong 🧚‍♀️❤️‍🔥";

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    ServerAddrInit(&servaddr, port);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);

    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    bind(udpfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    FD_ZERO(&rset);

    maxfdp1 = MAX(listenfd, udpfd) + 1;

    while (0 != strcmp(buffer, "quit\n"))
    {
        struct timeval timeout = {0};
        timeout.tv_sec = 7;
        timeout.tv_usec = 0;

        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);
        FD_SET(STDIN_FILENO, &rset);

        if (0 == select(maxfdp1, &rset, NULL, NULL, &timeout))
        {
            printf("No new connection in 7 seconds\n");
        }

        if (FD_ISSET(listenfd, &rset))
        {
            if (FAIL == TCPHandler(&cliaddr, listenfd, buffer, message))
            {
                return FAIL;
            }

        }

        if (FD_ISSET(udpfd, &rset))
        {
            UDPHandler(&cliaddr, udpfd, buffer, message);
        }
        if (FD_ISSET(STDIN_FILENO, &rset))
        {
            fgets(buffer, MAXLINE, stdin);

            if (0 == strcmp(buffer, "ping\n"))
            {
                printf("pong\n");
            }
        }
     }

    return 0;
}

void ServerAddrInit(struct sockaddr_in *servaddr, int port)
{
    bzero(servaddr, sizeof(struct sockaddr_in));
    servaddr->sin_family = AF_INET;
    servaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr->sin_port = htons(port);
}

void UDPHandler(struct sockaddr_in *cliaddr, int udpfd, char *buffer, 
                const char *message)
{
    int len = 0;

    assert(cliaddr);
    assert(buffer);
    assert(message);

    len = sizeof(struct sockaddr_in);
    bzero(buffer, MAXLINE);

    printf("\nMessage from UDP client: ");
    recvfrom(udpfd, buffer, MAXLINE, 0,
            (struct sockaddr *)cliaddr, (socklen_t *)&len);    
    printf("%s\n\n", buffer);

    if (0 == strcmp(buffer, "ping"))
    {
        sendto(udpfd, (const char *)message, MAXLINE, 0,
              (struct sockaddr *)cliaddr, sizeof(struct sockaddr_in));
    }    
}

int TCPHandler(struct sockaddr_in *cliaddr, int listenfd, char *buffer, 
               const char *message)
{
    int connfd = 0, len = 0;
    pid_t childpid = 0;
    char *addr = NULL;

    assert(cliaddr);
    assert(buffer);
    assert(message);

    printf("Waiting for connections...\n");
    len = sizeof(*cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)cliaddr, (socklen_t *)&len);
    if (connfd < 0)
    {
        return FAIL;
    }

    addr = inet_ntoa(cliaddr->sin_addr);
    printf("Connection accepted to %s\n", addr);

    if (0 == (childpid = fork()))
    {
        close(listenfd);
        memset(buffer, '\0', MAXLINE);

        while (recv(connfd, buffer, MAXLINE, 0) > 0)
        {
            printf("TCP Client message: %s\n\n", buffer);
            if(send(connfd, message, strlen(message), 0) < 0)
            {
                printf("Failed to send\n");
                return FAIL;
            }
        }

        close(connfd);
        printf("TCP client %s disconnected\n", addr);
        exit(0);
    }     
    close(connfd);

    return SUCCESS;
}
