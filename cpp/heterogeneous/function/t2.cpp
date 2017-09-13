/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:测试snprintf函数
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main()
{
    int iLength = 2;
    char sBuffer[3+1] = {0};

    snprintf(sBuffer, 3, "%d", iLength);


    cout << string(sBuffer).length() << " " << string(sBuffer) << endl;

    return 0;
}

