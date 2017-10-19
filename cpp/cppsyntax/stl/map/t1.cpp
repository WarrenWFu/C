/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:使用指针作为map的value，检查是可以实现多态的
 *
*******************************************************************************/
#include <iostream>
#include <map>
#include <string>

using namespace std;

class FooBasic
{
protected:
    int num1;
public:
    virtual void func() { cout << "from basic" << endl;}
};

class FooDerived:public FooBasic
{
    int num2;
public:
    void func() { cout << "from derived" << endl;}
};

void func1(FooBasic* val)
{
    map<string, FooBasic*> map1;

    map1.insert(pair<string,FooBasic*>("1", val));

    map1["1"]->func();
}

int main()
{
    FooDerived *fd = new FooDerived();

    func1(fd);

    fd->func();

    return 0;
}

