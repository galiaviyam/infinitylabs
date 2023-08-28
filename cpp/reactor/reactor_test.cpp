/****************************************/
/*                                      */
/*   Developer: Gali Aviyam             */
/*   Project:   Reactor                 */
/*   Date:      15/06/23                */
/*   Reviewer:  Gal                     */
/*                                      */
/****************************************/
#include <iostream>     // cout
#include <thread>       // thread
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_addr
#include <sys/time.h>   // struct timeval
#include <stdexcept>    // runtime_error

#include "reactor.hpp"

using namespace ilrd;

void TestReactor();
void PingPongTest(void);
int BindCreatedSocket(int socket_fd, char *server_ip, int port);
void ServerAddrInit(struct sockaddr_in *servaddr, size_t port, char *ip);

int main(void)
{
    TestReactor();
    PingPongTest();

    return 0;
}

void TestReactor()
{
    Reactor reactor;

    int readFd = Reactor::Mode::READ;
    reactor.Add(readFd, Reactor::Mode::READ, [](){
        std::cout << "Read callback called." << std::endl;
    });

    int writeFd = Reactor::Mode::WRITE;
    reactor.Add(writeFd, Reactor::Mode::WRITE, [](){
        std::cout << "Write callback called." << std::endl;
    });

    int exceptFd = Reactor::Mode::EXCEPT;
    reactor.Add(exceptFd, Reactor::Mode::EXCEPT, [](){
        std::cout << "Exception callback called." << std::endl;
    });

    reactor.Remove(writeFd, Reactor::Mode::WRITE);

    std::thread reactorThread([&]() 
    {
        reactor.Run();
    });

    std::this_thread::sleep_for(std::chrono::seconds(5));

    reactor.Stop();

    reactorThread.join();

    std::cout << "Reactor tests Passed." << std::endl;
}

void PingPongTest(void)
{
    std::cout << "---------- Ping Pong Test ----------" << std::endl;
    
    const std::size_t MAXLINE = 1024;
	int socket_fd = 0;
	char buffer[MAXLINE] = {0};
	const std::string message = "Pong";
	struct sockaddr_in cliaddr;
	int len = sizeof(struct sockaddr_in);

	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
		throw std::runtime_error("socket() fail");
	}

    std::cout << "Insert port number: " << std::flush;
    int port;
    std::cin >> port;

	if (BindCreatedSocket(socket_fd, NULL, port) < 0)
	{
		throw std::runtime_error("bind() fail");
	}

    Reactor udpServer;
    udpServer.Add(socket_fd, Reactor::READ, [&]()
    {
        auto n = recvfrom(socket_fd, (char *)buffer, MAXLINE, MSG_WAITALL, 
                    (struct sockaddr *)&cliaddr, (socklen_t *)&len);
        buffer[n] = '\0';
        printf("message from client: %s\n", buffer);
        sendto(socket_fd, message.c_str(), message.length(), MSG_CONFIRM, 
              (const struct sockaddr *)&cliaddr, len);
    });

    udpServer.Add(0, Reactor::READ, [&udpServer]()
    {
        std::string input;
        std::cin >> input;
        if ("stop" == input)
        {
            udpServer.Stop(); 
        }
    });

    udpServer.Run();
}


int BindCreatedSocket(int socket_fd, char *server_ip, int port)
{
    struct sockaddr_in servaddr;
    
    ServerAddrInit(&servaddr, port, server_ip);
    
    return bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
}

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

