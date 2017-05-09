/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

typedef struct Foo1
{
    char c;
    int i;
    double d;
    char c1;
}Foo1;

typedef struct Foo2
{
    Foo1 foo1;
    int i;
    long l;
}Foo2;


int main()
{
    void *p = malloc(sizeof(Foo1) + sizeof(Foo2));
    Foo1 *foo1 = new (p) Foo1();
    Foo2 *foo2 = new ((char *)p + sizeof(Foo1)) Foo2();

    free(p);



    return 0;
}

