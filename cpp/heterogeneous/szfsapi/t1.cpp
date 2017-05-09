/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 * g++ -g t1.cpp -I/mnt/winshared/qhjk/trunk/design_implementation/Server/library/libSzfsApi/util/include -L/home/spring/project/qhjk/product/Linux64/lib -lutil_api
 *
 *******************************************************************************/
#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <PoolAccess.hpp>
#include <MySemaphore.hpp>

using namespace std;

CPoolAccess pool(0x10, 10);

int main()
{
#if 1
    //for (int i = 0; i < 0; i++)
    //{
    //    pool.Employ();
    //    pid_t pid = fork();
    //    if (pid > 0)
    //    {
    //        printf("father [%d]\n", pool.GetCurrentDepth());
    //    }
    //    else 
    //    {
    //        pool.Fire();
    //        printf("child [%d]\n", pool.GetCurrentDepth());
    //        return 0;
    //    }
    //}
    sleep(5);
    printf("father last[%d]\n", pool.GetCurrentDepth());
    return 0;
#endif
#if 0
    MySemaphore mySem;
    mySem.Init(12345);

    pid_t pid = fork();

    if (pid > 0)
    {
        printf("father 1\n");
        mySem.Lock();
        printf("father 2\n");
        sleep(5);
    }
    else
    {
        sleep(1);
        MySemaphore mySem;
        mySem.Init(12345);
        printf("child 1\n");
        mySem.Lock();
        printf("child 2\n");
        return 0;
    }

    sleep(5);
#endif

    return 0;
}

