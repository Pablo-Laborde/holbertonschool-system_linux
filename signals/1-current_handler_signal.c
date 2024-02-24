#include "signals.h"


/**
* current_handler_signal- func
* @x: int
* Return: void
*/
void (*current_handler_signal(void))(int)
{
	return (signal_handler);
}
