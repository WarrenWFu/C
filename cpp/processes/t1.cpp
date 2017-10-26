/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:进程守护化参考
 *
 *******************************************************************************/
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main()
{
    if ( getppid() == 1 ) return 0;

    switch (fork())
    {
        case 0:  break;
        case -1: return -1;
        default: _exit(0);
    }

    if (setsid() < 0)
        return -1;

//源码中有下面一段，为什么要再fork一次?
//    switch (fork())
//    {
//        case 0:  break;
//        case -1: return -1;
//        default: _exit(0);
//    }

    int fd = -1;
    size_t maxfd = 0;

    // Close all the file description.
    maxfd = getdtablesize();
    for(fd = maxfd; fd >=0 ; fd--)
        close(fd);

    // Redirect Standard input [0] to /dev/null
    fd = open("/dev/null", O_RDWR);

    // Redirect Standard output [1] to /dev/null
    dup (fd);

    // Redirect Standard error [2] to /dev/null
    dup (fd);

    sleep(10);

    return 0;
}

