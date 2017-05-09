#include <stdio.h>

typedef struct Foo
Foo;

int main()
{
//    printf("[%d]\n", sizeof(Foo));
    printf("[%d]\n", sizeof(int));
    printf("[%d]\n", sizeof(long));
    printf("[%d]\n", sizeof(long long));
    printf("[%d]\n", sizeof(Foo*));

    return 0;
}
