/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:调用默认赋值重载函数，可以实现私有成员的赋值
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    for (int i = 0; i < 10; i++)
    {
        string *pStr = new string(1, (char)(i + 48)); 

        cout << *pStr << endl;
        cout << hex << pStr << endl;
    }
    


    return 0;
}

