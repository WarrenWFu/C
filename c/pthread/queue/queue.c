#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define  SIZE 10

typedef struct st_queue
{
	int              array[SIZE];
	int              head;
	int              tail;
} ST_QUEUE;

int initQueue(ST_QUEUE *queue)
{
	queue->head = 0;
	queue->tail = 0;
	return 0;
}

int destroyQueue(ST_QUEUE *queue)
{
	return 0;
}

int enqueue(ST_QUEUE *queue, int m)
{
	if(queue->head == (queue->tail + 1)%SIZE)
	{
		return 1;
	}
	
	queue->array[queue->tail] = m;
//loop to the tail	
	queue->tail = (queue->tail + 1)%SIZE;
	return 0;
}
int dequeue(ST_QUEUE *queue, int *m)
{
	if(queue->head == queue->tail)
	{
		return 1;
	}
	
	*m = queue->array[queue->head];
//loop to the head
	queue->head = (queue->head + 1)%SIZE;
	return 0;
}

ST_QUEUE     queue;

void *enqueueThread(void *arg)
{
	int     i = 0;
	int     ret = -1;
	
	while (1)
	{
		ret = enqueue(&queue, i);
		if (ret == 0)
		{
			i++;
		}
	}
	return NULL;
}

void *dequeueThread(void *arg)
{
	int     m = 0;
	int     ret = -1;
	
	while (1)
	{
		ret = dequeue(&queue, &m);
		//printf("dequeue ret = %d\n", ret);
		if (ret == 0)
		{
			printf("dequeue m = %d\n", m);
		}
	}
	return NULL;
}

#define PTHREAD_NUM_MAX		2

int main()
{
	pthread_t        tid[PTHREAD_NUM_MAX];
	int              i = 0;
	int              ret = 0;

	initQueue(&queue);

    //定义函数指针数组
	void *(*threadArray[])(void *) = {
		enqueueThread, dequeueThread
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

	destroyQueue(&queue);

	exit(0); 
}

