#include "_getline.h"


/**
* _getline- function
* @fd: int
* Return: char*
*/
char *_getline(const int fd) {
	static char
		buff[READ_SIZE];
	static int
		pos = 0;
	ssize_t
		ar = 0;
	int
		i = pos,
		len = 0,
		flag = 1;
	char
		*str = NULL,
		*aux = NULL;

	(void)ar;
	(void)aux;
	if (flag) {
		ar = read(fd, buff, READ_SIZE);
		flag = 0;
	}
	if (buff[i]) {
		while (buff[pos]) {
			if (buff[pos] == '\n')
				break;
			pos++;
		}
		len = pos - i + 1;
		str = cpy_string(&buff[i], len);
		if (str[len - 1] == '\n')
			str[len - 1] = '\0';
		if (buff[pos])
			pos++;
	}
	return (str);
}


/**
* join_strings- function
* @str1: char*
* @str2: char*
* Return: char*
*/
char *join_strings(char *str1, char *str2) {
	int
		i = 0,
		len1 = 0,
		len2 = 0;
	char
		*new_str = NULL;

	if (str1 && str2) {
		while (str1[len1])
			len1++;
		while (str2[len2])
			len2++;
		new_str = malloc(len1 + len2 + 1);
		if (new_str) {
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
char *cpy_string(char *str, int amt) {
	int
		i = 0;
	char
		*new_str = NULL;

	if (str) {
		new_str = malloc(amt + 1);
		if (new_str) {
			for (; i < amt; i++)
				new_str[i] = str[i];
			new_str[i] = '\0';
		}
	}
	return (new_str);
}
