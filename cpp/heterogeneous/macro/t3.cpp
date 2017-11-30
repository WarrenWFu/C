/**
 * @file        
 * @brief       宏定义中的#是将跟在其后面的变量变成字符串
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/
#include <iostream>
#include <string>

#define func(A) #A
#define func2(B) create##B

using namespace std;

int main()
{
    int iNum = 0;

    cout << string(func(func2(iNum))) + "---" << endl;

    return 0;
}

