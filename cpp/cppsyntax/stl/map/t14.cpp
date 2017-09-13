/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:注意map的clear，是不会执行所指向的对象的析构函数的，要自行释放
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Foo
{
public:
    Foo()
    {
        cout << "from constructor" << endl;
    }
    ~Foo()
    {
        cout << "from destructor" << endl;
    }
};

int main()
{
    map<string, Foo*> map1;

    cout << map1.size() << endl;
    Foo *pFoo = map1["123"];

    if (pFoo == NULL)
        cout << "NULL" << endl;
    else
        cout << "Not NULL" << endl;

    cout << map1.size() << endl;

    return 0;
}

