/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:一个简单的使用全局变量的方式，使用 g++ t4.cpp t42.cpp编译
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

extern int g_iNum;

int main()
{

    cout << "------" << g_iNum << endl;

    return 0;
}

