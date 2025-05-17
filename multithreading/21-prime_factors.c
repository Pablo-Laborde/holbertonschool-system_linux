#include "multithreading.h"



/**
* prime_factors - func
* @s: char const *
* Return: lsit_t *
*/
list_t *prime_factors(char const *s)
{
	unsigned long int n = 0, lim = 0, i = 0, *p = NULL;
	list_t *list = NULL;

	list = malloc(sizeof(list_t));
	if (!list)
		exit(1);
	list_init(list);
	n = strtol(s, NULL, 10);
	lim = n / 2;
	while ((i <= lim) && (i <= n))
	{
		if (i < 2)
			i = 2;
		if (!(n % i))
		{
			p = malloc(sizeof(unsigned long int));
			if (!p)
				exit(1);
			*p = i;
			list_add(list, (void *)p);
			n /= i;
		}
		else
			i++;
	}
	return (list);
}
