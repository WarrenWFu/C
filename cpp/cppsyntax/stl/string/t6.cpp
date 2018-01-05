/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * @brief:使用string的c_str函数
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>

using namespace std;

const string foo(int i)
{
    char szBuf[11] = {0};

    snprintf(szBuf, 10, "%d", i);

    return string(szBuf);
}

int main()
{
    cout << foo(12345) << endl;

    return 0;
}

