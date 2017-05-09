/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:这里动态库中调用了main.cpp中的函数，main又调用了动态库中的函数，
 * 但是只要保证最后解析的时候能找到对应的函数定义就不会又问题,编译命令为
 * g++ -fPIC -g t1.cpp
 * g++ -shared -o libtest.so t1.o
 * g++ -g main.cpp -L. -ltest
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include "t1.hpp"

using namespace std;

void func0()
{
    cout << "from func0" << endl;
}

int main()
{
    func1();
    return 0;
}

