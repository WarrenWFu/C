/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:函数中的异常被捕捉了，先执行局部变量的析构函数，然后再执行catch
 * 中的语句，如下面先执行from destructor，然后执行do nothing
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Foo
{
public:
    Foo() {m_iCount = ++ s_iCount; cout << "from constructor " << m_iCount << endl;}
    ~Foo() {cout << "from destructor " << m_iCount << endl;}
    static int s_iCount;
    int m_iCount;
};

int Foo::s_iCount = 0;

void func2();
void func3();

void func1()
{
    Foo foo;
    try
    {
        func2();
    } 
    catch (...) 
    {
        func3();
    }
}

void func2()
{
    Foo foo;
    throw 1;
    Foo foo2;
}

void func3()
{
    cout << "do nothing" << endl;
}

int main()
{
    cout << "begin" << endl;
    func1();
    cout << "end" << endl;

    return 0;
}

