#include "signals.h"


/**
* main- func
* @ac: int
* @av: char **
* Return: int
*/
int main(int ac, char **av)
{
	char *sigstr = NULL;

	if (ac != 2)
	{
		printf("Usage: %s <signum>\n", av[0]);
		return (EXIT_FAILURE);
	}
	sigstr = strsignal(atoi(av[1]));
	if (!sigstr)
		return (EXIT_FAILURE);
	printf("%s: %s\n", av[1], sigstr);
	return (EXIT_SUCCESS);
}
