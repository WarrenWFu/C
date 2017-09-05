/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * @brief:调用默认赋值重载函数，可以实现私有成员的赋值
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{

    string str1("1bc");
    int iNum = 1;

    if (iNum+48 == str1[0])
        cout << str1[1] << endl;

    return 0;
}

