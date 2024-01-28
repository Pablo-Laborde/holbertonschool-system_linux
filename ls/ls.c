/*	ls program - excersie 0	*/

#include "ls.h"

/**
* main- function
* @ac: int
* @av: char**
* @env: char**
* Return: int
*/
int main(int ac, char **av, char **env)
{
	int pos = 0, mode = 0;
	char *dirpath = NULL, *filename = NULL;
	DIR *directory = NULL;

	/*	get the path -> pass to disdir	*/
	if (ac == 1)
	{
		tosum(env, dirpath, filename, filename, mode);
		printf("\n");
	}
	else
	{
		/*	read each path or filename from av	*/
		for (pos = 1; pos < ac; pos++)
		{
			mode = 0;
			directory = dirch(av[pos]);
			if (directory)
			{
				if (ac > 2)
					printf("%s:\n", av[pos]);
				pdf(directory, av[pos], filename, mode);
			}
			else
			{
				dirpath = folch(av[pos], &filename, &mode);
				tosum(env, dirpath, filename, av[pos], mode);
			}
			printf("\n");
			if ((ac > 2) && (pos < ac - 1))
				printf("\n");
		}
	}
	closedir(directory);
	return (errno);
}


/**
* pdf- function
* @dir: DIR*
* @dp: char*
* @fn: char*
* @mode: int
* Return: int
*/
int pdf(DIR *dir, char *dp, char *fn, int mode)
{
	struct dirent *rd = NULL;

	if (dir)
	{
		while ((rd = readdir(dir)))
		{
			if (!fn)
			{
				if (rd->d_name[0] != '.')
					printf("%s\t", rd->d_name);
			}
			else
				if (!strc(rd->d_name, fn))
				{
					if (mode == 1)
						printf("%s/", dp);
					printf("%s\t", rd->d_name);
				}
		}
	}
	return (errno);
}


/**
* folch- function
* @str: char*
* @filename: char**
* @mode: int*
* Return: char*
*/
char *folch(char *str, char **filename, int *mode)
{
	int i = 0, j = 0, slashpos = 0;
	char *foldername = NULL;

	if (str)
	{
		while (str[i])
		{
			if (str[i] == '/')
				slashpos = i;
			i++;
		}
		if (slashpos > 0)
		{
			if ( (foldername = malloc(slashpos + 1)) )
			{
				for (j = 0; j < slashpos; j++)
					foldername[j] = str[j];
				foldername[j] = '\0';
			}
			*filename = &str[slashpos + 1];
			*mode = 1;
		}
	}
	return (foldername);
}


/**
* dirch- function
* @path: char*
* Return: DIR*
*/
DIR *dirch(char *path)
{
	DIR *directory = NULL;

	directory = opendir(path);
	return (directory);
}


/**
* getpath- function
* @env: char**
* Return: char*
*/
char *getpath(char **env)
{
	int j = 0, pos = 0;

	/*	get the current pwd	*/
		while (!pwdch(env[j]))
			j++;
		/*	printf("%s\n", env[j]);	*/
	while (env[j][pos] != '=')
		pos++;
	/*	printf("%s\n", &env[j][pos + 1]);	*/
	return (&(env[j][pos + 1]));
}


/**
* pwdch- function
* @str: char*
* Return: int
*/
int pwdch(char *str)
{
	int pos = 0, flag = 1;
	char *name = "PWD";

	while (name[pos])
	{
		if (str[pos] != name[pos])
			flag *= 0;
		pos++;
	}
	return (flag);
}


/**
* strc- function
* @str1: char*
* @str2: char*
* Return: int
*/
int strc(char *str1, char *str2)
{
	int i = 0, eq = 0;

	if (str1 && str2)
		do
		{
			if (str1[i] != str2[i])
				eq = 1;
			i++;
			if ((str1[i] && !str2[i]) || (!str1[i] && str2[i]))
				eq = 1;
		}	while (str1[i] && str2[i]);
	return (eq);
}
