#include "signals.h"

/**
* handle_sigaction- func
* Return: int
*/
int handle_sigaction(void)
{
	struct sigaction *act = NULL, *oldact = NULL;

	act = malloc(sizeof(struct sigaction));
	oldact = malloc(sizeof(struct sigaction));
	if (!act || !oldact)
		return (-1);
	act->sa_handler = signal_handler;
	return (sigaction(SIGINT, act, oldact));
}
