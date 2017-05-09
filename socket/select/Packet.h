
#include <stdint.h>

#define PACKET_TYPE_LOGIN 0x01
#define PACKET_TYPE_ERROR 0x02


#define ERROR_CODE_NO_ERROR   0x00
#define ERROR_CODE_NAMR_ERROR 0x01
#define ERROR_CODE_PWD_ERROR  0x02

#pragma pack(1)

typedef struct st_head
{
	uint8_t    type;
	uint32_t   len;
} ST_HEAD;

typedef struct st_login
{
	uint8_t    type;
	uint32_t   len;
	uint8_t    nameLen;
	char       *name;   /*没有'\0'*/
	uint8_t    pwdLen;
	char       *pwd;   /*没有'\0'*/
} ST_LOGIN;

typedef struct st_error
{
	uint8_t    type;
	uint32_t   len;
	uint8_t    errorCode; 
} ST_ERROR;

typedef struct st_cmd
{
	uint8_t    type;
	uint32_t   len;
	uint8_t    cmdLen;
	char       *cmd;   /*没有'\0'*/
} ST_CMD;

typedef struct st_cmd_result
{
	uint8_t    type;
	uint32_t   len;
	uint32_t   resultLen;
	char       *result;   /*没有'\0'*/
} ST_CMD_RESULT;

typedef struct st_heart
{
	uint8_t    type;
	uint32_t   len;
	uint32_t   number;
} ST_HEART;


#pragma pack()


int rcvPacket(int socketfd, 
	uint8_t *packetBuf, uint32_t *packetBufLen);

int initLogin(ST_LOGIN *login, const char *name, const char * pwd);

int enLogin(const ST_LOGIN *login,
	uint8_t *packetBuf, uint32_t *packetBufLen);


int dealLogin(const ST_LOGIN *login, int socketfd);

int destroyLogin(ST_LOGIN *login);



