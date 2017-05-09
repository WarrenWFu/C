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
#include <sys/socket.h>
#include <arpa/inet.h>


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
	int                 socketfd = -1;
	struct sockaddr_in  serverAddr;
	int                 ret = -1;

	socketfd = socket(AF_INET, 
		SOCK_STREAM, 0);
	if (socketfd < 0)
	{
		perror("socket err");
		exit(1);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5050);
	ret = inet_pton(AF_INET, "192.168.33.136", 
		&(serverAddr.sin_addr));
	if (ret < 0)
	{
		perror("inet_pton err");
		close(socketfd);
		exit(1);
	}

	ret = connect(socketfd, 
		(struct sockaddr *)&serverAddr,
		sizeof(serverAddr));
	if (ret < 0)
	{
		perror("connect err");
		close(socketfd);
		exit(1);
	}

	ret = writeN(socketfd, "hello", 
		strlen("hello"));
	if (ret < 0)
	{
		perror("writeN err");
		close(socketfd);
		exit(1);
	}

	
	close(socketfd);
	exit(0);
}










