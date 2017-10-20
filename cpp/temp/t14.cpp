/**
 * @file        
 * @brief       
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <map>
#include <typeinfo>

using namespace std;

class foo
{
public:
    virtual ~foo(){}
};

class bar: public foo
{};

typedef int (*functype) (int);

functype bar() {
    int foo(int i)
    {
        return i*2;
    }

    return foo;
}

int main(int argc, char* argv[])
{
    functype ft = bar();

    cout << ft(1) << endl;

    return 0;
}

