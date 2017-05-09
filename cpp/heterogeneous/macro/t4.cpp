/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用宏定义创建函数，注意使用的时候不要用引号
 *
*******************************************************************************/
#include <iostream>

#define DEFINE_FOR_DYN_CALL(baseclass, subclass, upsubclass) \
extern "C" baseclass *create##upsubclass() \
{ return new subclass(); } \
extern "C" void destroy##upsubclass(baseclass *ptr) \
{ delete ptr; }

class Foo
{
public:
    Foo() { std::cout << "from Foo" << std::endl;}
};

class Bar: public Foo
{
public:
    Bar() { std::cout << "from Bar" << std::endl;}
};

DEFINE_FOR_DYN_CALL(Foo, Bar, BAR)

int main()
{
    Bar bar;

    return 0;
}
