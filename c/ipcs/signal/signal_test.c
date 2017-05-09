#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<wait.h>

extern char **environ;

void hand_sig_child()
{
	int ret;
	pid_t  pid_c;

	pid_c = wait(&ret);
	ret = WEXITSTATUS(ret);
	printf("Child process PID[%d]return[%d]--\n",pid_c,ret);
}

int main()
{
	pid_t pid;
	signal(SIGCHLD,hand_sig_child);
	pid=fork();
	if(pid==0)
	{
		printf("Child process PID[%d]will exit with status 0.\n",getpid());
		exit(1);
	}
	else if(pid!=-1)
	{
		while(1)
		{
			sleep(1);
		}
	}
	else 
		printf("There was an error with forking!\n");
	return 0;
}

