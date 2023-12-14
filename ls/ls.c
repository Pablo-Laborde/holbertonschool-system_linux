/*	ls program - excersie 0	*/

#include "ls.h"

/**
* main- function
* @ac: int
* @av: char**
* @env: char**
* Return: int
*/
int main(int ac, char** av, char** env)
{
	int		pos = 0;
	char*	path = NULL,
		*	dirpath = NULL,
		*	filename = NULL;
	DIR*	directory = NULL;

	/*	get the path -> pass to disdir	*/
	if (ac == 1)
	{
		path = getpath(env);
		directory = dirch(path);
		pdf(directory, filename);
		printf("\n");
	}
	else
	{
		/*	read each path or filename from av	*/
		for (pos = 1; pos < ac; pos++)
		{
			directory = dirch(av[pos]);
			if (directory)
			{
				pdf(directory, filename);
			}
			else
			{
				dirpath = folch(av[pos], &filename);
				if (dirpath)
				{
					directory = dirch(dirpath);
					pdf(directory, filename);
					free(dirpath);
				}
				else
				{
					path = getpath(env);
					directory = dirch(path);
					pdf(directory, av[pos]);
				}
			}
			closedir(directory);
			printf("\n");
		}
	}
	return (errno);
}


int pdf(DIR* dir, char* fn)
{
	struct	dirent*	rd = NULL;

	if (dir)
	{
		while ( (rd = readdir(dir)) )
		{
			/*
			printf("%s:\n", rd->d_name);
			printf("%lu\n" ,rd->d_ino);
			printf("%lu\n" ,rd->d_off);
			printf("%hu\n" ,rd->d_reclen);
			printf("%d\n" ,rd->d_type);
			printf("%s\n", rd->d_name);
			*/
			if (!fn)
			{
				if (rd->d_name[0] != '.')
					printf("%s\t", rd->d_name);
			}
			else
				if (!strc(rd->d_name, fn))
					printf("%s\t", rd->d_name);
		}
	}
	return (errno);
}


/**
* folch- function
* @str: char*
* Return: char*
*/
char* folch(char* str, char** filename)
{
	int		i = 0,
			j = 0,
			slashpos = 0;
	char*	foldername = NULL;

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
		}
	}
	return (foldername);
}


/**
* dirch- function
* @path: char*
* Return: DIR*
*/
DIR* dirch(char* path)
{
	DIR*	directory = NULL;

	directory = opendir(path);
	return (directory);
}


/**
* getpath- function
* @env: char**
* Return: char*
*/
char* getpath(char** env)
{
	int		j = 0,
			pos = 0;

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
int pwdch(char* str)
{
	int		pos = 0,
			flag = 1;
	char*	name = "PWD";

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
int strc(char* str1, char* str2)
{
	int		i = 0,
			eq = 0;

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
