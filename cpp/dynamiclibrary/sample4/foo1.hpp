#ifndef __FOO1_HPP__
#define __FOO1_HPP__
class Foo1
{
public:
    Foo1(){}
    virtual ~Foo1(){}

    virtual int func1(){ return 1;}
    //virtual int func2(){ return 0;};
    virtual int func2() = 0;
};
#endif
