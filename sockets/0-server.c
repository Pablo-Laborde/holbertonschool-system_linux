#include "sockets.h"


/**
 * main- func
 * Return: int
 */
int main(void)
{
	int s_fd = 0;
	struct sockaddr_in sa;

	s_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s_fd == -1)
		exit(errno);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(12345);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) == -1)
		exit(errno);
	printf("Socket successfully created and binded.\n");
	if (listen(s_fd, 1) == -1)
		exit(errno);
	while (1)
	{}
	return (0);
}
