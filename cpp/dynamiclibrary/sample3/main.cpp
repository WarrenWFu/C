/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查.so文件中的值
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <dlfcn.h>

using namespace std;

class PluginBase
{
public:
    PluginBase() {};
    ~PluginBase() {};
};

struct PluginMetaInfo                                                          
{                                                                              
    const char* iface;                                                         
    const char* feature;                                                       
    PluginBase* (*create)();                                                   
    void (*destroy)(PluginBase* c);                                            
};

int main()
{
    void *handle = NULL;

    handle = dlopen("./libpchlselector.so", RTLD_LAZY);
    //handle = dlopen("./libpchlfeeofsender.so", RTLD_LAZY);
    if (!handle) 
    {
        cout << "加载失败" << endl;
        cout << string(dlerror()) << endl;
        return -1;
    }
    dlerror();    /* Clear any existing error */

    PluginMetaInfo *pTest = (PluginMetaInfo*)dlsym(handle, "ZFPT_plugin");
    if (pTest[0].iface != NULL)
    {
        cout << pTest[0].iface << endl;
        cout << pTest[0].feature << endl;
        //cout << pTest[0].iface << endl;

    }
    else 
        cout << "NULL" << endl;

    dlclose(handle);


    return 0;
}

