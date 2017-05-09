/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用multimap
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Foo
{};

int main()
{
    multimap<string, Foo*> m1;
    Foo foo;
    Foo foo2;

    m1.insert(pair<string, Foo*>("1", &foo));
    m1.insert(pair<string, Foo*>("1", &foo2));

    cout << m1.size() << endl;


    return 0;
}

