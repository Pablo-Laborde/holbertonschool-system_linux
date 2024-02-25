#include "signals.h"


/**
* current_handler_signal- func
* @x: int
* Return: void
*/
void (*current_handler_signal(void))(int)
{
	void (*handler)(int) = NULL;

	handler = signal(SIGINT, SIG_DFL);
	signal(SIGINT, handler);
	return (handler);
}
