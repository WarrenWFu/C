/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查string的erase函数,注意如果其中rfind没有找到的话用erase会报错
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{

    string str1 = "abc";

    cout << str1 << endl;

    str1.erase(str1.rfind("d"));

    cout << str1 << endl;

    return 0;
}

