/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <dlfcn.h>
#include "pub.hpp"

using namespace std;

typedef struct 
{

}dso_handle_t;

int main()
{
    //func();
#if 0
    int flags = RTLD_LAZY;
    dso_handle_t *mHandle = (dso_handle_t*)dlopen("./libtest.so", flags);

    const char*p = dlerror();
    if(!mHandle)
    {
        cout << "加载失败, 原因[" << p << "]" << endl;
    }

    typedef void (*create)();

    create pFun = (create)dlsym((void*)mHandle, "create");
    pFun();
#endif

    return 0;
}

