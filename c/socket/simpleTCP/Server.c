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
	int                 listenSocketfd = -1;
	int                 connnectSocketfd = -1;
	struct sockaddr_in  serverAddr;
	struct sockaddr_in  clientAddr;
	socklen_t           clientAddrLen;
	char                rcvBuf[100];
	int                 ret = -1;

	listenSocketfd = socket(AF_INET, 
		SOCK_STREAM, 0);
	if (listenSocketfd < 0)
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
		exit(1);
	}

	ret = bind(listenSocketfd, 
		(struct sockaddr *)&serverAddr, 
		sizeof(serverAddr));
	if (ret < 0)
	{
		perror("bind err");
		close(listenSocketfd);
		exit(1);
	}
	
	ret = listen(listenSocketfd, 5);
	if (ret < 0)
	{
		perror("listen err");
		close(listenSocketfd);
		exit(1);
	}

	clientAddrLen = sizeof(clientAddr);
	connnectSocketfd = accept(listenSocketfd, 
			(struct sockaddr *)&clientAddr, 
			&clientAddrLen);
	if (connnectSocketfd < 0)
	{
		perror("listen err");
		close(listenSocketfd);
		exit(1);
	}

	memset(rcvBuf, 0, sizeof(rcvBuf));
	ret = read(connnectSocketfd, rcvBuf, 
		sizeof(rcvBuf));
	if (ret < 0)
	{
		perror("read err");
		close(listenSocketfd);
		close(connnectSocketfd);
		exit(1);
	}

	printf("rcvBuf = %s\n", rcvBuf);

	
	close(listenSocketfd);
	close(connnectSocketfd);
		
	exit(0);
}










