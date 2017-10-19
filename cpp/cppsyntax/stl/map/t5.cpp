/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:map中的value可以使用指针实现多态，可以用dynamic_cast转换，但是
 * 记住基类至少要有一个virtual函数，否则报错！！！
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

class Foo2
{
public:
    Foo2():str0("123") {}
    virtual ~Foo2() {}
    string str0;
};

class Foo3:public Foo2
{
public:
    Foo3():str1("abc") {}
    string str1;
};

class Foo
{
public:
    Foo():map1() {}
    map<string, Foo2*> map1;
};

int main()
{
    Foo foo;
    Foo3 foo3;

    foo.map1["1"] = &foo3;

    cout << (dynamic_cast<Foo3*>(foo.map1["1"]))->str1 << endl;
//    cout << ((Foo3*)(foo.map1["1"]))->str0 << endl;
    cout << ((Foo3*)(foo.map1["1"]))->str1 << endl;

    return 0;
}

