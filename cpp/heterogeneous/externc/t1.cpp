/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查使用extern C后typeid不会发生变化
 *
 *******************************************************************************/
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

namespace upp
{
    class PchlSelector
    {};


}

using namespace upp;

extern "C"
{
    const char* strName = typeid(upp::PchlSelector).name();
}
int main()
{
    cout << string(strName) << endl;
    cout << string(typeid(PchlSelector).name()) << endl;

    return 0;
}
