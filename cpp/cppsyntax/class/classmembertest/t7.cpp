/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用类的static变量
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Foo
{
public:
    Foo();

    string str1;
    //static int LENGTH = 10;这句会报错，c++不能在类声明时初始化
    static int LENGTH;
};

int Foo::LENGTH = 10;

Foo::Foo()
{}

int main()
{
    Foo foo;
    
    cout << Foo::LENGTH << endl;


    return 0;
}

