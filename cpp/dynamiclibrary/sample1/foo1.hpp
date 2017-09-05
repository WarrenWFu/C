#ifndef __FOO1_HPP__
#define __FOO1_HPP__

#include <string>
#include "foo1ori.hpp" 

class Foo1:public Foo1Ori
{
public:
    Foo1():str1("abc") {}
    void func1();
private:
    std::string str1;
};
#endif


