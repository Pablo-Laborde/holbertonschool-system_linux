#include "ls.h"



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
		perm[1] = (ss->st_mode & S_IRUSR) ? 'r' : '-';
		perm[2] = (ss->st_mode & S_IWUSR) ? 'w' : '-';
		perm[3] = (ss->st_mode & S_IXUSR) ? 'x' : '-';
		/* group perm */
		perm[4] = (ss->st_mode & S_IRGRP) ? 'r' : '-';
		perm[5] = (ss->st_mode & S_IWGRP) ? 'w' : '-';
		perm[6] = (ss->st_mode & S_IXGRP) ? 'x' : '-';
		/* other perm */
		perm[7] = (ss->st_mode & S_IROTH) ? 'r' : '-';
		perm[8] = (ss->st_mode & S_IWOTH) ? 'w' : '-';
		perm[9] = (ss->st_mode & S_IXOTH) ? 'x' : '-';
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
	*	1	=	1
	*	2	=	a
	*	4	=	A
	*	8	=	l
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
