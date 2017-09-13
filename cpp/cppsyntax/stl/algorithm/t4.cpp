/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:通过这种方式将最后一个元素与第一个元素交换
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> v1;

    v1.push_back(2);
    v1.push_back(1);
    v1.push_back(3);

    cout << v1[0] << " " << v1[1] << endl;

    swap(v1[0], v1[v1.size() - 1]);

    cout << v1[0] << " " << v1[1] << endl;



    return 0;
}

