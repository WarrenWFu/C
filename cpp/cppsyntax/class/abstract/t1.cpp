/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:简单的抽象类使用，foo为抽象类，foo1是其派生类
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include "foo1.hpp"

using namespace std;

int main()
{
    //Foo1 foo1;
    Foo1 *pFoo1 = new Foo1();

    pFoo1->func();

    return 0;
}

