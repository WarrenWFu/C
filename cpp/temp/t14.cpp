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

int main(int argc, char* argv[])
{
    long long *l;

    printf("大小是%d\n", sizeof(l));

    return 0;
}

