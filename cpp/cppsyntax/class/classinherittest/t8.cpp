/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

class Foo
{
public:
    virtual void poo()
    {
        cout << "from father" << endl;
    }
};

class FooDer: public Foo
{
public:
    void poo()
    {
        cout << "from child" << endl;
    }
};

int main()
{

    Foo foo1 = Foo();
    FooDer foo2 = FooDer();
    Foo *foo1R = &foo1;
    Foo *foo2R = &foo2;

    cout << typeid(foo1R).name() << endl;
    cout << typeid(foo2R).name() << endl;

    return 0;
}

