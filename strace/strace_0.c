#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "syscall.h"



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
	struct user_regs_struct data;

	if (ac < 2)
		printf("usage: ./strace_1 command_path args\n"), return (1);
	pid = fork();
	if (!pid)
	{
		ptrace(PTRACE_TRACEME, pid, NULL, NULL);
		execve(av[1], av + 1, env);
	}
	waitpid(pid, &status, 0);
	ptrace(PTRACE_GETREGS, pid, NULL, &data);
	if ((long)data.orig_rax != -1)
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
		if ((long)data.orig_rax != -1)
		{
			printf("%llu\n", data.orig_rax);
			fflush(NULL);
		}
		/* Step to next syscall entry */
		ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		waitpid(pid, &status, 0);
	}
	return (0);
}

/*
* There was a problem in which the execve output was printed before the syscall
* number in some cases. That wassolved forcing output with the fflush(NULL),
* it could have been solved with setbuf(stdout, NULL) too.
*/
