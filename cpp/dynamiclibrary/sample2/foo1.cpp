/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include "foo1.hpp"

using namespace std;

Foo1::~Foo1()
{
    cout << "from Foo1::~Foo1()" << endl;
}

int Foo1::func(std::string &val)
{
    return val.length();
}
