/**
 * @file        
 * @brief       变成僵尸进程的进程过继给1号进程后，会被1号进程杀死
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/
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
        case 0:  
            sleep(10);
            break;
        case -1: 
            return -1;
        default: 
            sleep(15);
            break;
    }


    return 0;
}

