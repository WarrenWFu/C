/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用double的最大值，注意要包括cfloat
 *
*******************************************************************************/
#include <cstdio>
#include <cfloat>

int main()
{
    printf("保留全部精度的double类型正数的最小值:%e\n",DBL_MAX);

    double dNum = 100.0;

    if (dNum < DBL_MAX)
        printf("<\n");

    return 0;

}
