#include "sockets.h"


/**
* break_input - Breaks and prints the request.
* @msg: Input to break.
*/
void break_input(char *msg)
{
	char *a = NULL, *b = NULL;

	a = strdup(msg);
	if (!a)
		exit(errno);
	b = a;
	b = strtok(b, " \n");
	printf("Method: %s\n", b);
	b = strtok(NULL, " \n");
	printf("Path: %s\n", b);
	b = strtok(NULL, " \n");
	printf("Version: %s\n", b);
	free(a);
}
