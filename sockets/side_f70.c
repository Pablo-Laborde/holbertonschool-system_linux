#include "sockets.h"



/**
* get_input_2 - Retrieves input from client.
* @client_fd: Client file descriptor.
* Return: Input retrieved.
*/
char *get_input_2(int client_fd)
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
		if (blen < 255)
			break;
	}
	return (fmsg);
}


/**
* split_body - Splits the boy content.
* @rr: Raw request.
* Return: Array with body content.
*/
char **split_body(char *rr)
{
	char *a = NULL, *b = NULL, *c = NULL, **arr = NULL;
	int size = 0;

	a = strdup(rr);
	b = a;
	b = strtok(b, "\r\n");
	while (b)
	{
		c = b;
		b = strtok(NULL, "\r\n");
	}
	b = strdup(c);
	c = b;
	c = strtok(c, "=&");
	while (c)
	{
		size++;
		arr = add_to_arr(arr, strdup(c), size);
		c = strtok(NULL, "=&");
	}
	free(a);
	free(b);
	return (arr);
}


/**
* retrieve_path - Retrieves the path from raw input.
* @rr: Raw request.
* Return: Path as a string.
*/
char *retrieve_path(char *rr)
{
	char *a = NULL, *b = NULL, *c = NULL;

	a = strdup(rr);
	b = a;
	b = strtok(b, " \r\n");
	while (strcmp(b, "POST"))
		b = strtok(NULL, " \r\n");
	b = strtok(NULL, " \r\n");
	c = strdup(b);
	free(a);
	return (c);
}


/**
* print_bp - Print body parameters.
* @path: Path to print.
* @arr: Array of strings.
*/
void print_bp(char *path, char **arr)
{
	int i = 0;

	printf("Path: %s\n", path);
	for (; arr[i]; i += 2)
		printf("Body param: \"%s\" -> \"%s\"\n", arr[i], arr[i + 1]);
}
