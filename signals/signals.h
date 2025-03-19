#ifndef SIGNALS_H
#define SIGNALS_H


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include <unistd.h>


int handle_signal(void);
void signal_handler(int sig);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);

/* ex 4 */
int trace_signal_sender(void);
void sigfunc(int sig, siginfo_t *info, void *ucontext);

void sigIntFunc(int sig);
int pid_exist(pid_t pid);


#endif
