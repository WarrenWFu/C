/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:继承重写static函数,其实相当于两个位于不同名称空间中的函数,关于其
 * 能否多态有待确认
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Foo1
{
public:
    virtual ~Foo1(){}
    static int func1(int);
};

int Foo1::func1(int val)
{
    return val + 1000;
}

class Foo2:public Foo1
{
public:
    static int func1(int);
};

int Foo2::func1(int val)
{
    return val + 2000;
}

int main()
{
    cout << Foo1::func1(1) << endl;
    cout << Foo2::func1(1) << endl;

    return 0;
}

