/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:测试条件表达式
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

void foo(string str)
{
    cout << str << endl;
}

int main()
{
    int a = 3;
    int b = 2;    

    foo(b > a?"a":"b");

    int iA[10];

    int *pI1 = iA;
    int *pI2 = iA + 9;

    cout << pI2 - pI1 << endl;

    return 0;
}

