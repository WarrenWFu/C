/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:通过g++ -D_DEBUG或者-D _DEBUG可以在编译时来定义宏_DEBUG
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int a = 1;
    int b = 2;
    int c = 0;
#ifdef _DEBUG
    cout << "test" << endl;
#endif


    cout << a++ << endl;
    cout << a << endl;
    cout << b << endl;

    return 0;
}

