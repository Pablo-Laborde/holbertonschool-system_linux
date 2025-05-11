#include "multithreading.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/**
* tprintf - func
* @format: char const *
* Return: int
*/
int tprintf(char const *format, ...)
{
	pthread_t tid;

	pthread_cond_wait(&cond, &mutex);
	tid = pthread_self();
	printf("[%ld] %s", tid, format);
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

