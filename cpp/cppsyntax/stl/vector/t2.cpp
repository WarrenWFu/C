/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:检查vector作为指针使用的情况,使用起来和一般的类型指针没什么区别
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Foo
{
public:
    Foo(int val):iNum(val){}
    int iNum;
};

void func(vector<string*>* pV, string *pStr)
{
    pV->push_back(pStr);
}

using namespace std;

int main()
{
    vector<string*> v1;
//    Foo foo1(10);
    string str1("abc");

    cout << v1.size() << endl;

    func(&v1, &str1);

    cout << v1[0]->c_str() << endl;
    cout << v1.size() << endl;

    return 0;
}

