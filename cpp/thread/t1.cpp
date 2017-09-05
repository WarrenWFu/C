/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:获取线程返回值的方式，线程抛出的异常无法catch到
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

using namespace std;

void *func(void *val)
{
    cout << "thread start" << endl;
    sleep(3);
    cout << "thread end" << endl;
    throw 1;
    char *p = "return";
    return (void *)p;
}

int main()
{
    pthread_t pthread;
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);

    try
    {
        if (pthread_create(&pthread, &attributes, func, NULL))
        {
            cout << "创建线程错误,errno[" << errno << "]" << endl;
        }
        pthread_attr_destroy(&attributes);

        for (;;)
        {
            sleep(5);
        }
    }
    catch(...)
    {
        cout << "捕捉到线程异常" << endl;
    }


    //string str1;
    //std::getline(cin, str1);

    void *pRes = NULL;
    if (pthread_join(pthread, &pRes))
    {
        cout << "等待线程错误,errno[" << errno << "]" << endl;
    }
    cout << "线程返回值为[" << (char *)pRes << "]" << endl;

    return 0;
}

