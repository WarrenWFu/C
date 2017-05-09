#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int my_system(const char *command)
{
	pid_t	pid=0;
	int		status=0;

	pid = fork();
	
	if( pid > 0 )
	{
		pid = wait(&status);
		return WEXITSTATUS(status);
	}
	else if( 0 == pid )
	{
		status = execlp("sh", "sh", "-c", 
			command, NULL);
		if( status < 0 )
		{
			perror("exec error");
			exit(-1);//-1 auto give to status
		}
		exit(status);
	}
	else
	{
		perror("fork error");
		return -1;
	}
	return 0;
}

int main()
{
	printf("Main Start---\n");
	my_system("ls -al");
	printf("---Main End\n");

	return 0;
}
