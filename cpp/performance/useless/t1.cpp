/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:测试for外和for中定义内建变量的性能, 测试发现建在外部速度稍微
 * 快一些
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int iNum = 10; 
    int *pNum = &iNum;

    for(int i = 0; i < 10000000; i ++)
    {
        pNum = &iNum;
    }

    return 0;
}

