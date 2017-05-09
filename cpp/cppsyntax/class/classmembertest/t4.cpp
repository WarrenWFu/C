/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查抽象类的继承
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

class Foo
{
public:
    virtual void func() = 0;
};

class Foo1:public Foo
{
public:
    virtual void func() = 0;
};

class Foo2:public Foo
{
public:
    void func() {}
};


int main()
{
    Foo2 *pFoo2 = new Foo2();

    return 0;
}

