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

using namespace std;

int main()
{
	FILE *fp = NULL;
    fp = fopen("/home/spring/project/qhjk/product/Linux64/bin/123456789012345678901234", "rb");
    if (NULL==fp)
        return -1;

	char pSz[1025] = {0};
    cout << fread(pSz, 1, 1024, fp) << endl;

	cout << pSz << endl;


    return 0;
}
