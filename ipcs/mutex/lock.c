#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE			1024

int			buffer[BUFFER_SIZE];
pthread_mutex_t		mutex;

void *threadFun1(void *arg)
{
	int		i;
	int		count=0;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		for(i=0; i<BUFFER_SIZE; i++)
		{
			buffer[i]=count;
		}
		count++;
		pthread_mutex_unlock(&mutex);
	}
}

void *threadFun2(void *arg)
{
	int		i;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("Get:%d--%d\n",buffer[0],
			buffer[BUFFER_SIZE-1]);
		pthread_mutex_unlock(&mutex);
	}
}

#define MAX_PTHREAD_NUM		2

int main()
{
	pthread_t 	tid[MAX_PTHREAD_NUM];
	int			ret=0;
	int			i;
	int			t_value[MAX_PTHREAD_NUM];
	void		*(*threadFun[])(void*) = {threadFun1, threadFun2};

    pthread_mutexattr_t attr;                                                   
    pthread_mutexattr_init(&attr);                                              
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);                     
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);                
    pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);

	//ret = pthread_mutex_init(&mutex,NULL);
	ret = pthread_mutex_init(&mutex,&attr);
	if(ret!=0)
	{
		fprintf(stderr, "pthread mutex init error:%s",
			strerror(ret));
		return 1;
	}
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
	ret = pthread_mutex_destroy(&mutex);
	if(ret!=0)
	{
		fprintf(stderr, "pthread mutex destroy error:%s",
			strerror(ret));
		return 1;
	}
	printf("All threads are over!\n");
	return 0;
}

