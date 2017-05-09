/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用string的c_str函数
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
    string str1("1");
    
    //if (1 == ((int)str1.c_str()[0] - 48))
    if (1 == atoi(str1.c_str()))
        cout << "equal" << endl;


    return 0;
}

