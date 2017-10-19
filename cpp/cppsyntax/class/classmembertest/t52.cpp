/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:如果只用到类的数据成员而没有用到函数，是否可以不用.cpp文件
 *
*******************************************************************************/
#include <iostream>
#include "t52.hpp"

using namespace std;

Foo::~Foo()
{}

int Foo::func2()
{
    int iNum = 10;
    return iNum;
}

Foo *Foo::getInstance()
{
    return new Foo();
}
