#include "hnm.h"


/**
* main- func
* @ac: int
* @av: char **
* Return: int
*/
int main(int ac, char **av)
{
	int fd = 0, i = 1;

	if (ac == 1)
	{
		fd = open("a.out", O_RDONLY);
		elf_handler(fd);
		close(fd);
	}
	else
	{
		for (; i < ac; i++)
		{
			fd = open(av[i], O_RDONLY);
			if (fd != -1)
			{
				elf_handler(fd);
				close(fd);
			}
		}
	}
	return (EXIT_SUCCESS);
}


/**
* elf_handler- func
* @fd: int
* Return: void
*/
void elf_handler(int fd)
{
	char head[16];

	read(fd, head, (sizeof(char) * 16));
	if (head[0] != EI_MAG0)
		return;
	if (head[1] != EI_MAG1)
		return;
	if (head[2] != EI_MAG2)
		return;
	if (head[3] != EI_MAG3)
		return;
	if (head[3] == ELFCLASS32)
		manage_32(fd);
}
