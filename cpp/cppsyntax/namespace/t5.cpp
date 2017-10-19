/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:注意嵌套namespace的使用
 *
*******************************************************************************/
#include <iostream>
#include <string>

namespace Foo0
{
namespace Foo1
{
    class Foo0
    {};
}
}

using namespace std;

int main()
{
    Foo0::Foo1::Foo0 *pFoo01 = new Foo0::Foo1::Foo0();

    delete pFoo01;


    return 0;
}

