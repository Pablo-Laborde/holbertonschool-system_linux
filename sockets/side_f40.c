#include "sockets.h"



/**
* create_socket - Creates a socket.
* Return: Socket file descriptor.
*/
int create_socket(void)
{
	int socket_fd = 0;

	socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_fd == -1)
	{
		printf("Failed creating socket.\n");
		exit(errno);
	}
	return (socket_fd);
}


/**
* bind_socket - Binds a socket.
* @socket_fd: Socket file descriptor.
* @port: Port to bind.
*/
void bind_socket(int socket_fd, int port)
{
	struct sockaddr_in socket_addr;

	socket_addr.sin_family = AF_INET;
	socket_addr.sin_port = htons(port);
	socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socket_fd, (struct sockaddr *)&socket_addr,
		sizeof(struct sockaddr_in)) == -1)
	{
		printf("Failed to bind.\n");
		exit(errno);
	}
}


/**
* listen_socket - Listens to socket.
* @socket_fd: Socket file descriptor.
* @port: Port to listen.
*/
void listen_socket(int socket_fd, int port)
{
	if (listen(socket_fd, 1) == -1)
	{
		printf("Failed to listen.\n");
		exit(errno);
	}
	printf("Server listening on port %d\n", port);
}


/**
* accept_client - Accepts a client.
* @socket_fd: Socket file descriptor.
* Return: Client file descriptor.
*/
int accept_client(int socket_fd)
{
	int client_fd = 0;
	struct sockaddr_in client_addr;
	socklen_t addr_len = 0;

	addr_len = (socklen_t)sizeof(struct sockaddr_in);
	client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_len);
	if (client_fd == -1)
		exit(errno);
	printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
	return (client_fd);
}


/**
* get_input - Retrieves input from client.
* @client_fd: Client file descriptor.
* Return: Input retrieved.
*/
char *get_input(int client_fd)
{
	char buffer[256], *fmsg = NULL, *aux = NULL;
	ssize_t blen = 0, msglen = 0, alen = 0;

	while (1)
	{
		aux = fmsg;
		alen = msglen;
		blen = recv(client_fd, buffer, 255, 0);
		msglen += blen;
		fmsg = malloc(msglen + 1);
		if (!fmsg)
			exit(errno);
		fmsg[msglen] = 0;
		if (aux)
		{
			memcpy(fmsg, aux, alen);
			free(aux);
		}
		memcpy(fmsg + alen, buffer, blen);
		if (!strcmp(fmsg + msglen - 4, "\r\n\r\n"))
			break;
	}
	return (fmsg);
}
