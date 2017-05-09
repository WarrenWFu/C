/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description: 查看主机字节序的函数,可以考虑用union来实现
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstring>
#include <cfloat>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
    int iNum = 1;
    //int iNum = 257;
    char *pChar = (char *)&iNum;

    cout << (int)pChar[0] << endl;
    cout << (int)pChar[1] << endl;
    cout << (int)pChar[2] << endl;
    cout << (int)pChar[3] << endl;


    return 0;
}

