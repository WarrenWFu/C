#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define	BUFFER_SIZE	1024

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
			return -1;
		}
		left = left - ret;
		offset = offset + ret;
	}
	return offset;
}


ssize_t readLine(int fd, void *buf, size_t count)
{
	int		offset = 0;
	int		ret = 1;
	
	while( ret > 0 && offset <= count )
	{
		ret = read(fd, buf+offset, 1);
		if( ret > 0 )
		{
			offset++;
//			printf("offset:%d\n", count);
		}
		else if( ret < 0 )
		{
			return -1;
		}
		else
		{
			break;
		}
		
//		printf("%d:%d:%d\n", *(char*)(buf+offset-1),'\n');

		if('\n'== ((char*)buf)[offset-1])
		{
			break;
		}
	}
//	printf("offset=%d\n");
	return offset;
}

#define		EXCHANGE_OFFSET		('a'-'A')

int main(int argc, char *argv[])
{
	int 	ret = -1;
	int		src_fd = -1;
	int		dest_fd = -1;
	char	buffer[BUFFER_SIZE];
	char	*temp=NULL;
	int		i = 0;
	
	if( 3 != argc )
	{
		printf("Usage:\n");
		printf("\t%s [dest_file] [src_file]\n",
			argv[0]);
		return 1;
	}

	src_fd = open( argv[1], O_RDONLY);
	if(src_fd<0)
	{
		perror(argv[1]);
		return 2;
	}

	
	dest_fd = open( argv[2], 
		O_WRONLY|O_CREAT|O_TRUNC, 0666 );
	if(dest_fd<0)
	{
		perror(argv[2]);
		close(src_fd);
		return 2;
	}

	while(1)
	{
		memset(buffer, 0, BUFFER_SIZE);
		ret = readN( src_fd, buffer, BUFFER_SIZE);
		if( ret < 0)
		{
			ret = 3;
			break;
		}
		if( 0 == ret )
		{
			break;
		}
		temp=buffer;
		for( i=0; i<ret; i++ )
		{
			if(*temp >= 'a' && *temp <= 'z')
			{
				*temp = *temp - EXCHANGE_OFFSET;
			}
			else if(*temp >= 'A' && *temp <= 'Z')
			{
				*temp = *temp + EXCHANGE_OFFSET;
			}
			temp++;
		}
		ret = writeN(dest_fd, buffer, ret);
		if( ret < 0 )
		{
			ret = 3;
			break;
		}
	}

	close(src_fd);
	close(dest_fd);
	return ret;
}


