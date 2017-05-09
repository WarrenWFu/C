#include <time.h>

#include "Socket.h"



int openSocket(const char *serverIP, 
	uint16_t port)
{
	int                 socketfd = -1;
	struct sockaddr_in  serverAddr;
	int                 ret = -1;
	int                 var;
	
	socketfd = socket(AF_INET, 
		SOCK_STREAM, 0);
	if (socketfd < 0)
	{
		perror("socket err");
		return -1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	ret = inet_pton(AF_INET, serverIP, 
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
		return -1;
	}


	var = fcntl(socketfd, F_GETFL, NULL);
	if (var < 0)
	{
		close(socketfd);
		return -1;
	}
	ret = fcntl(socketfd, 
		F_SETFL, 
		var | O_NONBLOCK);
	
	if (ret < 0)
	{
		close(socketfd);
		return -1;
	}
	
	return socketfd;
}


int openListenSocket(uint16_t port)
{
	struct sockaddr_in  serverAddr;
	int                 listenSocketfd;
	int                 ret = -1;
	int                 var;
	
	listenSocketfd = socket(AF_INET, 
		SOCK_STREAM, 0);
	if (listenSocketfd < 0)
	{
		perror("socket err");
		return -1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	
	ret = bind(listenSocketfd, 
		(struct sockaddr *)&serverAddr, 
		sizeof(serverAddr));
	if (ret < 0)
	{
		perror("bind err");
		close(listenSocketfd);
		return -1;
	}

	ret = listen(listenSocketfd, 5);
	if (ret < 0)
	{
		perror("listen err");
		close(listenSocketfd);
		return -1;
	}

	var = fcntl(listenSocketfd, F_GETFL, NULL);
	if (var < 0)
	{
		close(listenSocketfd);
		return -1;
	}
	ret = fcntl(listenSocketfd, 
		F_SETFL, 
		var | O_NONBLOCK);
	
	if (ret < 0)
	{
		close(listenSocketfd);
		return -1;
	}

	return listenSocketfd;
}

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


ssize_t readN_timeout(int fd, void *buf, 
	size_t count, unsigned int sec)
{
	int		         left = count;
	int		         offset = 0;
	int		         ret = -1;
	fd_set           rfset;
	struct timeval   timeout;
	time_t           t1 = 0;
	time_t           t2 = 0;

	timeout.tv_sec = sec;
	timeout.tv_usec = 0;

	FD_ZERO(&rfset);
	FD_SET(fd, &rfset);

	while(left)
	{
again_select:
		if (t2 > t1)
		{
			if (sec > (t2 -t1))
			{
				timeout.tv_sec = sec - (t2 -t1);
			}
			else
			{
				errno = ETIMEDOUT;
				return -1;
			}
			
		}

		t1 = time(NULL);
		ret = select(fd+1, 
			&rfset,
			NULL,
			NULL,
			&timeout);
		if (ret < 0)
		{
			if (errno == EINTR)
			{
				goto again_select;
			}
			return -1;
		}
		else if (ret == 0)
		{
			errno = ETIMEDOUT;
			return -1;
		}

again_read:
		ret = read(fd, buf+offset, left);
		if( ret < 0 )
		{
			if (errno == EINTR)
			{
				goto again_read;
			}
			else if (errno == EAGAIN)
			{
				goto again_select;
			}
			return -1;
		}
		if( 0 == ret )
		{
			break;
		}
		left = left - ret;
		offset = offset + ret;

		t2 = time(NULL);
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


ssize_t writeN_timeout(int fd, const void *buf,
	size_t count, unsigned int sec)
{
	int		         left = count;
	int		         offset = 0;
	int		         ret = -1;
	fd_set           wfset;
	struct timeval   timeout;
	time_t           t1 = 0;
	time_t           t2 = 0;

	timeout.tv_sec = sec;
	timeout.tv_usec = 0;

	FD_ZERO(&wfset);
	FD_SET(fd, &wfset);

	while(left)
	{
again_select:
		if (t2 > t1)
		{
			if (sec > (t2 -t1))
			{
				timeout.tv_sec = sec - (t2 -t1);
			}
			else
			{
				errno = ETIMEDOUT;
				return -1;
			}
			
		}
		t1 = time(NULL);
		ret = select(fd+1, 
			NULL,
			&wfset,
			NULL,
			&timeout);
		if (ret < 0)
		{
			if (errno == EINTR)
			{
				goto again_select;
			}
			return -1;
		}
		else if (ret == 0)
		{
			errno = ETIMEDOUT;
			return -1;
		}
		
again_write:
		ret = write(fd, buf+offset, left);
		if( ret < 0 )
		{
			if (errno == EINTR)
			{
				goto again_write;
			}
			else if (errno == EAGAIN)
			{
				goto again_select;
			}
			return -1;
		}
		left = left - ret;
		offset = offset + ret;
		t2 = time(NULL);
	}
	return offset;
}



ssize_t readLine(int fd, char *buf, size_t count)
{
	int		         left = count;
	int		         offset = 0;
	int		         ret = 1;

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

ssize_t readLine_timeout(int fd, 
	char *buf, size_t count,
	unsigned int sec)
{
	int		         left = count;
	int		         offset = 0;
	int		         ret = 1;
	fd_set           rfset;
	struct timeval   timeout;
	time_t           t1 = 0;
	time_t           t2 = 0;

	timeout.tv_sec = sec;
	timeout.tv_usec = 0;

	FD_ZERO(&rfset);
	FD_SET(fd, &rfset);
	
	while(left > 0)
	{
again_select:
		if (t2 > t1)
		{
			if (sec > (t2 -t1))
			{
				timeout.tv_sec = sec - (t2 -t1);
			}
			else
			{
				errno = ETIMEDOUT;
				return -1;
			}
			
		}

		t1 = time(NULL);
		ret = select(fd+1, 
			&rfset,
			NULL,
			NULL,
			&timeout);
		if (ret < 0)
		{
			if (errno == EINTR)
			{
				goto again_select;
			}
			return -1;
		}
		else if (ret == 0)
		{
			errno = ETIMEDOUT;
			return -1;
		}

again_read:
		ret = read(fd, buf+offset, 1);
		if( ret > 0 )
		{
			offset++;
			left--;
		}
		else if(ret < 0 )
		{
			if (errno == EINTR)
			{
				goto again_read;
			}
			else if (errno == EAGAIN)
			{
				goto again_select;
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

		t2 = time(NULL);
	}
	
	return offset;
}


ssize_t readLine2(int fd, char *buf, size_t count)
{
	int    ret = -1;
	int    i = 0;

	if (count < 1)
	{
		return -1;
	}
	
	ret = readLine(fd, buf, count-1);
	if (ret <= 0)
	{
		return ret;
	}

	i = ret;
	while (buf[i] == '\n' 
		|| buf[i] == '\r')
	{
		i--;
	}

	buf[i+1] = '\0';
	
	return ret;
}


ssize_t readLine2_timeout(int fd, 
	char *buf, size_t count, int sec)
{
	int    ret = -1;
	int    i = 0;

	if (count < 1)
	{
		return -1;
	}
	
	ret = readLine_timeout(fd, buf, count-1,
		sec);
	if (ret <= 0)
	{
		return ret;
	}

	i = ret;
	while (buf[i] == '\n' 
		|| buf[i] == '\r')
	{
		i--;
	}

	buf[i+1] = '\0';
	
	return ret;
}


