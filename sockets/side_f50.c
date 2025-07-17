#include "sockets.h"



/**
* print_ppq - Prints the path and queries individually.
* @arr: Array of strings to print.
*/
void print_ppq(char **arr)
{
	int i = 1;

	printf("Path: %s\n", arr[0]);
	for (; arr[i]; i += 2)
		printf("Query: \"%s\" -> \"%s\"\n", arr[i], arr[i + 1]);
}


/**
* spliter - Splits a string.
* @str: String to split.
* @delim: String with the delimeters.
* @n: Position number of the desired word.
* Return: Copy of the desired string.
*/
char *spliter(char *str, char *delim, int n)
{
	int i = 0;
	char *a = NULL, *b = NULL;

	a = strdup(str);
	if (!a)
		exit(errno);
	b = a;
	b = strtok(b, delim);
	for (; b && (i < n); i++)
		b = strtok(NULL, delim);
	if (!b)
		return (NULL);
	b = strdup(b);
	if (!b)
		exit(errno);
	free(a);
	return (b);
}


/**
* add_to_arr - Adds a new string at the end of the array.
* @arr: Array where the string is going to be added.
* @str: String to be added.
* @size: Size of arr (without the NULL termination).
* Return: Pointer to the beginning of the array of strings.
*/
char **add_to_arr(char **arr, char *str, int size)
{
	int i = 0;
	char **na = NULL;

	na = malloc((size + 1) * sizeof(char *));
	if (!na)
		exit(errno);
	for (; i < (size - 1); i++)
		na[i] = arr[i];
	na[i] = str;
	na[size] = NULL;
	free(arr);
	return (na);
}


/**
* ppq - Print the path and queries.
* @msg: Input to search for the path and queries.
* Return: Array with path and queries, NULL termianted.
*/
char **ppq(char *msg)
{
	int i = 0;
	char *a = NULL, *s = NULL, **arr = NULL;
	a = spliter(msg, " \r\n", 1);
	s = spliter(a, "?&=", i);
	while (s)
	{
		arr = add_to_arr(arr, s, i + 1);
		i++;
		s = spliter(a, "?&=", i);
	}
	free(a);
	return (arr);
}


/**
* free_arr - Frees array of strings.
* @arr: Array to be freed.
*/
void free_arr(char **arr)
{
	int i = 0;

	for (; arr[i]; i++)
		free(arr[i]);
	free(arr);
}
