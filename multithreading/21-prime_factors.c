#include "multithreading.h"



/**
* prime_factors - func
* @s: char const *
* Return: lsit_t *
*/
list_t *prime_factors(char const *s)
{
	unsigned long int n = 0, lim = 0, i = 2, *p = NULL;
	list_t *list = NULL;

	list = malloc(sizeof(list_t));
	list_init(list);
	n = strtol(s, NULL, 10);
	if (n < 2)
	{
		p = malloc(sizeof(unsigned long int));
		*p = n;
		list_add(list, (void *)p);
	}
	else
	{
		do {
			lim = n / 2;
			if (!(n % i))
			{
				p = malloc(sizeof(unsigned long int));
				*p = i;
				list_add(list, (void *)p);
				n /= i;
			}
			else
				i += (i == 2) ? 1 : 2;
		} while (i <= lim);
		if (n > 1)
		{
			p = malloc(sizeof(unsigned long int));
			*p = n;
			list_add(list, (void *)p);
		}
	}
	return (list);
}
