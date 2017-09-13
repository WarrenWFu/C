/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

typedef struct Foo
{
public:
    char c1;
    int i2;
    //short ss2;
    //short ss3;
    //short ss4;
    //short ss5;
    //char c2;
    long l;
    int i;
    char c;
    short ss;
}Foo;

int main()
{
    cout << sizeof(Foo) << endl;

    void *pBuffer = malloc(sizeof(Foo)*10);
    memset(pBuffer, 0x00, sizeof(pBuffer));

    Foo *pFoo = new (pBuffer) Foo();
    Foo *pFoo1 = new ((char *)pBuffer + sizeof(Foo)) Foo();

    free(pBuffer);

    return 0;
}

