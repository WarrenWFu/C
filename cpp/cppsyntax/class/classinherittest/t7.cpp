
/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:初始化列表无法初始化从基类继承的成员，引用实现多态和指针一样
 * 可以对引用进行强制类型转换和指针一样
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

class Foo1
{
public:
    Foo1():str1("1"){}
    virtual ~Foo1(){}

    string str1;
};

class Foo2: public Foo1
{
public:
    Foo2(){ str1 = "2";}
    ~Foo2(){}
};

void func(Foo1 &val)
{
    cout << typeid(val).name() << endl;
    cout << val.str1 << endl;
}

int main()
{
    Foo2 foo2;
    Foo1 &pfoo1 = foo2;

    func((Foo2 &)pfoo1);

    return 0;
}
