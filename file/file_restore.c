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

ssize_t writeN(int fd, const void *buf, size_t count)
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
		}
		else if( ret < 0 )
		{
			return -1;
		}
		else
		{
			break;
		}
		
		if('\n'== ((char*)buf)[offset-1])
		{
			break;
		}
	}
	return offset;
}

int main(int argc, char *argv[])
{
	int			fd = -1;
	char		input_str[BUFFER_SIZE];
	int			ret = 1;
	int			count = BUFFER_SIZE;

	if( argc != 2 )
	{
		printf("Usage:\n");
		printf("\t%s [filename]\n", argv[0]);
		return 1;
	}

	fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if( fd<0 )
	{
		perror(argv[1]);
		return 2;
	}

	while(1)
	{
		memset(input_str, 0, count);
		count = 0;

		count = readLine( 0, input_str, BUFFER_SIZE );
		
		if( 5 == count && 
			!strcmp(input_str, "exit\n"))
		{
			break;
		}

		ret = writeN(fd, input_str, count);
		if( -1 == ret )
		{
			perror("write error:");
		}
	}

	close(fd);
	return 0;
}


