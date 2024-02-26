#include "signals.h"


/**
* main- func
* Return: int
*/
int main(void)
{
	if (signal(SIGINT, sigIntFunc) == SIG_ERR)
		return (EXIT_FAILURE);
	pause();
	printf("Signal received\n");
	fflush(stdout);
	return (EXIT_SUCCESS);
}


/**
* sigIntFunc- func
* @sig: int
* Return: void
*/
void sigIntFunc(int sig)
{
	printf("Caught %d\n", sig);
	fflush(stdout);
}
