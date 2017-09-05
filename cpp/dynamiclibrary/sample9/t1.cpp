/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:此测试用于检查链接关系，具体结果查阅linux笔记
 * libtest1.so 依赖 libtest2.so
 * a.out 依赖 libtest1.so
 *
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    return 0;
}
#include "l1.hpp"

int main()
{
    func1();

    return 0;
}

