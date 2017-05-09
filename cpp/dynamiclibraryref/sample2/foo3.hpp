#ifndef __FOO3_HPP__
#define __FOO3_HPP__
#include "foo2.hpp"
#include <string>

class Foo3:public Foo2
{
public:
    Foo3();
    virtual ~Foo3();

    std::string str1;
};
#endif



