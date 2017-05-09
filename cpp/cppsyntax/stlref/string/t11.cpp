/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str1;

    std::getline(cin, str1);

    cout << str1 << endl;

    str1 = str1.substr(20);

    cout << str1 << endl;

    return 0;
}

