/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:检查vector中存放指针的使用，注意delete的时候要用取址符
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
    Foo():str1("abc") {}
    string str1;
};

int main()
{
    vector<Foo *> v1;

    Foo *pFoo = new Foo();

    v1.push_back(pFoo);

    vector<Foo *>::iterator iter = v1.begin();
    cout << (*iter)->str1 << endl;
    cout << pFoo->str1 << endl;

    delete *iter;

    v1.erase(iter);
//    cout << pFoo->str1 << endl; 此句报错，因为已经析构

    return 0;
}

