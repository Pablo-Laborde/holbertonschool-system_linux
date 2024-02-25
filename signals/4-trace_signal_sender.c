#include "signals.h"


/**
* trace_signal_sender- func
* Return: int
*/
int trace_signal_sender(void)
{
	if (signal(SIGQUIT, sigfunc) == SIG_ERR)
		return (-1);
	return (0);
}


/**
* sigfunc- func
* @sig: int
* Return: void
*/
void sigfunc(int sig)
{
	(void) sig;

	printf("SIGQUIT sent by [%d]\n", getppid());
	fflush(stdout);
}
