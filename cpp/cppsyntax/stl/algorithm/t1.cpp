/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用几种stl算法函数
 *
*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int arr1[] = {1,2,3,4,5};
    int arr2[] = {9,5,6,11,1,17};
    vector<int> v(10); //不给长度会段错误
    vector<int>::iterator it;

    sort(arr1, arr1+5);
    sort(arr2, arr2+6);

    it = set_intersection(arr1, arr1+5, arr2, arr2+6, v.begin());

    cout << int(it - v.begin()) << endl;

    return 0;


}

