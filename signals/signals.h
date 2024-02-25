#ifndef SIGNALS_H
#define SIGNALS_H


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


int handle_signal(void);
void signal_handler(int sig);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);


#endif
