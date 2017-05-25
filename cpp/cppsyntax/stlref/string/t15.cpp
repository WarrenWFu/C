/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:最好不要使用如下方式调用，虽然可以，但是会导致不可预知错误
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void func(const string& val)
{
    cout << val << endl;
}

int main(int argc, char *argv[])
{
    string strA(argv[1]);
    string strB(argv[2]);

    func(strA + "/" + strB);

    return 0;
}

