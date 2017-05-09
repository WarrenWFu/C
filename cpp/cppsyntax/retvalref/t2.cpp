/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Foo
{};

Foo *func(bool val)
{
    if(val)
        return new Foo;
    else
        return NULL;

}

int main(int argc, char *argv[])
{
    bool bTest = argc > 1? true: false;
    func(bTest);

    return 0;
}

