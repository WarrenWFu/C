/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:两个stl之间可以直接赋值，如果是不同类型的stl用copy，但是可能会
 * 出错,使用时要注意
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{

    set<string> set1;
    set<string> set2;

    set1.insert("a");
    set1.insert("b");
    set1.insert("c");
    set1.insert("d");
    set1.insert("e");
    set1.insert("f");

    set2 = set1;

    for (set<string>::iterator iter = set2.begin();
            iter != set2.end(); iter ++)
    {
        cout << *iter << endl;
    }

    return 0;
}

