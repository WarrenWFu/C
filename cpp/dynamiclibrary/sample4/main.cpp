/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:测试通过动态加载实现多态，在程序中include基类头文件，派生类中重写
 * 基类的virtual方法，之后通过g++ -fpic -shared foo2.cpp -o libtest2.so来生成动
 * 态库，其中是否需要strip有待商榷，然后使用g++ main.cpp -ldl生成a.out，直接执行
 * ./a.out就可以调用到foo2.cpp生成的动态库。
 * 注意事项
 * 1.编译时不需要链接动态库，也不需要定义LD_LIBRARY_PATH，实现真正的动态加载
 * 2.也不需要头文件，只要包含基类的头文件就可以
 * 3.调用到的继承类中的函数，基类中要有，可以是纯虚函数
 * 4.如果动态库中用到了其他动态库中的函数或类，需要编译这个动态库的时候进行链接
 * 所以动态库之间最后减少关联，否则会使动态调用变得繁琐而复杂
 *
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <typeinfo>
#include <dlfcn.h>
#include "foo1.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    Foo1 *pFoo1 = NULL;
    void *handle = NULL;

    handle = dlopen("./libtest2.so", RTLD_NOW);
    if (!handle) 
    {
        cout << "加载失败" << endl;
        cout << string(dlerror()) << endl;
        return -1;
    }
    dlerror();    /* Clear any existing error */

    Foo1 *(*pFunc)() = (Foo1* (*)())dlsym(handle, "createFoo2");
    if (pFunc == NULL)
    {
        cout << "get symbol failed" << endl;
        return -1;
    }
    printf("address %p\n", pFunc);

    pFoo1 = pFunc();

    cout << pFoo1->func1() << endl;
    cout << pFoo1->func2() << endl;
    cout << typeid(*pFoo1).name() << endl;

    delete pFoo1;

    dlclose(handle);

    return 0;
}
