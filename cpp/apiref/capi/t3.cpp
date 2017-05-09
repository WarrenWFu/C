/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstdio>
#include <sys/time.h>

using namespace std;

int main()
{
    struct timeval start_tv;

    gettimeofday(&start_tv, NULL);

    cout << start_tv.tv_sec << endl;
    cout << start_tv.tv_usec << endl;


    return 0;
}
