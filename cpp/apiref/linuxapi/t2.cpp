/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:getenv的变量对于进程来说是不变的，是否存在系统调用可以重新载入？
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>

using namespace std;

int main()
{
    struct timeval tv;
    memset(&tv, 0x00, sizeof(tv));

    cout << gettimeofday(&tv, NULL) << endl;
    cout << tv.tv_sec << endl;
    cout << tv.tv_usec << endl;

    long lNum = tv.tv_sec * 1000000 + tv.tv_usec;
    cout << lNum << endl;

    printf("%03d%ld\n", 1, lNum);

    return 0;
}

