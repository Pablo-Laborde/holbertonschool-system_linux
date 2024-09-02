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


/**
* pf- func
* @path: char *
* @flags: int
* Return: void
*/
void pf(char *path, int flags)
{
	if (flags & 8)
	{
		printf("file info ");
	}
	printf("%s", path);
}


/**
* manage_files- func
* @flags: int
* @path: char *
* Return: void
*/
int manage_files(int ac, char **av, int flags)
{
	int i = 1, separator = 0, printed = 0;
	char sepc = ' ';
	struct stat ss;

	if ((flags & 1) || (flags & 8))
		sepc = '\n';
	for (; i < ac; i++)
		if ((lstat(av[i], &ss) == -1) && ((av[i][0] != '-') || !av[i][1]))
		{
			printf("./hls: cannot access '%s': No such file or directory\n", av[i]);
			printed |= 1;
		}
	for (i = 1; i < ac; i++)
	{
		if (!lstat(av[i], &ss) && !S_ISDIR(ss.st_mode))
		{
			(separator) ? printf("%c", sepc) : (separator = 1);
			pf(av[i], flags);
			printed |= 3;
		}
	}
	if (separator)
		printf("\n");
	return (printed);
}


/**
* print_dir- func
* @flags: int
* @path: char *
* Return: int
*/
int print_dir(int flags, char *path)
{
	int separator = 0;
	char sepc = ' ';
	DIR *dir = NULL;
	struct dirent *fd = NULL;

	dir = opendir(path);
	if (!dir)
		exit(errno);
	if ((flags & 1) || (flags & 8))
		sepc = '\n';
	fd = readdir(dir);
	while (fd)
	{
		if (fd->d_name[0] != '.')
		{
			(separator) ? printf("%c", sepc) : (separator = 1);
			pf(fd->d_name, flags);
		}
		fd = readdir(dir);
	}
	if (separator)
		printf("\n");
	closedir(dir);
	return (1);
}


/**
* set_flags- func
* @ac: int *
* @av: char **
* @flags: int *
* Return: int
*/
int set_flags(int ac, char **av, int *flags)
{
	int i = 1, amo = 0;

	/*
		1	=	1
		2	=	a
		4	=	A
		8	=	l
	*/
	for (; i < ac; i++)
		if ((av[i][0] == '-') && (av[i][1] != '\0'))
		{
			if (av[i][1] == '1')
				*flags |= 1;
			else if (av[i][1] == 'a')
				*flags |= 2;
			else if (av[i][1] == 'A')
				*flags |= 4;
			else if (av[i][1] == 'l')
				*flags |= 8;
			else
			{
				printf("hls: invalid option -- '%c'\n", av[i][1]);
				printf("Try 'hls --help' for more information.\n");
				exit(errno);
			}
			amo++;
		}
	return (amo);
}
