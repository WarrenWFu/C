#ifndef __FOO1_HPP__
#define __FOO1_HPP__
#include <string>

class Foo1
{
public:
    Foo1():str1("123"){}
    virtual ~Foo1();

    int func(std::string&);

    std::string str1;
};


#endif
