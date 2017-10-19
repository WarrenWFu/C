/**
 * @file        
 * @brief       通过增加判断条件可以使函数互相调用
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>

using namespace std;

void bar(bool);

void foo(bool b)
{
    if (b)
        bar(true);

    cout << "foo" << endl;
}

void bar(bool b)
{
    if (b)
        foo(false);

    cout << "bar" << endl;
}


int main()
{
    foo(true);

    return 0;
}

