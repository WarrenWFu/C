/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

void func(const string &str)
{
    cout << str << endl;
}

int main()
{
    char szBuf[] = "1234abcd";

    char cTmp = szBuf[4];
    szBuf[4] = '\0';
    func(szBuf);
    szBuf[4] = cTmp;
    
    cout << szBuf << endl;

    return 0;
}

