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

#pragma pack(2)

struct Foo
{
    int m_iA;
    char m_cA;
};

int main()
{
    cout << sizeof(struct Foo) << endl;
    cout << sizeof(long double) << endl;
    return 0;
}

