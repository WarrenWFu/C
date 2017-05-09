#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdint.h>
#include <sys/shm.h>
#include <semaphore.h>

ssize_t readN(int fd, void *buf, size_t count)
{
	int		left = count;
	int		offset = 0;
	int		ret = -1;

	while(left)
	{
		ret = read(fd, buf+offset, left);
		if( ret < 0 )
		{
			if (errno == EINTR)
			{
				continue;
			}
			return -1;
		}
		if( 0 == ret )
		{
			break;
		}
		left = left - ret;
		offset = offset + ret;
	}
	return offset;
}

ssize_t writeN(int fd, const void *buf,
	size_t count)
{
	int		left = count;
	int		offset = 0;
	int		ret = -1;

	while(left)
	{
		ret = write(fd, buf+offset, left);
		if( ret < 0 )
		{
			if (errno == EINTR)
			{
				continue;
			}
			return -1;
		}
		left = left - ret;
		offset = offset + ret;
	}
	return offset;
}


ssize_t readLine(int fd, char *buf, size_t count)
{
	int		left = count;
	int		offset = 0;
	int		ret = 1;
	
	while(left > 0)
	{
		ret = read(fd, buf+offset, 1);
		if( ret > 0 )
		{
			offset++;
			left--;
		}
		else if( ret < 0 )
		{
			if (errno == EINTR)
			{
				continue;
			}
			return -1;
		}
		else
		{
			break;
		}
		
		if('\n'== buf[offset-1])
		{
			break;
		}
	}
	
	return offset;
}

typedef struct st_shm
{
	sem_t       sem1;
	sem_t       sem2;
	uint32_t    data;
} ST_SHM;

int initShm(ST_SHM *shm)
{
	int   ret = -1;

	ret = sem_init(&(shm->sem1), 1, 1);
	if (ret < 0)
	{
		return ret;
	}

	ret = sem_init(&(shm->sem2), 1, 0);
	if (ret < 0)
	{
		sem_destroy(&(shm->sem1));
		return ret;
	}

	shm->data = 0;

	return 0;
}

int main()
{
	int     shmid = -1;
	int     ret = -1;
	ST_SHM  *pshm = NULL;
	
	shmid = shmget((key_t)0x01020304, 
		sizeof(ST_SHM),
		0);
	if (shmid < 0)
	{
		perror("shmget err");
		exit(1);
	}

	pshm = shmat(shmid, NULL, 0);
	if (pshm == ((void *)-1))
	{
		perror("shmat err");
		exit(1);
	}

	
	while (1)
	{
		sem_wait(&(pshm->sem2));
		
		printf("pshm->data = %d\n", 
			pshm->data);
		
		sem_post(&(pshm->sem1));
	}

	
	
	
	exit(0);
}










