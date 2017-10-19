/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:vector为空时，begin()和end()是相等的
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1;

    for (vector<int>::iterator iter = v1.begin();
            iter != v1.end(); iter++)
    {
        cout << *iter << endl; 
    }

    return 0;
}

