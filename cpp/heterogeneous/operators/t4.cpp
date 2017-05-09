/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查.操作符和->顺序,两者是平级的，所以从左到右执行
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>

using namespace std;

class Foo2
{
public:
    Foo2():iNum(5) {}
    int iNum;
};
class Foo1
{
public:
    Foo2 foo2;
};

int main()
{
    Foo1 *pFoo1 = new Foo1();

    cout << pFoo1->foo2.iNum << endl;

    return 0;
}

