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
	int status = 0, i = 0;
	char **cav = NULL;
	struct user_regs_struct data;

	cav = malloc(sizeof(char *) * ac);
	if (!cav)
		return (1);
	for (; i < (ac - 1); i++)
		cav[i] = av[i + 1];
	cav[i] = NULL;
	pid = fork();
	if (!pid)
	{
		ptrace(PTRACE_TRACEME, pid, NULL, NULL);
		execve(cav[0], cav, env);
	}
	else
	{
		while (waitpid(pid, &status, 0) && !WIFEXITED(status))
		{
			ptrace(PTRACE_GETREGS, pid, NULL, &data);
			if (data.orig_rax != -1)
				printf("%llu\n", data.orig_rax);
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		}
	}
	free(cav);
	return (0);
}
