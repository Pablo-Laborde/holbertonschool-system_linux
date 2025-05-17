#include "multithreading.h"



pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


/**
* mutex_create - func
*/
__attribute__((constructor)) void mutex_create(void)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
}


/**
* mutex_destroy - func
*/
__attribute__((destructor)) void mutex_destroy(void)
{
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}



/**
* prime_factors - func
* @s: char const *
* Return: lsit_t *
*/
list_t *prime_factors(char const *s)
{
	pthread_t tid;

	pthread_cond_wait(&cond, &mutex);
	pthread_mutex_lock(&mutex);
	tid = pthread_self();
	printf("[%ld] = ", tid);
	prime(strtoul(s, NULL, 10));
	pthread_mutex_unlock(&mutex);
	return (0);
}


/**
* prime - func
* @n: unsigned long
*/
void prime(unsigned long int n)
{
	unsigned long int aux = n, lim = n / 2, i = 2;
	int flag = 0;

	while (i <= lim)
	{
		if (!(aux % i))
		{
			(flag) ? (printf(" * ")) : (flag = 1);
			printf("%lu", i);
			aux /= i;
		}
		else
			i++;
	}
	printf("\n");
}
