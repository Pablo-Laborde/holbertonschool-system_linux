#include "sockets.h"



/**
* main - func
* Return: int
*/
int main(void)
{
	int socket_fd = 0, client_fd = 0, port = 8080;
	char *response = "HTTP/1.1 200 OK\r\n\r\n", *rr = NULL, **arr = NULL;

	setbuf(stdout, NULL);
	socket_fd = create_socket();
	bind_socket(socket_fd, port);
	listen_socket(socket_fd, port);
	while (1)
	{
		client_fd = accept_client(socket_fd);
		rr = get_input(client_fd);
		printf("Raw request: \"%s\"\n", rr);
		arr = ha(rr);
		print_ha(arr);
		free_arr(arr);
		send(client_fd, response, strlen(response), 0);
		close(client_fd);
		free(rr);
	}
	return (0);
}
