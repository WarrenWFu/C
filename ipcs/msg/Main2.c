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

#pragma pack(1)

typedef struct st_msg
{
	long      type;
	uint32_t  data;
} ST_MSG;

#pragma pack()

int main()
{
	int     msgid = -1;
	ST_MSG  msg;
	int     ret = -1;
	
	msgid = msgget((key_t)0x01020304, 
		IPC_CREAT|0777);
	if (msgid < 0)
	{
		perror("msgget err");
		exit(1);
	}

	ret = msgrcv(msgid, &msg, 
			sizeof(msg) - sizeof(msg.type),
			0, 
			0);
	if (ret < 0)
	{
		perror("msgrcv err");
		exit(1);
	}

	printf("msg.data = %d\n", msg.data);


	getchar();

	ret = msgctl(msgid, IPC_RMID, NULL);
	if (ret < 0)
	{
		perror("msgctl err");
		exit(1);
	}

	
	exit(0);
}










