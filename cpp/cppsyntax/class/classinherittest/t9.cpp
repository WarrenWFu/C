/**
 * @file        
 * @brief       匹配重载函数时，不需要协变的函数优先于需要协变的函数
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>

using namespace std;

class Foo
{
public:
    void bar(const string &s)
    {
        cout << "from bar1" << endl;
        cout << s << endl;
    }

    void bar(const char *pSz)
    {
        cout << "from bar2" << endl;
        cout << pSz << endl;
    }

    void func(int i)
    {
        cout << "from func1" << endl;
        cout << i << endl;
    }

    void func(double d)
    {
        cout << "from func2" << endl;
        cout << d << endl;
    }

};

int main()
{
    Foo foo;
    string s("123");

    foo.bar(s);     //调用第一个函数
    foo.bar("abc"); //调用第二个函数

    foo.func(1);    //调用第三个函数
    foo.func(1.1);  //调用第四个函数

    return 0;
}

