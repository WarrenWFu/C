/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:引用作为参数，效果和指针是一样的
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

void foo(int &iA)
{
    iA = 3;
}

int main()
{
    int iA = 10;

    foo(iA);
    cout << iA << endl;

    return 0;
}

