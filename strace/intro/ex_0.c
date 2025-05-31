#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int ac, char **av, char **env)
{
	pid_t pid = 0;
	int status = 0, i = 0;
	char **cav = NULL;

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
			printf("single step\n");
			ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
		}
		printf("Exit status: %d\n", WEXITSTATUS(status));
	}
	free(cav);
	return (0);
}
