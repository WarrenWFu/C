/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:map插入时进行由小到大排序，时间复杂度为NlogN,负数同样被排序
 * 定义时使用类似map <int, string, greater<int> > m_MyMap;可以由大到小排序
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    map<double, string> m1;

    m1.insert(pair<double, string>(5.12, "abc"));
    m1.insert(pair<double, string>(3.22, "bc"));
    m1.insert(pair<double, string>(7.12, "adc"));
    m1.insert(pair<double, string>(105.12, "fbc"));
    m1.insert(pair<double, string>(-5.02, "c"));

    for (map<double, string>::iterator iter = m1.begin(); iter != m1.end(); 
            iter ++)
    {
        cout << iter->first << "->" << iter->second << endl;
    }

    return 0;
}

