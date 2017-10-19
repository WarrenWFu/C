/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:函数指针的使用，注意对一个NULL的函数指针使用()也会报段错误的
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>

#define CREATEFUNC(str) str()
typedef int (*pFunc)();



using namespace std;

int func()
{
    return 10;
}


int main(int argc, char* argv[])
{
    map<string, pFunc> m1;

    m1["1"] = func;

    int iNum = m1[argv[1]]();

    cout << iNum << endl;
    
    return 0;
}

