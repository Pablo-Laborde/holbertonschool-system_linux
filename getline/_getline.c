#include "_getline.h"


/**
* _getline- function
* @fd: int
* Return: char*
*/
char *_getline(const int fd)
{
	static int		flag = 1;
	static int		init = 0;
	static char		buff[READ_SIZE];

	int 	ready = 0;
	char*	line_ave = NULL,
			*	line_aux = NULL;

	while (!ready)
	{
		if (flag)
		{
			read(fd, buff, READ_SIZE);
			init = 0;
			flag = 0;
		}
		line_ave = c_line(buff, &init);
		if (line_aux)
		{
			line_ave = two_in_one(line_aux, line_ave);
			line_aux = NULL;
		}
		
		else
		{
			line_aux = line_ave;
			flag = 1;
		}
	}
	return (line_ave);
}


/**
* c_line- function
* @buff: char*
* @p: int*
* Return: char*
*/
char* c_line(char* buff, int* p)
{
	int		init = *p,
				fine = *p,
				size = 0,
				j = 0;
	char*	line = NULL;

	while ((fine < READ_SIZE) && (buff[fine]) && (buff[fine] != '\n'))
		fine++;
	while ((fine < READ_SIZE) && (buff[fine] == '\n'))
		fine++;
	size = fine - init + 1;
	*p = fine;
	line = malloc(size);
	if (line)
	{
		for (j = 0; j < (size - 1); j++)
			line[j] = buff[init + j];
		line[j] = '\0';
	}
	return (line);
}


/**
* two_in_one- function
* @s1: char*
* @s2: char*
* Return: char*
*/
char* two_in_one(char* s1, char* s2)
{
	int		size = 0,
				i = 0,
				j = 0,
				k = 0;
	char*	line = NULL;

	if (!s2)
		return (s1);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	size = i + j - 1;
	line = malloc(size);
	if (line)
	{
		for (k = 0; k < i; k++)
			line[k] = s1[k];
		for (k = 0; k < j; k++)
			line[i + k] = s2[k];
		free(s1);
		free(s2);
	}
	return (line);
}


/**
* two_in_one- function
* @line: char*
* Return: int
*/
int line_trn(char* line)
{
	int		i = 0,
				flag = 0;

	if (line)
	{
		while (line[i])
		{
			i++;
			if (line[i] == '\n')
				flag = 1;
		}
		if ((i > 0) && (line[i - 1] == '\n'))
			line[i - 1] = '\0';
	}
return (flag);
}
