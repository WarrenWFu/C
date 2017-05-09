/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:注意这种map的初始化方式
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

class Foo
{
public:
    Foo():map1(){}

    map<string, string> map1;
    
};

int main()
{
    Foo foo;

    foo.map1["1"] = "a";

    return 0;
}

