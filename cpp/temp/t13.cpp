/**
 * @file        
 * @brief       获取数组元素个数
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
    const char *sA[] = {"12", "123", "1"};

    cout << sizeof(sA)/sizeof(char *) << endl;

    const string s(argv[1]);
    if (s[0] != '0' && 0 == atoi(s.c_str()))
    {
        cout << "no" << endl;
    }
    else 
    {
        cout << atoi(s.c_str()) << endl;
    }

    return 0;
}

