#include "multithreading.h"

PTHREAD_MUTEX_INITIALIZER
PTHREAD_COND_INITIALIZER

/**
* tprintf - func
* @format: char const *
* Return: int
*/
int tprintf(char const *format, ...)
{
	pthread_cond_wait(&cond, &mutex);
	printf("%s", format);
	return (0);
}


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
__attribute__((constructor)) void mutex_destroy(void)
{
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}

