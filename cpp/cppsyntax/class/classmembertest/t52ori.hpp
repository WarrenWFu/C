/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:如果只用到类的数据成员而没有用到函数，是可以不用.cpp文件
 *
*******************************************************************************/
#ifndef __T52ORI__
#define __T52ORI__
#include <string>

using namespace std;

class FooOri
{
public:
    FooOri();
    virtual ~FooOri();

    virtual void func1() = 0;
    virtual int func2() = 0;
    string str1;
};
#endif

