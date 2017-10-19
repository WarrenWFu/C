/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * @brief:将integer转成string, 也可以使用char数组过度，如果需要的话
 *
*******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    int iNum = 95;

    string str1 = iNum < 10? string(1, (char)(iNum + 48)): 
            string(1, (char)(iNum/10 + 48)) + string(1, (char)(iNum%10 + 48));


    cout << str1 << endl;

    return 0;
}

