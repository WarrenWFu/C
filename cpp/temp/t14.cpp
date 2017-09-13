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
#include <cstdlib>
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
    map<int, foo*> m;
    m[0] = new foo();
    m[1] = new bar();
    m[2] = new bar();

    for (map<int, foo*>::iterator itor = m.begin(); itor != m.end(); itor ++)
    {
        if (dynamic_cast<bar*>(itor->second))
            cout << "found" << endl;
    }

//    if (dynamic_cast<bar*>(pfA))
//        cout << "pfA" << endl;
//    if (dynamic_cast<bar*>(pfB))
//        cout << "pfB" << endl;

    return 0;
}

