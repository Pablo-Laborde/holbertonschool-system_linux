/*	ls program - excersie 0	*/

#include "ls.h"


/**
* tosum- func
* @env: char**
* @dirpath: char*
* @filename: char*
* @av: char*
* @mode: int
* Return: void
*/
void tosum(char **env, char *dirpath, char *filename, char *av, int mode)
{
	char *path = NULL;
	DIR *directory = NULL;

	if (dirpath)
	{
		directory = dirch(dirpath);
		pdf(directory, dirpath, filename, mode);
		free(dirpath);
	}
	else
	{
		path = getpath(env);
		directory = dirch(path);
		pdf(directory, path, av, mode);
	}
	closedir(directory);
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
		do {
			if (str1[i] != str2[i])
				eq = 1;
			i++;
			if ((str1[i] && !str2[i]) || (!str1[i] && str2[i]))
				eq = 1;
		}	while (str1[i] && str2[i]);
	return (eq);
}

