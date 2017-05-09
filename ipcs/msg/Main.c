/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用消息队列进行进程间通讯
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    return 0;
}
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
	
	msgid = msgget((key_t)0x01020304, 0);
	if (msgid < 0)
	{
		perror("msgget err");
		exit(1);
	}

	msg.type = 1;
	msg.data = 250;
	ret = msgsnd(msgid, &msg, 
			sizeof(msg) - sizeof(msg.type),
			0);
	if (ret < 0)
	{
		perror("msgsnd err");
		exit(1);
	}

	msg.type = 1;
	msg.data = 22;
	ret = msgsnd(msgid, &msg, 
			sizeof(msg) - sizeof(msg.type),
			0);
	if (ret < 0)
	{
		perror("msgsnd err");
		exit(1);
	}

	msg.type = 2;
	msg.data = 44;
	ret = msgsnd(msgid, &msg, 
			sizeof(msg) - sizeof(msg.type),
			0);
	if (ret < 0)
	{
		perror("msgsnd err");
		exit(1);
	}

	msg.type = 1;
	msg.data = 99;
	ret = msgsnd(msgid, &msg, 
			sizeof(msg) - sizeof(msg.type),
			0);
	if (ret < 0)
	{
		perror("msgsnd err");
		exit(1);
	}

	
	
	
	exit(0);
}










