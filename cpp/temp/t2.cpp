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

int main(int argc, char *argv[])
{

    int iNum1 = 10;
    int &iNum2 = iNum1;

    cout << iNum1 << endl;
    cout << iNum2 << endl;

    return 0;
}

