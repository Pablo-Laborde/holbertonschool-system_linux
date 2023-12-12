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
	int		j = 0;
	char*	path = NULL;
	DIR*	directory = NULL;

	/*	get the path -> pass to disdir	*/
	if (ac == 1)
	{
		path = getpath(env);
		directory = dirch(path);
		dirdis(directory, NULL);
	}
	else
	{
		/*	read each path or filename from av	*/
		for (pos = 1; pos < ac; pos++)
		{
			directory = dirch(av[pos]);
			if (directory)
				dirdis(directory, NULL);
			else
			{
				path = getpath(env);
				directory = dirch(path);
				reclist(directory, av[pos]);
			}
			closedir(directory);
		}
	}
	return (errno);
}


/**
* dirdis- function
* @directory: DIR*
* @filename: char*
* Return: int
*/
int dirdis(DIR*	directory, char* filename)
{
	char*	errmsg = NULL;
	struct	dirent*	rd = NULL;

	/*	read & print -> close stream	*/
	if (directory)
	{
		if (!filename)
		{
			while ( (rd = readdir(directory)) )
			{
				//if (rd->d_type == 4)
				//	printf("%s:\n", rd->d_name);
				// printf("%lu\n" ,rd->d_ino);
				// printf("%lu\n" ,rd->d_off);
				// printf("%hu\n" ,rd->d_reclen);
				// printf("%d\n" ,rd->d_type);
				//if (rd->d_name[0] != '.')
					printf("%s\t", rd->d_name);
			}
			printf("\n");
		}
		// else
		// {

		// }
	}
	// else if ()
	// {}
	else
	{
		errmsg = strerror(errno);
		printf("%s\n", errmsg);
	}
	return (errno);
}


/**
* reclist- function
* @directory: DIR*
* @filename: char*
* Return: int
*/
void reclist(DIR* directory, char* filename)
{
	struct	dirent*	rd = NULL;

	rd = readdir(directory);
	if (rd)
	{
		reclist(directory, filename);
		if ((!filename) || (!strcmp(filename, rd->d_name)))
			printf("%s\n", rd->d_name);
	}
	return;
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
	int		j = 0;
	int		pos = 0;

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
	int		pos = 0;
	int		flag = 1;
	char*	name = "PWD";

	while (name[pos])
	{
		if (str[pos] != name[pos])
			flag *= 0;
		pos++;
	}
	return (flag);
}
