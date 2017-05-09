/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:如果纯虚函数的参数是基类，那么实体类中对纯虚函数的实现的时候使用
 * 派生类作为参数，是不行的，必须也是一个基类
 *
*******************************************************************************/
#include <iostream>
#include <string>

class Bar1
{};

class Bar2: public Bar1
{};

class Foo1
{
public:
    Foo1(){};
    virtual ~Foo1(){};

    virtual void func(Bar1 *) = 0;
};

class Foo2:public Foo1
{
public:
    Foo2(){};
    ~Foo2(){};

    //这个函数才是上面纯虚函数的实现
    void func(Bar1 *){}
    //这个函数不是上面纯虚函数的实现void func(Bar2 *){}
};

using namespace std;

int main()
{
    Foo2 foo2;

    return 0;
}

