/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:测试条件运算符的返回值
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int iA = 2;
    int iB = -1;
    int iC = 3;
    int iD = 4;

    int iRes = ((iA > iB? iA = iB: iA) > iC? iA = iC: iA) > iD? iA = iD:iA;

    cout << iRes << endl;
    cout << "只为测试" << endl;


    return 0;
}

