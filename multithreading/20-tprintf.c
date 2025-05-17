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
* tprintf - func
* @format: char const *
* Return: int
*/
int tprintf(char const *format, ...)
{
	pthread_t tid;
	va_list args;

	pthread_cond_wait(&cond, &mutex);
	pthread_mutex_lock(&mutex);
	tid = pthread_self();
	printf("[%ld] ", tid);
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}
