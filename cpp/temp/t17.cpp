/**
 * @file        
 * @brief       编译会报错，无法将类的成员方法作为回调函数使用
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
 */

#include <iostream>
#include <string>

typedef void (*FuncType)();

using namespace std;

class Foo {
public:
    int v1;

    void func1() {
        cout << v1 << endl;
    }
};

void func2() {
    cout << "from func2" << endl;
}

void testFunc(FuncType pFunc) {
    pFunc();
}

int main(int argc, char *argv[])
{
    Foo foo;
    foo.v1 = 1;
    testFunc(func2);
    foo.func1();

    return 0;
}

