/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用auto通过初始化值的类型来确定变量的类型，加快开发速度，但是 初始化不能省略。
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    auto fNum = 0.12f;
    auto dNum = 0.13;

    cout << sizeof(fNum) << endl;
    cout << sizeof(dNum) << endl;

    return 0;
}

