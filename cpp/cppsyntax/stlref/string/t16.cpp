/**
 * @file        
 * @brief       const char数组可以通过=直接转成string
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    const char sz1[] = "abc";
    string s1 = sz1;

    cout << s1 << endl;

    return 0;
}

