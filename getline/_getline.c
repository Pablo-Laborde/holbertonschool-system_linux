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
	static char		buff[1024];

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
		if ((init < READ_SIZE) && ((buff[init] == '\n') || (buff[init] == '\0')))
		{
			if ((init < (READ_SIZE - 1)) && (buff[init] == '\n') && (buff[init + 1] == '\n'))
			{
				printf("\n");
			 	init++;
			}
			ready = 1;
			init++;
		}
		if (init >= READ_SIZE)
		{
			if (!ready)
				line_aux = line_ave;
			flag = 1;
		}
	}
	return (line_ave);
}


char* c_line(char* buff, int* p)
{
	int		init = *p,
				fine = *p,
				size = 0,
				j = 0;
	char*	line = NULL;

	while ((buff[fine]) && (fine < READ_SIZE) && (buff[fine] != '\n'))
		fine++;
	*p = fine;
	size = fine - init + 1;
	if (size > 1)
		line = malloc(size);
	if (line)
	{
		for (j = 0; j < (size - 1); j++)
			line[j] = buff[init + j];
		line[j] = '\0';
	}
	return (line);
}


char* two_in_one(char* s1, char* s2)
{
	int		size = 0,
				i = 0,
				j = 0,
				k = 0;
	char*	line = NULL;

	while (s1[i])
		i++;
	while (s2[j])
		j++;
	size = i + j - 1;
	line = malloc(size);
	if (line)
	{
		for (k = 0; k < (i - 1); k++)
			line[k] = s1[k];
		for (k = 0; k < j; k++)
			line[i + k] = s2[k];
		free(s1);
		free(s2);
	}
	return (line);
}
