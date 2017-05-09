/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <utility>
#include <memory>

using namespace std;

class Foo
{
public:
    Foo() { cout << "from constructor" << endl;}
    ~Foo() { cout << "from destructor" << endl;}
};

int main()
{
    auto_ptr<Foo> pa(new Foo());

    cout << "-----------------------" << endl;

    return 0;
}

