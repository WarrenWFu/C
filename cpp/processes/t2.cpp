/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:简单的通过异步信号signal来回收结束的子进程，而不用waitpid来阻塞。
 *
*******************************************************************************/
#include <string>
#include <cstdio>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void forsigchld(int val)
{
    pid_t pid;
    pid = waitpid(-1, NULL, WNOHANG);

    char buffer[10];
    for ( ;pid > 0; )
    {
        snprintf(buffer, sizeof(buffer), "%08d", pid);
        printf("the child pid is [%d]\n", pid);
        pid = waitpid(-1, NULL, WNOHANG);
    }
}

int main()
{
    signal(SIGPIPE, SIG_IGN);
    
    struct sigaction act;
    act.sa_handler = forsigchld;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_NOCLDSTOP;
    
    if(sigaction(SIGCHLD, &act, NULL)<0)
    {
        printf("sigaction fail[%d]", errno);
    }

    switch (fork())
    {
        case 0:
            printf("from child\n");
            sleep(1);
            break;
        case -1: 
            return -1;
        default:
            sleep(1000);
            break;
    }


    return 0;
}

