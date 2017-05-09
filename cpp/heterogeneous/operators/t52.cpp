#include "t52.hpp"

using namespace upp;

//_init已经过时不建议使用
//void _init()
//{
//    std::cout << "come from _init()" << std::endl;
//}

static void start(void) __attribute__ ((constructor));

void start(void)
{
    std::cout << "come from __attribute__((constructor))" << std::endl;
}

extern "C"
{

static const char *s_className = typeid(Foo1).name();

MyInfo myInfos[2] = {
    //{typeid(Foo1).name(), typeid(Foo2).name(), typeid(Foo3).name()}, {0, 0, 0}};
    {s_className, typeid(Foo2).name(), typeid(Foo3).name()}, {0, 0, 0}};
}

