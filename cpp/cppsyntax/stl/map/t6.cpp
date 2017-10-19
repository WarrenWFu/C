/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:检查map的[]和find的效率,效率没有明显差别，注意两者的返回值，[]
 * 返回引用，如果key不存在，那么就会默认生成一个对象，但是find不会，所以一定要
 * 注意对find判断返回值，而[]注意不要让它去生成不必要的空值
 *  
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

class Foo
{
public:
    Foo():str1("abc") {}
    string str1;
    string str2;
    string str3;
    string str4;
    string str5;
    string str6;
    string str7;
    string str8;
    string str9;
    string str10;
    string str11;
};

int main(int argc, char *argv[])
{
    map<int, Foo> *pMap = new map<int, Foo>();
    map<int, Foo> map1;

    Foo foo = map1[10];

    cout << foo.str1 << endl;

    for (int i = 0; i < 10000; i ++)
    {
        (*pMap)[i] = Foo();
    }

    for (int i = 0; argv[1][0] == '1' && i < 10000; i ++)
    {
        cout << (*pMap)[i].str1 << endl;
    }

    for (int i = 0; argv[1][0] == '2' && i < 10000; i ++)
    {
        cout << pMap->find(i)->second.str1 << endl;
    }

    return 0;
}

