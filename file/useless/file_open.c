#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define	FILE_PATH	"a.txt"
#define FILE_NAME_LENGTH	17	

int main()
{
	int 	fd[10];
	int 	i = 0;
	int		start=0;
	char	filename[FILE_NAME_LENGTH];
	int		end=0;

	printf("start:%p\n",&start);
	printf("filename:%p\n",filename);
	printf("end:%p\n",&end);

	for(i=0;i<10;i++)
	{
		memset(filename, 0, FILE_NAME_LENGTH); 
		sprintf(filename, "IotekTestFileName%d", i);
		printf("end = %d start =% d\n", end, start);
        //使用读写方式|创建方式打开，创建文件则以0640的权限创建。
		fd[i] = open( filename, O_RDWR | O_CREAT, 
			0640 );
		if( fd[i] < 0 )
		{
	//		perror(FILE_PATH);
			fprintf( stderr, "%s:%s\n", filename, 
				strerror(errno));
			return 1;
		}
	}

	for(i=0;i<10;i++)
	{
		close(fd[i]);
	}
	return 0;
}


