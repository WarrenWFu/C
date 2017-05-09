/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:类的const成员变量，只能通过初始化列表来初始化
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Foo
{
public:
    Foo();

    const string str1;
};

Foo::Foo():
    str1("abc")
{}

int main()
{
    Foo foo;

    cout << foo.str1 << endl;

    return 0;
}

