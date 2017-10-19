/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:注意创建pair本身就会调用构造函数，insert的时候还是相当于进行了拷贝
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
    pair<string, Foo> pairTemp;
    map<string, Foo> map1;
    map1.insert(pairTemp);

    string strTemp;
    std::getline(cin, strTemp);


    return 0;
}

