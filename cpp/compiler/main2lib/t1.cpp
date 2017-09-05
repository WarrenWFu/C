/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:可以将main函数编入动态库中，用这句编译动态库
 * g++ -fpic -shared t1.cpp -o libtest.so
 * 在用这句编译执行程序
 * g++ t2.cpp -L. -ltest
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include "t2.hpp"

using namespace std;

int main()
{
    cout << foo() << endl;

    return 0;
}

