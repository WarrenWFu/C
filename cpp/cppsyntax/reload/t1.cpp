/**
 * @file        
 * @brief  注意两个原型相同的函数，哪怕不是成员函数也是可以重载的     
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>

using namespace std;

int foo(int i) {
    cout << "from foo1" << endl;
    return 0;
}

//int foo(int i) { //这句会报重复定义
int foo(int i, int v) {
    cout << "from foo2" << endl;
    return 0;
}

int main()
{
    foo(0);
    foo(0, 0);

    return 0;
}

