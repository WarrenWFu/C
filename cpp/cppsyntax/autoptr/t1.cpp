/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Foo
{
public:
    Foo()
    { 
        iA = 10;
        strA = "abc";
    }
    ~Foo(){}

    int getIA()
    {
        return iA;
    }

    string getStrA()
    {
        return strA;
    }

    void printStrA()
    {
        cout << strA << endl;
    }

    int    iA;
    string strA;
};

int main()
{
    auto_ptr<Foo> autoPtr(new Foo());

    cout << autoPtr->getIA() << endl;
    cout << autoPtr->getStrA() << endl;
    autoPtr->printStrA();

    return 0;
}

