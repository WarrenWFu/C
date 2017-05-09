
#ifndef SOCKET_H
#define SOCKET_H

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


int openSocket(const char *serverIP, 
	uint16_t port);

int openListenSocket(uint16_t port);

ssize_t readN(int fd, void *buf, size_t count);
ssize_t writeN(int fd, const void *buf,
	size_t count);
ssize_t readLine(int fd, char *buf, size_t count);
ssize_t readLine2(int fd, char *buf, size_t count);

ssize_t readLine_timeout(int fd, 
	char *buf, size_t count,
	unsigned int sec);

ssize_t readLine2_timeout(int fd, 
	char *buf, size_t count,
	unsigned int sec);

#endif

