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

using namespace std;

class AbsFoo
{};

class AbsBar
{};

class ConFoo: public AbsFoo
{};

class ConBar: public AbsBar
{};

class AbsFactory
{
public:
    virtual ~AbsFactory(){}
    virtual AbsFoo *createFoo() = 0;
    virtual AbsBar *createBar() = 0;
};

class ConFactory: public AbsFactory
{
public:
    AbsFoo *createFoo()
    {
        cout << "from 1" << endl;
        return new ConFoo();
    }

    virtual AbsBar *createBar()
    {
        return new ConBar();
    }
};

int main()
{
    AbsFactory *pFac = new ConFactory();
    AbsFoo *pFoo = pFac->createFoo();

    return 0;
}

