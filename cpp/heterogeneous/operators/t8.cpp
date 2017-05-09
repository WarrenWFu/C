/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:当捕捉到...异常时，可以直接用throw将它抛出去
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <exception>

using namespace std;

void func1()
{
    //throw 1; //此句用...来捕捉
    throw exception();
}

void func(int val)
{
    try
    {
        func1();
    }
    catch(exception &e)
    {
        cout << "1------" << endl;
        cout << e.what() << endl;
    }
    catch(...)
    {
        cout << "---1---" << endl;
        throw;
    }

}

int main(int argc, char *argv[])
{
    try
    {
        func(argc);
    }
    catch(exception &e)
    {
        cout << "2------" << endl;
        cout << e.what() << endl;
    }
    catch(...)
    {
        cout << "---2---" << endl;
    }

    return 0;
}

