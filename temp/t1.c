#include <stdio.h>

void myfflush()
{
    char buf[50];

    fgets((char *) buf, 50, stdin);
}

int main()
{
    myfflush();

    return 0;

}
