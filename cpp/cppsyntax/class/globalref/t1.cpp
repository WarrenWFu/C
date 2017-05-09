/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

class Foo
{
public:
    Foo(){cout << "from constructor" << endl;}
    ~Foo(){cout << "from destructor" << endl;}
};

Foo foo;

int main()
{
    sleep(1);
    _exit(0);
}

