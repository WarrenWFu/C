/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:查看typeid的返回值
 * 使用g++ -fPIC -shared t52.cpp -o libtest2.so
 * 使用g++ -fPIC -shared t51.cpp -o libtest.so -L. -ltest2
 * 使用g++ t5.cpp -ldl
 *
*******************************************************************************/
#include <dlfcn.h>
#include <iostream>
#include <string>
#include "t52.hpp"

using namespace std;
using namespace upp;

int main()
{
    void *handle = NULL;

    handle = dlopen("./libtest.so", RTLD_NOW);
    if (!handle) 
    {
        cout << "加载失败" << endl;
        cout << string(dlerror()) << endl;
        return -1;
    }
    dlerror();    /* Clear any existing error */
    
    int (*pFunc)()= (int (*)())dlsym(handle, "_Z6MYFUNCv");
    if (pFunc == NULL)
    {
        cout << "get symbol failed" << endl;
        return -1;
    }

    if (pFunc() != 0)
        cout << "func failed" << endl;

    dlclose(handle);

    return 0;
}
