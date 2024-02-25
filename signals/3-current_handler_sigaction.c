#include "signals.h"


/**
* current_handler_sigaction- func
* Return: void
*/
void (*current_handler_sigaction(void))(int)
{
	void (*sighandler)(int) = NULL;

	struct sigaction *act = NULL, *oldact = NULL;

	act = malloc(sizeof(struct sigaction));
	oldact = malloc(sizeof(struct sigaction));
	if (!act || !oldact)
		return (NULL);
	act->sa_handler = SIG_DFL;
	sigaction(SIGINT, act, oldact);
	sighandler = oldact->sa_handler;
	sigaction(SIGINT, oldact, act);
	return (sighandler);
}
