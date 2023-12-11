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

	printf("%d\n", errno);
	/*	get the path -> pass to disdir	*/
	if (ac == 1)
	{
		/*	get the current pwd	*/
		while (env[j])
		{
			if (pwdch(env[j]))
				pos = j;
			j++;
		}
		/*	printf("%s\n", env[pos]);	*/
		path = getpath(env[pos]);
		/*	printf("%s\n", path);	*/
		dirdis(path);
	}
	else
	{
		/*	read each path from av	*/
		for (pos = 1; pos < ac; pos++)
		{
			if (pos > 1)
				printf("\n");
			printf("%s:\n", av[pos]);
			dirdis(av[pos]);
		}
	}

	return (errno);
}


/**
* dirdis- function
* @path: int
* Return: int
*/
int dirdis(char* path)
{
	DIR* directory = NULL;
	struct	dirent* rd = NULL;

	/*	open -> read & print -> close stream	*/
	directory = opendir(path);
	if (directory)
	{
		while ( (rd = readdir(directory)) )
		{
			/*	printf("%lu\n" ,rd->d_ino);
				printf("%lu\n" ,rd->d_off);
				printf("%hu\n" ,rd->d_reclen);
				printf("%d\n" ,rd->d_type);	*/
			if (rd->d_name[0] != '.')
				printf("%s\t", rd->d_name);
		}
		closedir(directory);
		printf("\n");
	}
	else
	{
		/*	print errors	*/
		printf("%d\n", errno);
	}
}


/**
* pwdch- function
* @str: int
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


/**
* getpath- function
* @str: int
* Return: char*
*/
char* getpath(char* str)
{
	int		pos = 0;

	while (str[pos] != '=')
		pos++;
	return (&(str[pos + 1]));
}
