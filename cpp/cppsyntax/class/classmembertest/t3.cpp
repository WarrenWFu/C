/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:在初始化列表中调用基类的构造函数
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

class Foo
{
public:
    Foo(const string& val):str1(val) {}
    const string& getStr1() const { return str1; }
   
private:
    string str1;
};

class Foo1:public Foo
{
public:
    Foo1(const string& val):Foo::Foo(val) {}

};

int main()
{
    Foo1 *pFoo1 = new Foo1("abc");

    cout << pFoo1->getStr1() << endl;

    return 0;
}

