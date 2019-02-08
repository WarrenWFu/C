/**
 * @file        
 * @brief       类中有一个域指向自身，这种设计在JS的Window对象的window属性中存在
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
 */

#include <iostream>
#include <string>

using namespace std;

class Foo {
public:
    Foo *pThis;
    string sName;
};

int main(int argc, char *argv[])
{
    Foo foo;
    foo.pThis = &foo;
    foo.sName = "Foo";

    cout << foo.pThis->sName << endl;

    return 0;
}

