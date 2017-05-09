#ifndef __FOO2_HPP__
#define __FOO2_HPP__
#include "foo1.hpp"
#include <string>

class Foo2
{
public:
    Foo2();
    virtual ~Foo2(){ delete pFoo1;}
    int func();

    Foo1 *pFoo1;
    std::string str1;
};

#endif



