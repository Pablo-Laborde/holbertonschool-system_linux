/*	ls program - excersie 0	*/

#include "ls.h"

/**
* main- function
* @ac: int
* @av: char**
* Return: int
*/
int main(int ac, char **av)
{
	int flags = 0, i = 1, af = 0, ap = 0;
	struct stat ss;

	af += set_flags(ac, av, &flags);
	if (ac - af - 1)
	{
		ap = manage_files(ac, av, flags);
		if (ac - af - 2)
			ap |= 1;
		for (i = 1; i < ac; i++)
		{
			if (!lstat(av[i], &ss) && (S_ISDIR(ss.st_mode) & 1))
			{
				(ap & 2) ? printf("\n") : (ap |= 2);
				if (ap & 1)
					printf("%s:\n", av[i]);
				print_dir(flags, av[i]);
			}
		}
	}
	else
		print_dir(flags, ".");
	return (errno);
}
