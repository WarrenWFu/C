#ifndef __FOO1_ORI_HPP__
#define __FOO1_ORI_HPP__

#include <string>

class Foo1Ori
{
public:
    Foo1Ori():str0("ori") {}
    virtual void func1() = 0;
private:
    std::string str0;
};
#endif



