/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include "tc_autoptr.h"

using namespace std;
using namespace tars;

class Foo:public TC_HandleBase
{
public:
    Foo()
    {
        i1 = 1;
        s1 = "abc";
    }

    virtual ~Foo()
    {
        cout << " from ~Foo()" << endl;
    }

    int i1;
    string s1;
};

int main()
{
    TC_AutoPtr<Foo> ap = new Foo();

    return 0;
}

