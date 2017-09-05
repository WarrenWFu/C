#include "foo2.hpp"

Foo2::Foo2():
iNum(5)
{}

Foo2::~Foo2()
{}

int Foo2::func1()
{
    return 10;
}

int Foo2::func2()
{
    return iNum;
}

extern "C"
{
    Foo2 *createFoo2()
    {
        return new Foo2(); 
    }
}

