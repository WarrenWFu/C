/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查string的运算符重载
 *
*******************************************************************************/
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
    string str1 = "abc";
    string str2 = "abd";

    set<string> set1;

    set1.insert(str1);
    set1.insert(str2);

    cout << set1.size() << endl;

    return 0;
}


