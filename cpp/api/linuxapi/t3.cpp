/**
 * @file        
 * @brief       使用signal和alarm实现回调
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <cstdio>
#include <unistd.h>
#include <string>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

time_t nSeconds = time(NULL);
long long iCounter = 0;

void foo(int sig) {
    iCounter = 100000000099;
    printf("%ld\n", time(NULL) - nSeconds);
    signal(SIGALRM, foo);
    alarm(1);
}

int main()
{
    foo(0);

    iCounter = 0;
    for (iCounter = 0; iCounter < 100000000000; iCounter++)
    { }

    printf("%lld\n", iCounter);

    return 0;
}
