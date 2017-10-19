/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:抽象基类的构造函数和析构函数,在子类的构造和析构过程中同样会
 * 被调用，记住抽象基类只是不能被实例化，不代表他不会被分配内存，所以需要加的
 * virtual不能省
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Foo
{
public:
    Foo():str1("abc") { cout << "from base class constructor" << endl; }
    virtual ~Foo() { cout << "from base class destructor" << endl; }
    virtual void func() = 0;
private:
    string str1;
};

class Foo1:public Foo
{
public:
    void func() {}
};


int main()
{
    Foo1 *pFoo1 = new Foo1();

    delete pFoo1;

    return 0;
}

