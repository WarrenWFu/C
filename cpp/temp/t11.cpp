#include <iostream>
#include <cstdio>

void foo(void) 
{
    std::cout << "from foo " << std::endl;
}

int main() 
{
    int iA = 123;
    char szA[8] = {0};
    sprintf(szA, "%d", iA);
    std::cout << szA << std::endl;
    return 0;
}

