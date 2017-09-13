/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用匿名实例push_back，完全是可以的
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> v1;
    string str1 = "abc";
    string str2 = "123";

    v1.push_back(string(str1 + str2));

    cout << v1[0] << endl;

    return 0;
}

