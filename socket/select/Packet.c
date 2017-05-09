#include <string.h>
#include <stdlib.h>

#include "Packet.h"


int rcvPacket(int socketfd, 
	uint8_t *packetBuf, uint32_t *packetBufLen)
{
	uint32_t   step;
	uint32_t   offset = 0;
	ST_HEAD    *head = NULL;
	int        ret = -1;

	step = sizeof(ST_HEAD);
	ret = readN(socketfd, 
		packetBuf+offset,
		step);
	if (ret < 0)
	{
		return -1;
	}
	else if (ret < step)
	{
		return 0;
	}
	offset += step;

	head = (ST_HEAD *)packetBuf;

	step = ntohl(head->len);
	ret = readN(socketfd, 
		packetBuf+offset,
		step);
	if (ret < 0)
	{
		return -1;
	}
	else if (ret < step)
	{
		return 0;
	}
	offset += step;

	*packetBufLen = offset;

	return offset;
}



int rcvPacket_timeout(int socketfd, 
	uint8_t *packetBuf, 
	uint32_t *packetBufLen,
	unsigned int sec)
{
	uint32_t   step;
	uint32_t   offset = 0;
	ST_HEAD    *head = NULL;
	int        ret = -1;
	time_t     t1;
	time_t     t2;

	t1 = time(0);
	step = sizeof(ST_HEAD);
	ret = readN_timeout(socketfd, 
		packetBuf+offset,
		step,
		sec);
	if (ret < 0)
	{
		return -1;
	}
	else if (ret < step)
	{
		return 0;
	}
	offset += step;

	head = (ST_HEAD *)packetBuf;

	t2 = time(0);
	if (sec <= (t2 - t1))
	{
		return -1;
	}
	step = ntohl(head->len);
	ret = readN_timeout(socketfd, 
		packetBuf+offset,
		step,
		sec - (t2 - t1));
	if (ret < 0)
	{
		return -1;
	}
	else if (ret < step)
	{
		return 0;
	}
	offset += step;

	*packetBufLen = offset;

	return offset;
}



int initLogin(ST_LOGIN *login,
	const char *name, const char *pwd)
{
	uint8_t   nameLen = 0;
	uint8_t   pwdLen = 0;

	nameLen = strlen(name);
	pwdLen = strlen(pwd);
	
	login->type = PACKET_TYPE_LOGIN;

	login->len = sizeof(login->nameLen)
		+ nameLen
		+ sizeof(login->pwdLen)
		+ pwdLen;
	
	login->nameLen = nameLen;

	login->name = (char *)malloc(login->nameLen);
	if (login->name == NULL)
	{
		return -1;
	}
	memcpy(login->name, name, 
		login->nameLen);

	login->pwdLen = pwdLen;

	login->pwd = (char *)malloc(login->pwdLen);
	if (login->pwd == NULL)
	{
		free(login->name);
		return -1;
	}
	memcpy(login->pwd, pwd, 
		login->pwdLen);

	return 0;
}

int enLogin(const ST_LOGIN *login,
	uint8_t *packetBuf, uint32_t *packetBufLen)
{
	uint32_t   step = 0;
	uint32_t   offset = 0;
	uint32_t   len = 0;

	step = sizeof(login->type);
	if (step + offset > *packetBufLen)
	{
		return -1;
	}
	memcpy(packetBuf+offset, 
		&(login->type),
		step);
	offset += step;

	step = sizeof(login->len);
	len = htonl(login->len);
	if (step + offset > *packetBufLen)
	{
		return -2;
	}
	memcpy(packetBuf+offset, 
		&len,
		step);
	offset += step;

	step = sizeof(login->nameLen);
	if (step + offset > *packetBufLen)
	{
		return -3;
	}
	memcpy(packetBuf+offset, 
		&(login->nameLen),
		step);
	offset += step;

	step = login->nameLen;
	if (step + offset > *packetBufLen)
	{
		return -4;
	}
	memcpy(packetBuf+offset, 
		login->name,
		step);
	offset += step;

	step = sizeof(login->pwdLen);
	if (step + offset > *packetBufLen)
	{
		return -5;
	}
	memcpy(packetBuf+offset, 
		&(login->pwdLen),
		step);
	offset += step;

	step = login->pwdLen;
	if (step + offset > *packetBufLen)
	{
		return -6;
	}
	memcpy(packetBuf+offset, 
		login->pwd,
		step);
	offset += step;

	*packetBufLen = offset;

	return 0;
}


