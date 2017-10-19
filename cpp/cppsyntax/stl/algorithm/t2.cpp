/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查map中的key排序情况，结果是map插入时已经对key进行了排序
 *
*******************************************************************************/

#include<iostream>
#include<map>

using namespace std;

int main()
{
    map<string,string> map1;
    map<string,string>::iterator iter;

    map1["db"] = "1";
    map1["da"] = "2";
    map1["ab"] = "3";
    map1["cb"] = "4";
    map1["ba"] = "5";

    for(iter = map1.begin(); iter != map1.end(); iter ++)
    {
        cout << iter->first << "=>" << iter->second << endl;
    }

    return 0;

}
