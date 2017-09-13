/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * @brief:检查string函数，返回位置的话总是以0开头
 *
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
int main()
{
    string str1 = "123456789";

    cout << string(str1, 3)<< endl;

    return 0;
}

