/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

void foo(const string& abc="123")
{
    cout << abc << endl;
}

int main()
{
    string abc = "123";
    foo();
    return 0;
}

