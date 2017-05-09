#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

pthread_cond_t		my_cond;
pthread_mutex_t		my_mutex;
int					flag=0;

void *thread1(void *arg)
{
	int ret=0;
	pthread_mutex_lock(&my_mutex);
	if( flag == 0)
	{
		ret = pthread_cond_wait(&my_cond, 
			&my_mutex);
		if (ret != 0)
		{
			fprintf(stderr, "pthread_cond_wait err %s\n",
				strerror(ret));
			pthread_mutex_unlock(&my_mutex);
			return NULL;
		}
	}
	printf("Thread1\n");
	pthread_mutex_unlock(&my_mutex);
	return NULL;
}

void *thread2(void *arg)
{
	int ret=0;
	printf("Thread2\n");
	sleep(10);
	pthread_mutex_lock(&my_mutex);
	if( flag == 0 )
	{
		flag=1;
		pthread_mutex_unlock(&my_mutex);
		ret = pthread_cond_signal(&my_cond);
		if (ret != 0)
		{
			fprintf(stderr, "pthread_cond_signal err %s\n",
				strerror(ret));
			return NULL;
		}
	}
	else
	{
		pthread_mutex_unlock(&my_mutex);	
	}
	return NULL;
}


#define PTHREAD_NUM_MAX		2

int main()
{
	pthread_t        tid[PTHREAD_NUM_MAX];
	int              i = 0;
	int              ret = 0;

	pthread_cond_init(&my_cond,NULL);

	void *(*threadArray[])(void *) = {
		thread1, thread2,
	};

	for (i=0; i<PTHREAD_NUM_MAX; i++)
	{
		ret = pthread_create(&tid[i], NULL, 
				threadArray[i], NULL);
		if (ret != 0)
		{
			fprintf(stderr, "pthread_create err %s\n",
				strerror(ret));
			return 1;
		}
	}

	for (i=0; i<PTHREAD_NUM_MAX; i++)
	{
		ret = pthread_join(tid[i], NULL);
		if (ret != 0)
		{
			fprintf(stderr, "pthread_join err %s\n",
				strerror(ret));
			return 1;
		}
	}

	pthread_cond_destroy(&my_cond);

	exit(0); 
}

