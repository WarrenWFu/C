/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:如果只用到类的数据成员而没有用到函数的话，是可以只包含头文件的，
 * 相当于这个类就是C里面的结构体，如果这个头文件中不包含任何函数的定义的话，那么
 * 就不能调用它的任何函数，包括非默认的构造函数，析构函数。
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include "t52.hpp"
#include <dlfcn.h>

using namespace std;

int main(int argc, char *argv[])
{
    void *handle = NULL;
    FooOri *pFoo = NULL;

    handle = dlopen("./libtest.so", RTLD_LAZY);
    if (!handle) 
    {
        cout << "加载失败" << endl;
        cout << string(dlerror()) << endl;
        return -1;
    }
    dlerror();    /* Clear any existing error */

    Foo *(*pTest)();
    pTest = (Foo* (*)())dlsym(handle, "_ZN3Foo11getInstanceEv");
    if (pTest == NULL)
        cout << "没取到" << endl;

    pFoo = pTest();
    int iNum = pFoo->func2();
    cout << iNum << endl;
//
    delete pFoo;

    dlclose(handle);


    return 0;
}

