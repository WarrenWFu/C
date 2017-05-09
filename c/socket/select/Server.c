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
#include <pthread.h>

#include "Socket.h"
#include "Debug.h"

int main()
{
	int                 listenSocketfd = -1;
	int                 connectSocketfd = -1;
	ST_HEAD             *head = NULL;
	ST_LOGIN            login;
	uint8_t             packetBuf[1024 * 100];
	uint32_t            packetBufLen;
	int                 i = 0;
	int                 ret = -1;

	listenSocketfd = openListenSocket(5050);
	if (listenSocketfd < 0)
	{
		printf("openListenSocket err\n");
		exit(1);
	}

	connectSocketfd = accept(listenSocketfd,
		 NULL,
		 NULL);
	if (connectSocketfd < 0)
	{
		perror("accept err");
		exit(1);
	}

	//収包
	packetBufLen = sizeof(packetBuf);
	ret = rcvPacket(connectSocketfd, 
		packetBuf, &packetBufLen);
	if (ret < 0)
	{
		perror("rcvPacket err");
		close(listenSocketfd);
		close(connectSocketfd);
		exit(1);
	}
	else if (ret == 0)
	{
		close(listenSocketfd);
		close(connectSocketfd);
		exit(1);
	}
	DEBUG_PRINT_DATA(packetBuf, packetBufLen);

	head = (ST_HEAD *)packetBuf;
	switch (head->type)
	{
		case PACKET_TYPE_LOGIN:
		{
			//解包
			ret = deLogin(&login, 
				packetBuf, packetBufLen);
			if (ret < 0)
			{
				close(listenSocketfd);
				close(connectSocketfd);
				printf("deLogin err");
				exit(1);
			}

			//处理包
			ret = dealLogin(&login, 
				connectSocketfd);
			if (ret < 0)
			{
				close(listenSocketfd);
				close(connectSocketfd);
				printf("dealLogin err");
				exit(1);
			}

			//销毁包
			destroyLogin(&login);
		}
	}
	
	exit(0);
}

