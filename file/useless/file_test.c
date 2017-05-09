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
#define		STUDENT_FILE		"stu"

typedef struct st_student
{
	char 	*name;
	char	age;
	char	sex;
	char	*QQnum;
	char	*home_addr;
}ST_STUDENT;

int main(int argc, char *argv[])
{
	int			mode = 0777;
	int 		ret = -1;
	int			fd = -1;
	int			i = 0;
	ST_STUDENT	stu;// = {"TT", 20, 'f', "1234567"};

	stu.name = "TT";
	stu.age = 20;
	stu.sex = 'f';
	stu.QQnum = "1234567";
	stu.home_addr = "Moon abdcdejk;odsdkja;idujkj";

	printf("umask = %x\n", umask);
	//printf("mode&~umask = %x\n", (mode&(~umask)));
	fd = open( STUDENT_FILE, 
		O_WRONLY|O_CREAT|O_TRUNC, 
		0666);
	if(fd<0)
	{
		perror(STUDENT_FILE);
		return 2;
	}

//	ret = writeN(fd, stu.name, strlen(stu.name));
//	ret = writeN(fd, &stu, sizeof(ST_STUDENT));

	close(fd);
	return ret;
}


