/**
 * @file        
 * @brief       引用作为参数，效果和指针是一样的
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/
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

