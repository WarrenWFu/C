/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:getenv的变量对于进程来说是不变的，是否存在系统调用可以重新载入？
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
    cout << getenv("MYTEST") << endl;

    string strTest;
    std::getline(cin, strTest);

    cout << getenv("MYTEST") << endl;

    return 0;
}

