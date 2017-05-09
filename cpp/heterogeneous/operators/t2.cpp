/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:左右移的用法
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int iNum = 1;

    iNum <<= 1;
    cout << iNum << endl;

    iNum <<= 2;
    cout << iNum << endl;

    iNum >>= 3;
    cout << iNum << endl;

    return 0;
}

