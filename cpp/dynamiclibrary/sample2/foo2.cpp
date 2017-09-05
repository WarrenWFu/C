/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include "foo2.hpp"
#include <iostream>
#include <string>

using namespace std;

Foo2::Foo2():
str1("234")
{
    pFoo1 = new Foo1();
}

int Foo2::func()
{
    cout << "from Foo2::func()" << endl;
    pFoo1->func(str1);
}

