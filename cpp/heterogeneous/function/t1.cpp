/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:测试使用参数数目可以变的函数
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdarg>

using namespace std;

void foo(int amount = 0,...);

int main(int argc, char *argv[])
{
    //这里不能直接传字符串，而要构造string
    foo(3, string("abc"), string("12"), string("=_="));
    foo();
    foo(2, string("12"), string("=_="));

    return 0;
}

void foo(int amount,...)
{
    va_list vl;
    string str1;
    va_start(vl, amount);
    for (int i = 0; i < amount; i ++)
    {
        str1 = va_arg(vl, string); 
        cout <<  str1 << endl;
    }

    va_end(vl);
}
