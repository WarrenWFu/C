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

void foo()
{
    cout << "test" << endl;

}

int main()
{
    string str1 = "123456789";

    foo();

    cout << str1.find('7', 2) << endl;
    cout << str1.substr(1,3) << endl;

    return 0;
}

