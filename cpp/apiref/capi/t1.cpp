/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:rename实现移动文件
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <errno.h>

using namespace std;

int main()
{
    cout << getenv("HOME") << endl;
    //string strName(getenv("HOME"));
    //cout << string(strName + "/tt1").c_str() << endl;
    cout << rename("ttt", "./tt1/tt2") << endl;
    cout << errno << endl;


    return 0;
}

