#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct wrlock{
	int wr_num;

}ST_WRLOCK;

pthread_mutex_t		mutex1;
pthread_mutex_t		mutex2;
pthread_mutex_t		mutex3;
pthread_mutex_t		mutex4;
pthread_mutex_t		mutex5;
pthread_mutex_t		mutex6;


int wr_init(ST_WRLOCK *wrlock)
{
	ret = pthread_mutex_init(&wrlock,NULL);
	if(ret!=0)
	{
		fprintf(stderr, "pthread mutex init error:%s",
			strerror(ret));
		return 1;
	}
}

int wr_destroy(ST_WRLOCK *wrlock)
{
	ret = pthread_mutex_destroy(&wrlock);
	if(ret!=0)
	{
		fprintf(stderr, "pthread mutex destroy error:%s",
			strerror(ret));
		return 1;
	}
}

int r_lock(ST_WRLOCK *wrlock)
{

		return pthread_mutex_lock(&wrlock);
	
}

int r_unlock(ST_WRLOCK *wrlock)
{
	int		i;
	while(1)
	{
		pthread_mutex_lock(&mutex1);
		pthread_mutex_lock(&mutex2);
		pthread_mutex_lock(&mutex3);
		printf("Thread 1\n");
		count++;
		pthread_mutex_unlock(&mutex4);
		pthread_mutex_unlock(&mutex5);
		pthread_mutex_unlock(&mutex6);
	}
}

int w_lock(ST_WRLOCK *wrlock)
{
	
		return pthread_mutex_lock(&wrlock);
		num++;
}

int w_unlock(ST_WRLOCK *wrlock)
{
	int		i;
	while(1)
	{
		pthread_mutex_lock(&mutex1);
		pthread_mutex_lock(&mutex2);
		pthread_mutex_lock(&mutex3);
		printf("Thread 1\n");
		count++;
		pthread_mutex_unlock(&mutex4);
		pthread_mutex_unlock(&mutex5);
		pthread_mutex_unlock(&mutex6);
	}
}

