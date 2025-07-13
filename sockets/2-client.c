#include "sockets.h"


/**
 * main- func
 * @ac: int
 * @av: char **
 * Return: int
 */
int main(int ac, char **av)
{
	int s_fd = 0, c_fd = 0;
	struct addrinfo hint, *res = NULL;

	if (ac != 3)
	{
		printf("Usage: %s <host> <port>\n", av[0]);
		exit(EXIT_FAILURE);
	}
	s_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	hint.ai_flags = 0;
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;
	hint.ai_addrlen = 0;
	hint.ai_addr = NULL;
	hint.ai_canonname = NULL;
	hint.ai_next = NULL;
	if (getaddrinfo(av[1], av[2], &hint, &res))
		exit(EXIT_FAILURE);
	c_fd = connect(s_fd, res->ai_addr, res->ai_addrlen);
	if (c_fd == -1)
		exit(EXIT_FAILURE);
	printf("Connected to %s:%s\n", av[1], av[2]);
	return (EXIT_SUCCESS);
}
