#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "syscall.h"



/**
* syscall_name - func
* @no: unsigned long
* Return: char *
*/
char *syscall_name(unsigned long no)
{
	return ((char *)((no == syscalls_64_g[no].nr) ?
			syscalls_64_g[no].name : syscalls_32_g[no].name));
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
	struct user_regs_struct data;

	if (ac < 2)
	{
		printf("usage: ./strace_2 command_path args\n");
		return (1);
	}
	setbuf(stdout, NULL);
	pid = fork();
	if (!pid)
	{
		ptrace(PTRACE_TRACEME, pid, NULL, NULL);
		execve(av[1], av + 1, env);
	}
	waitpid(pid, &status, 0);
	ptrace(PTRACE_GETREGS, pid, NULL, &data);
	if ((long)data.orig_rax != -1)
		printf("%s = %#llx\n", syscall_name(data.orig_rax), data.rax);
	while (!WIFEXITED(status))
	{
		/* Step to syscall exit */
		ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		waitpid(pid, &status, 0);
		ptrace(PTRACE_GETREGS, pid, NULL, &data);
		if ((long)data.orig_rax != -1)
			printf("%s", syscall_name(data.orig_rax));
		/* Step to next syscall entry */
		ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		waitpid(pid, &status, 0);
		ptrace(PTRACE_GETREGS, pid, NULL, &data);
		if ((long)data.orig_rax != -1)
		{
			if (data.rax == (unsigned long long)-38)
				printf(" = ?\n");
			else
				printf(" = %#llx\n", data.rax);
		}
	}
	return (0);
}
