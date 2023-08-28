/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   UDP TCP Ping-Pong       */
/*   Date:      06/05/23                */
/*   Reviewer:  Tal                     */
/*                                      */
/****************************************/

void ServerAddrInit(struct sockaddr_in *servaddr, size_t port, char *ip);

int SocketCreate(void);

int BindCreatedSocket(int socket_fd, char *server_ip, int port);

int SocketConnect(int socket_fd, char *server_ip, int port);

int SocketSend(int socket_fd, const char *message);

int SocketReceive(int socket_fd, char* message);
