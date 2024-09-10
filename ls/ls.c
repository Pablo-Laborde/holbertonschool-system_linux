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
* @name: char *
* @flags: int
* @ss: struct stat *
* Return: void
*/
void pf(char *name, int flags, struct stat *ss)
{
	int tpr = 0;
	char perm[11], *time = NULL;
	struct passwd *pwd;
	struct group *grp;

	if (flags & 8)
	{
		/* directory or regular */
		perm[0] = (S_ISDIR(ss->st_mode)) ? 'd' : '-';
		/* user perm */
		perm[1] = (S_IRUSR & ss->st_mode) ? 'r' : '-';
		perm[2] = (S_IWUSR & ss->st_mode) ? 'w' : '-';
		perm[3] = (S_IXUSR & ss->st_mode) ? 'x' : '-';
		/* group perm */
		perm[4] = (S_IRGRP & ss->st_mode) ? 'r' : '-';
		perm[5] = (S_IWGRP & ss->st_mode) ? 'w' : '-';
		perm[6] = (S_IXGRP & ss->st_mode) ? 'x' : '-';
		/* other perm */
		perm[7] = (S_IROTH & ss->st_mode) ? 'r' : '-';
		perm[8] = (S_IWOTH & ss->st_mode) ? 'w' : '-';
		perm[9] = (S_IXOTH & ss->st_mode) ? 'x' : '-';
		perm[10] = '\0';
		pwd = getpwuid(ss->st_uid);
		grp = getgrgid(ss->st_gid);
		time = ctime(&(ss->st_mtime));
		printf("%s %ld %s %s %ld "
		, perm, ss->st_nlink, pwd->pw_name, grp->gr_name, ss->st_size);
		for (tpr = 4; tpr < 16; tpr++)
			printf("%c", time[tpr]);
		printf(" ");
	}
	printf("%s", name);
}


/**
* manage_files- func
* @ac: int
* @av: char **
* @flags: int
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
			printf("./hls: cannot access %s: No such file or directory\n",
				av[i]);
			printed |= 1;
		}
	for (i = 1; i < ac; i++)
	{
		if (!lstat(av[i], &ss) && !S_ISDIR(ss.st_mode))
		{
			(separator) ? printf("%c", sepc) : (separator = 1);
			pf(av[i], flags, &ss);
			printed |= 3;
		}
	}
	if (separator)
		printf("\n");
	return (printed);
}


/**
* check_condition- func
* @flags: int
* @fn: char *
* Return: int
*/
int check_condition(int flags, char *fn)
{
	if (fn[0] != '.')
		return (1);
	if (flags & 4)
	{
		if (!fn[1])
			return (0);
		if ((fn[1] == '.') && !fn[2])
			return (0);
		return (1);
	}
	if (flags & 2)
		return (1);
	return (0);
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
	struct stat ss;

	dir = opendir(path);
	if (!dir)
		exit(errno);
	if ((flags & 1) || (flags & 8))
		sepc = '\n';
	fd = readdir(dir);
	while (fd)
	{
		if (check_condition(flags, fd->d_name))
		{
			(separator) ? printf("%c", sepc) : (separator = 1);
			lstat(fd->d_name, &ss);
			pf(fd->d_name, flags, &ss);
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
