#include "_getline.h"


/**
* _getline- function
* @fd: int
* Return: char*
*/
char *_getline(const int fd)
{
	static char buff[READ_SIZE];
	static int pos;
	static ssize_t ar;
	int i = pos, len = 0, cl = 0;
	char *str = NULL, *aux = NULL;

	if (fd == -1)
	{
		pos = 0;
		ar = 0;
	}
	while ((pos < ar) || ((ar = read(fd, buff, READ_SIZE)) && ar > 0))
	{
		if (!(pos < ar))
			pos = 0;
		i = pos;
		pos = end_line(buff, pos, ar);
		len = pos - i + 1;
		if (!(pos < ar))
			len--;
		else
		{
			pos++;
			cl = 1;
		}
		aux = cpy_string(&buff[i], len);
		if (aux)
		{
			if (aux[len - 1] == '\n')
				aux[len - 1] = '\0';
			if (str)
				str = join_strings(str, aux);
			else
				str = aux;
			aux = NULL;
		}
		if (cl)
			break;
	}
	return (str);
}


/**
* end_line- function
* @str: char*
* @pos: int
* @ar: int
* Return: int
*/
int end_line(char *str, int pos, int ar)
{
	int
		i = pos;

	while (str[i] && (str[i] != '\n') && (i < ar))
		i++;
	return (i);
}


/**
* join_strings- function
* @str1: char*
* @str2: char*
* Return: char*
*/
char *join_strings(char *str1, char *str2)
{
	int
		i = 0,
		len1 = 0,
		len2 = 0;
	char
		*new_str = NULL;

	if (str1 && str2)
	{
		while (str1[len1])
			len1++;
		while (str2[len2])
			len2++;
		new_str = malloc(len1 + len2 + 1);
		if (new_str)
		{
			for (; i < len1; i++)
				new_str[i] = str1[i];
			for (i = 0; i < len2; i++)
				new_str[i + len1] = str2[i];
			new_str[len1 + len2] = '\0';
			free(str1);
			free(str2);
		}
	}
	return (new_str);
}


/**
* cpy_string- function
* @str: char*
* @amt: int, doesn't take into account the '\0'
* Return: char*
*/
char *cpy_string(char *str, int amt)
{
	int
		i = 0;
	char
		*new_str = NULL;

	if (str)
	{
		new_str = malloc(amt + 1);
		if (new_str)
		{
			for (; i < amt; i++)
				new_str[i] = str[i];
			new_str[i] = '\0';
		}
	}
	return (new_str);
}
