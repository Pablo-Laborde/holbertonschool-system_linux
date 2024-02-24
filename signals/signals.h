#ifndef SIGNALS_H
#define SIGNALS_H


#include <signal.h>
#include <stdio.h>


int handle_signal(void);
void signal_handler(int sig);
void (*current_handler_signal(void))(int);


#endif
