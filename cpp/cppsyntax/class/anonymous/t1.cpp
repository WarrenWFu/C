/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查匿名类的构造和析构情况,和一般的形参是一样的，进入函数构造，
 * 离开函数析构，但是注意此时函数的参数不能是&和指针, 但可以是const型&
 * 这也可以看做是引用和指针的一个区别
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

class Foo
{
public:
    Foo() {cout << "from constructor" << endl;}
    ~Foo() {cout << "from destructor" << endl;}

};

//void foo( Foo *val) 报错
//void foo( Foo &val) 报错
//void foo( Foo val)  可以
void bar( const Foo &val)
{
    cout << "in foo" << endl;
}

int main()
{
    cout << "before foo" << endl;
    bar(Foo());
    cout << "after foo" << endl;

    return 0;
}

