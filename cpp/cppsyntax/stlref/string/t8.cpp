/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用默认的构造函数或者“”初始化的string为空
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    return 0;
}
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str1 = "";
    if (str1.length() == 0)
    {
        cout << "length == 0" << endl;
    }

    if (str1.empty())
    {
        cout << "empty" << endl;
    }

    return 0;

}
