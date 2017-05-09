/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:通过erase删除第二个元素，有时会使iter回到第一个元素，应该注意
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

void foo(map<string, string> &val1, string val2)
{
    val1.erase(val2);
}


int main()
{
    map<std::string, std::string> map1;

    map1["b"] = "2";
    map1["c"] = "3";
    map1["a"] = "1";
    map1["d"] = "4";

    for (map<string,string>::iterator iter = map1.begin(); iter != map1.end();
            iter ++)
    {
        if (iter->first == "b")
            //foo(map1, iter->first);
            map1.erase("b");
        else
            cout << iter->second << endl;
    }


    return 0;
}

