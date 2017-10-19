/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:如果只用到类的数据成员而没有用到函数，是可以不用.cpp文件
 *
*******************************************************************************/
#ifndef __T52__
#define __T52__
#include "t52ori.hpp"

using namespace std;

class Foo:public FooOri
{
public:
    virtual ~Foo();

    void func1() {}
    int func2();
    Foo *getInstance(); 
};

#endif

