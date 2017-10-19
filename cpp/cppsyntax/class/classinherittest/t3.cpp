/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:将不想要被使用的函数声明为private并不要给出定义，可以在编译阶段
 * 就防止这个函数被调用，同时因为是private变量，继承类无法直接进行修改
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

class Foo
{
public:
    Foo():str1("abc") {}

    const string &getStr1() { return str1; }
protected:
    string str1;
private:
    void setStr1(const string&);
};

class Foo1:public Foo
{
public:
    void setStr1(const string& val) { str1 = val;}

};

int main()
{
    Foo1 *pFoo = new Foo1();

//    pFoo->setStr1();报错
    cout << pFoo->getStr1() << endl;

    pFoo->setStr1("123");
    cout << pFoo->getStr1() << endl;

    return 0;
}

