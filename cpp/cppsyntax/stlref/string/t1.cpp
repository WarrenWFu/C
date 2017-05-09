/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:string的find函数只有找到给定的完整string才会不等于string::npos
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    string str1 = "abc is 123.";
    string str2;

    cout << str1 << endl;

    while (true)
    {
        getline(cin, str2);
        if (str2 == "q")
            break;

        if (str1.find(str2) != string::npos)
        {
            cout << "找到，未知在：" << str1.find(str2) << endl;
        }
        else
        {
            cout << "未找到" << endl; 
        }
    
    }

    return 0;
}

