#include "signals.h"


/**
* handle_signal- func
* Return: int
*/
int handle_signal(void)
{
	if ((signal(SIGINT, signal_handler) == SIG_ERR))
		return (-1);
	return (0);
}


/**
* signal_handler- func
* @sig: int
* Return: void
*/
void signal_handler(int sig)
{
	printf("Gotcha! [%d]\n", sig);
}
