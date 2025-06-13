#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "syscall.h"



/**
* cp_av - func
* @ac: int
* @av: char **
* Return: char **
*/
char **cp_av(int ac, char **av)
{
	char **cav = NULL;
	int i = 0;

	cav = malloc(sizeof(char *) * ac);
	if (!cav)
		exit(1);
	for (; i < (ac - 1); i++)
		cav[i] = av[i + 1];
	cav[i] = NULL;
	return (cav);
}


/**
* main - func
* @ac: int
* @av: char **
* @env: char **
* Return: int
*/
int main(int ac, char **av, char **env)
{
	pid_t pid = 0;
	int status = 0;
	char **cav = NULL;
	struct user_regs_struct data;

	cav = cp_av(ac, av);
	pid = fork();
	if (!pid)
	{
		ptrace(PTRACE_TRACEME, pid, NULL, NULL);
		execve(cav[0], cav, env);
	}
	waitpid(pid, &status, 0);
	ptrace(PTRACE_GETREGS, pid, NULL, &data);
	if (data.orig_rax != -1)
	{
		printf("%llu\n", data.orig_rax);
		fflush(NULL);
	}
	while (!WIFEXITED(status))
	{
		/* Step to syscall exit */
		ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		waitpid(pid, &status, 0);
		ptrace(PTRACE_GETREGS, pid, NULL, &data);
		if (data.orig_rax != -1)
		{
			printf("%llu\n", data.orig_rax);
			fflush(NULL);
		}
		/* Step to next syscall entry */
		ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		waitpid(pid, &status, 0);
	}
	free(cav);
	return (0);
}

/*
* There was a problem in which the execve output was printed before the syscall
* number in some cases. That wassolved forcing output with the fflush(NULL),
* it could have been solved with setbuf(stdout, _IONBF) too.
*/
