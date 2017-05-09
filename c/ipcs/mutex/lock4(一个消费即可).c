#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE			1024

int			buffer[BUFFER_SIZE];

int		count=0;
pthread_mutex_t		mutex1;
pthread_mutex_t		mutex2;

//int		flag=0; //0-is old, 1-is new;

void *threadFun1(void *arg)
{
	int		i;
	while(1)
	{
		pthread_mutex_lock(&mutex1);
		printf("Thread 1\n");
		count++;
		pthread_mutex_unlock(&mutex2);
	}
}

void *threadFun2(void *arg)
{
	int		i;
	while(1)
	{
		pthread_mutex_lock(&mutex2);
		printf("Thread 2:%d\n",count);
		pthread_mutex_unlock(&mutex1);
	}
}

void *threadFun3(void *arg)
{
	int		i;
	while(1)
	{
		pthread_mutex_lock(&mutex2);
		printf("Thread 3:%d\n",count);
		pthread_mutex_unlock(&mutex1);
	}
}

#define MAX_PTHREAD_NUM		3

int main()
{
	pthread_t 	tid[MAX_PTHREAD_NUM];
	int			ret=0;
	int			i;
	int			t_value[MAX_PTHREAD_NUM];
	void		*(*threadFun[])(void*) = 
				{threadFun1, threadFun2,threadFun3};

	ret = pthread_mutex_init(&mutex1,NULL);
	if(ret!=0)
	{
		fprintf(stderr, "pthread mutex init error:%s",
			strerror(ret));
		return 1;
	}
	
	ret = pthread_mutex_init(&mutex2,NULL);
	if(ret!=0)
	{
		fprintf(stderr, "pthread mutex init error:%s",
			strerror(ret));
		return 1;
	}
	pthread_mutex_lock(&mutex2);
	
	printf("Main thread before pthread create\n");

	for(i=0; i<MAX_PTHREAD_NUM; i++)
	{
		t_value[i]=i;
		ret=pthread_create( &(tid[i]), NULL,
			threadFun[i], (void*)&(t_value[i]));
		if(ret!=0)
		{
			fprintf(stderr, "pthread create error:%s",
				strerror(ret));
			return 1;
		}
	}
	printf("Main thread after pthread create\n");
	for(i=0; i<MAX_PTHREAD_NUM; i++)
	{
		ret = pthread_join(tid[i],NULL);
		if(ret!=0)
		{
			fprintf(stderr, "pthread join error:%s",
				strerror(ret));
			return 2;
		}
	}
	ret = pthread_mutex_destroy(&mutex1);
	if(ret!=0)
	{
		fprintf(stderr, "pthread mutex destroy error:%s",
			strerror(ret));
		return 1;
	}
	ret = pthread_mutex_destroy(&mutex2);
	if(ret!=0)
	{
		fprintf(stderr, "pthread mutex destroy error:%s",
			strerror(ret));
		return 1;
	}
	
	printf("All threads are over!\n");
	return 0;
}

