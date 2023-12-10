/* ls program - excersie 0 */

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
	/* First Step: get the current pwd */
	int		pos = 0;
	int		j = 0;
	char*	path = NULL;
	DIR* directory = NULL;
	struct	dirent* rd = NULL;


	(void)ac;
	(void)av;
	while (env[j])
	{
		if (pwdch(env[j]))
			pos = j;
		j++;
	}
	/* printf("%s\n", env[pos]); */

	/* Second Step: get the path */
	path = getpath(env[pos]);
	/* printf("%s\n", path); */

	/* Third Step: open -> read -> close stream */
	directory = opendir(path);
	if (directory)
	{
		while ( (rd = readdir(directory)) )
		{
			/*
			printf("%lu\n" ,rd->d_ino);
			printf("%lu\n" ,rd->d_off);
			printf("%hu\n" ,rd->d_reclen);
			printf("%d\n" ,rd->d_type);
			*/
			if (rd->d_name[0] != '.')
				printf("%s\t", rd->d_name);
		}
		closedir(directory);
		printf("\n");
	}
	else
		printf("fail\n");
	return (0);
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
