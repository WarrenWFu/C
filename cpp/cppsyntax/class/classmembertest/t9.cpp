/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:类成员的默认构造函数在类实例化的时候会被调用
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Foo1
{ 
public:
    Foo1() 
    {
        cout << "from Foo1" << endl;
    }
    ~Foo1()
    {
        cout << "from Foo1 des" << endl;
    }

};

class Foo2
{ 
public:
    Foo1 foo1;
};

int main()
{
    Foo2 foo2;

    Foo2 *pFoo2 = new Foo2();

    delete pFoo2;

    return 0;
}

