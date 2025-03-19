#include "signals.h"


/**
* trace_signal_sender- func
* Return: int
*/
int trace_signal_sender(void)
{
	struct sigaction sa;

	sa.sa_sigaction = sigfunc;
	sa.sa_flags = SA_SIGINFO;
	return (sigaction(SIGQUIT, &sa, NULL));
}


/**
* sigfunc- func
* @sig: int
* @info: siginfo_t *
* @ucontext: void *
* Return: void
*/
void sigfunc(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;

	printf("SIGQUIT sent by [%d]\n", info->si_pid);
	fflush(stdout);
}
