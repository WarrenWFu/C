#ifndef __FOO2_HPP__
#define __FOO2_HPP__

#include "foo1.hpp"

class Foo2:public Foo1
{
public:
    Foo2();
    ~Foo2();

    virtual int func1();
    virtual int func2();

    int iNum;
};

#endif
