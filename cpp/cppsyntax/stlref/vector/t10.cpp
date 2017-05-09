/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用指针指向vector时，不能够进行加减操作,注意vector还是和数组有
 * 区别的
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string*> v1;
    string str1("abc");
    string str2("def");

    v1.push_back(&str1);
    v1.push_back(&str2);

    string *pStr = v1[0];

    cout << *pStr << endl;
    cout << pStr[0] << endl;
    cout << pStr[1] << endl;//此句打出来是乱码

    return 0;
}

