/**
 * @file        
 * @brief       检查函数声明时如果throw(),则函数中抛出的异常无法被程序catch
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/
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
    //catch(exception &e) //如果用这句来捕捉则会coredown，所以...不能少
    catch(...)
    {
        cout << "get" << endl;
    }

    return 0;
}

