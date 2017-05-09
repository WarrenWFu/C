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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

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



int main()
{
	int            semid = -1;
	int            ret = -1;
	int            fd = -1;
	struct sembuf  semopbuf[1];
	uint32_t       data = 0;

	fd = open("aa.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open err");
		exit(1);
	}
	
	semid = semget((key_t)0x01020304, 
		2, 0);
	if (semid < 0)
	{
		perror("semget err");
		close(fd);
		exit(1);
	}

	

	while (1)
	{
		semopbuf[0].sem_num = 1;
		semopbuf[0].sem_op = -1;
		semopbuf[0].sem_flg = SEM_UNDO;
		ret = semop(semid, 
				semopbuf, 
				sizeof(semopbuf)/sizeof(struct sembuf));
		if (ret < 0)
		{
			perror("semop err");
			semctl(semid, 0, IPC_RMID, NULL);
			close(fd);
			exit(1);
		}
		lseek(fd, SEEK_SET, 0);
		readN(fd, &data, sizeof(data));
		printf("data = %d\n", data);

		semopbuf[0].sem_num = 0;
		semopbuf[0].sem_op = 1;
		semopbuf[0].sem_flg = SEM_UNDO;
		ret = semop(semid, 
				semopbuf, 
				sizeof(semopbuf)/sizeof(struct sembuf));
		if (ret < 0)
		{
			perror("semop err");
			semctl(semid, 0, IPC_RMID, NULL);
			close(fd);
			exit(1);
		}
	}

	semctl(semid, 0, IPC_RMID, NULL);
	close(fd);
	
	exit(0);
}










