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

#include "Debug.h"
#include "Socket.h"
#include "Packet.h"


int main()
{
	int                 socketfd = -1;
	uint8_t             packetBuf[1024*100];
	uint32_t            packetBufLen;
	ST_LOGIN            login;
	int                 ret = 0;

	socketfd = openSocket("192.168.33.136",
		5050);
	if (socketfd < 0)
	{
		printf("openSocket err\n");
		exit(1);
	}

	//初始化包
	ret = initLogin(&login, 
		"CC", "123");
	if (ret < 0)
	{
		printf("initLogin err\n");
		close(socketfd);
		exit(1);
	}

	//打包
	packetBufLen = sizeof(packetBuf);
	ret = enLogin(&login, packetBuf, 
		&packetBufLen);
	if (ret < 0)
	{
		printf("enLogin err ret = %d\n",
			ret);
		close(socketfd);
		exit(1);
	}

	DEBUG_PRINT_DATA(packetBuf, packetBufLen);

	//发包
	writeN(socketfd, packetBuf, 
		packetBufLen);

	
	//销毁包
	destroyLogin(&login);

	close(socketfd);
	
	exit(0);
}










