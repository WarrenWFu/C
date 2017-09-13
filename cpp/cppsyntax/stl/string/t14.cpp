/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * @brief:注意使用+=操作string的时候，如果C字符串中包含'\0'，那么会导致截断
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    char szStr[10] = {0};

    memcpy(szStr, "ab", 2);
    memcpy(szStr+3, "12", 2);

    string strA;

    strA += szStr;

    cout << strA.size() << endl;
    cout << strA << endl;

    return 0;
}

