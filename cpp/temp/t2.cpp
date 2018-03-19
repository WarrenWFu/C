/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    int ns1[] = {1, 2};
    int ns2[] = {1, 3};
    ns1 = ns2;


    return 0;
}

