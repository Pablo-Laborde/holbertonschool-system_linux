#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>


int main(void)
{
    char *s = "Hello World!";
    pid_t pid;

    pid = getpid();
    while (1)
    {
        printf("%s ->%d    %p\n", s, pid, s);
        sleep(2);
    }
    return (0);
}
