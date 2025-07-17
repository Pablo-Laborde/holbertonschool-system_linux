#include "sockets.h"



/**
* print_ha - Prints array of headers.
* @arr: Array to be printed.
*/
void print_ha(char **arr)
{
	int i = 0;

	for (; arr[i]; i += 2)
		printf("Header: \"%s\" -> \"%s\"\n", arr[i], arr[i + 1]);
}


/**
* ha - Creates a header array.
* @msg: Input.
* Return: Array of strings.
*/
char **ha(char *msg)
{
	int hi = 1, pos = 0, size = 0;
	char *a = NULL, *s = NULL, *q = NULL, **arr = NULL;

	a = spliter(msg, "\r\n", hi);
	while (a)
	{
		pos = 0;
		s = spliter(a, " ", pos);
		while (s)
		{
			size++;
			if (pos == 0)
			{
				q = spliter(s, ":", 0);
				free(s);
			}
			else
				q = s;
			arr = add_to_arr(arr, q, size);
			pos++;
			s = spliter(a, " ", pos);
		}
		free(a);
		hi++;
		a = spliter(msg, "\r\n", hi);
	}
	free(a);
	return (arr);
}
