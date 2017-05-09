#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *threadFun(void *arg)
{
	printf("I am thread %d\n", *((int*)arg));
}

#define MAX_PTHREAD_NUM		4
int main()
{
	pthread_t 	tid[MAX_PTHREAD_NUM];
	int			ret=0;
	int			i;
	int			t_value[MAX_PTHREAD_NUM];

	printf("Main thread before pthread create\n");

	for(i=0; i<MAX_PTHREAD_NUM; i++)
	{
		t_value[i]=i;
		ret=pthread_create( &(tid[i]), NULL,
			threadFun, (void*)&(t_value[i]));
		if(ret!=0)
		{
			fprintf(stderr, "pthread create error:%s",
				strerror(ret));
			return 1;
		}
	}
	printf("Main thread after pthread create\n");
	getchar();//主线程结束，子线程运行,不加会阻塞,主线程结束，子线程被迫结束
	return 0;
}

