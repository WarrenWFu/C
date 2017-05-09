/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include<iostream>
#include<string>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
    int iArray[] = {1, 2, 3, 4};
    int* pA = iArray;
    int* pB = &iArray[2];

    printf("%p\n", pA);
    printf("%p\n", pB);

    cout << pB - pA << endl;

    return 0;
}
