#include <signal.h>
#include <unistd.h>


/**
* pid_exist- func
* @pid: pid_t
* Return: int
*/
int pid_exist(pid_t pid)
{
	return (!kill(pid, SIGCONT)? 1 : 0);
}
