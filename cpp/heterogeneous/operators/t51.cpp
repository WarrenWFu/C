/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:查看typeid的返回值
 *
*******************************************************************************/
#include <dlfcn.h>
#include <iostream>
#include <string>
#include "t52.hpp"

using namespace std;
using namespace upp;

int MYFUNC()
{
    void *handle = NULL;

    handle = dlopen("./libtest2.so", RTLD_NOW);
    if (!handle) 
    {
        cout << "加载失败" << endl;
        cout << string(dlerror()) << endl;
        return -1;
    }
    dlerror();    /* Clear any existing error */
    
    MyInfo *pMyInfo = (MyInfo*)dlsym(handle, "myInfos");
    if (pMyInfo == NULL)
    {
        cout << "get symbol failed" << endl;
        return -1;
    }

    if (pMyInfo[0].c_str1 != NULL)
        cout << "1:" << pMyInfo[0].c_str1 << endl; 
    if (pMyInfo[0].c_str2 != NULL)
        cout << "2:" << pMyInfo[0].c_str2 << endl; 
    if (pMyInfo[0].c_str3 != NULL)
        cout << "3:" << pMyInfo[0].c_str3 << endl; 

    //delete pMyInfo;//这里不能delete

    dlclose(handle);

    return 0;
}