int deLogin(ST_LOGIN *login,
	const uint8_t *packetBuf, uint32_t packetBufLen)
{
	uint32_t   step = 0;
	uint32_t   offset = 0;
	uint32_t   len = 0;

	step = sizeof(login->type);
	if (step + offset > packetBufLen)
	{
		return -1;
	}
	memcpy(&(login->type),
		packetBuf+offset, 
		step);
	offset += step;

	step = sizeof(login->len);
	if (step + offset > packetBufLen)
	{
		return -2;
	}
	memcpy(&(login->len),
		packetBuf+offset, 
		step);
	login->len = ntohl(login->len);
	offset += step;

	step = sizeof(login->nameLen);
	if (step + offset > packetBufLen)
	{
		return -3;
	}
	memcpy(&(login->nameLen),
		packetBuf+offset, 
		step);
	offset += step;

	step = login->nameLen;
	if (step + offset > packetBufLen)
	{
		return -4;
	}
	login->name = (char *)malloc(step);
	if (login->name == NULL)
	{
		return -5;
	}
	memcpy(login->name,
		packetBuf+offset, 
		step);
	offset += step;

	step = sizeof(login->pwdLen);
	if (step + offset > packetBufLen)
	{
		return -6;
	}
	memcpy(&(login->pwdLen),
		packetBuf+offset, 
		step);
	offset += step;

	step = login->pwdLen;
	if (step + offset > packetBufLen)
	{
		return -6;
	}
	login->pwd = (char *)malloc(step);
	if (login->pwd == NULL)
	{
		free(login->name);
		return -7;
	}
	memcpy(login->pwd,
		packetBuf+offset, 
		step);
	offset += step;


	return 0;
}


int dealLogin(const ST_LOGIN *login, int socketfd)
{
	ST_ERROR    error;
	uint8_t     errorCode = ERROR_CODE_NO_ERROR;

	if (strncmp(login->name, 
		"CC", login->nameLen) != 0)
	{
		errorCode = ERROR_CODE_NAMR_ERROR;
	}
	else if (strncmp(login->pwd, 
		"123", login->pwdLen) != 0)
	{
		errorCode = ERROR_CODE_PWD_ERROR;
	}

	//³õÊ¼»¯´íÎó×´Ì¬°ü
	//initError(...);

	//´ò´íÎó×´Ì¬°ü
	//enError(...);

	//·¢´íÎó×´Ì¬°ü
	//writeN(...);

	return 0;
}

int destroyLogin(ST_LOGIN *login)
{
	free(login->name);
	login->name = NULL;
	
	free(login->pwd);
	login->pwd = NULL;
}

int initError(ST_ERROR *error, 
	uint8_t errorCode)
{
	error->type = PACKET_TYPE_ERROR;
	error->len = sizeof(error->errorCode);
	error->errorCode = errorCode;

	return 0;
}

int enError(const ST_ERROR *error,
	uint8_t *packetBuf, 
	uint32_t *packetBufLen)
{
	uint32_t     step = 0;
	uint32_t     offset = 0;
	uint32_t     len = 0;

	step = sizeof(error->type);
	if (step + offset > *packetBufLen)
	{
		return -1;
	}
	memcpy(packetBuf+offset, 
		&(error->type), 
		step);
	offset += step;

	step = sizeof(error->len);
	if (step + offset > *packetBufLen)
	{
		return -1;
	}
	len = htonl(error->len);
	memcpy(packetBuf+offset, 
		&len, 
		step);
	offset += step;

	step = sizeof(error->errorCode);
	if (step + offset > *packetBufLen)
	{
		return -1;
	}
	memcpy(packetBuf+offset, 
		&(error->errorCode), 
		step);
	offset += step;


	*packetBufLen = offset;

	return 0;
}







