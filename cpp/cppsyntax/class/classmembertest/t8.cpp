/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:如果只有头文件是可以用默认的那些函数的，如默认构造，默认析构，
 * 默认拷贝函数，但是virtual的函数一定要定义，拷贝应该考虑深拷贝，浅显拷贝问题
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include "t8.hpp"

using namespace std;

int main()
{
    vector<Foo*> v1;

    Foo *foo = new Foo();
    foo->str1 = "123";
    foo->dNum1 = 1.1;

    v1.push_back(new Foo(*foo));
    v1.push_back(new Foo(*foo));
    v1.push_back(new Foo(*foo));

    cout << v1[0]->str1 << endl;
    cout << v1[0]->dNum1 << endl;
    cout << v1[1]->str1 << endl;
    cout << v1[1]->dNum1 << endl;
    cout << v1[2]->str1 << endl;
    cout << v1[2]->dNum1 << endl;

    delete foo;

    delete v1[0];
    delete v1[1];
    delete v1[2];

    return 0;
}

