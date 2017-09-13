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
    map1.insert(pair<string, Foo*>("123", new Foo()));

    string strTemp;
    std::getline(cin, strTemp);

    delete map1["123"];//这句不能少
    map1.clear();


    return 0;
}

