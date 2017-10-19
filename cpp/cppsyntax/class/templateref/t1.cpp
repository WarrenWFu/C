/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:继承一个模板类，那么调用模板类的方法时，相当于已经传入了类型参数
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

template<typename T>
class Foo
{
public:
    Foo() {}
    virtual ~Foo() {}

    void func1()
    {
        typedef char TMustBeCompleteType[sizeof(T) == 0 ? -1 : 1];
        cout << typeid(T).name() << endl;
    }
};

class Boo3
{};

//class Boo2: public Foo<int> 也是可以的
class Boo2: public Foo<Boo3>
{};


int main()
{
    Boo2 boo2;

    //这里不再需要传入类型参数了
    boo2.func1();

    return 0;
}

