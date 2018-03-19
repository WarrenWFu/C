/**
 * @file        
 * @brief       C++的string是可以修改的
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
    string s = "123";
    cout << s << endl;
    s.replace(0, 1, "a");

    cout << s << endl;

    return 0;
}

