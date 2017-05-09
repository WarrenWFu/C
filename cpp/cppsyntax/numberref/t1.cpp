/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查double型的与0比较问题,一般可以使用 dNum < 0.0001 && dNum > -0.0001
 * 来进行0判断
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    double dNum = 0.0;
    double dNum1 = 2.0000000001;
    double dNum2 = 2.0;
        

    //if (dNum2 - dNum1 > 1e-7)
    if (dNum2 - dNum1 != 0)
    {
        cout << "not equal" << endl; 
    }
    else
    {
        cout << "equal" << endl; 
    }

    cout << 1e-4 << endl;
    cout << -1e-4 << endl;

    return 0;
}

