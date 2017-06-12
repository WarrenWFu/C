/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查函数声明时如果throw(),则函数中抛出的异常无法被程序catch
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

//void func() throw()
void func() 
{
    throw 1;
    //throw nullptr;注意这种方式可以跑出NULL指针，如果抛出NULL则会被当做int 0
}


int main()
{
    try
    {
        func();
    }
    catch(...)
    {
        cout << "get" << endl;
    }

    return 0;
}

