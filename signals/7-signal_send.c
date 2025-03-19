#include "signals.h"


/**
* main- func
* @ac: int
* @av: char **
* Return: int
*/
int main(int ac, char **av)
{
	union sigval sv;

	if (ac != 2)
	{
		printf("Usage: %s <pid>\n", av[0]);
		fflush(stdout);
		return (EXIT_FAILURE);
	}
	if (sigqueue(atoi(av[1]), SIGINT, sv) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
