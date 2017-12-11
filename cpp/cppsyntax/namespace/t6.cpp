/**
 * @file        
 * @brief       命名空间同样可作用于函数
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>

using namespace std;

namespace Foo
{
    void bar()
    {
        cout << "abc" << endl;
    }
}

int main()
{
    Foo::bar();

    return 0;
}

