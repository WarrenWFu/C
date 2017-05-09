#ifndef __F51_HPP__
#define __F51_HPP__

#include <typeinfo>
#include <iostream>

namespace upp
{
    class Foo1
    {};

    class Foo2
    {
        public:
            Foo2(){}
            virtual ~Foo2(){}
    };

    class Foo3: public Foo2
    {
        public:
            Foo3(){}
            ~Foo3(){}
    };

    struct MyInfo
    {
        const char* c_str1;
        const char* c_str2;
        const char* c_str3;
    };
}

#endif
