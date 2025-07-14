#include "sockets.h"


/**
 * main- func
 * Return: int
 */
int main(void)
{
	int s_fd = 0, c_fd = 0;
	char buffer[256];
	socklen_t len = 0;
	struct sockaddr_in sa, ca;
	ssize_t b_len = 0;

	setbuf(stdout, NULL);
	s_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s_fd == -1)
		exit(errno);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(12345);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s_fd, (struct sockaddr *)&sa, sizeof(struct sockaddr_in)) == -1)
		exit(errno);
	if (listen(s_fd, 1) == -1)
		exit(errno);
	printf("Server listening on port 12345\n");
	len = (socklen_t)sizeof(struct sockaddr_in);
	c_fd = accept(s_fd, (struct sockaddr *)&ca, &len);
	if (c_fd == -1)
		exit(errno);
	printf("Client connected: %s\n", inet_ntoa(ca.sin_addr));
	printf("Message received: \"");
	b_len = recv(c_fd, buffer, 256, 0);
	while (b_len)
	{
		write(1, buffer, b_len);
		b_len = recv(c_fd, buffer, 256, 0);
	}
	printf("\"\n");
	close(c_fd);
	return (0);
}
