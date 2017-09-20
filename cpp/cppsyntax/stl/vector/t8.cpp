/**
 * @file        
 * @brief       快速的将两个vector合并
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    std::vector<int> v2;
    v2.push_back(3);
    v2.push_back(4);

    cout << v1.size() << endl;

    v1.insert(v1.end(), v2.begin(), v2.end());

    cout << v1.size() << endl;

    int i = 2;
    int j = 1;
    int* pI = NULL;
    int* pJ = &j;

    pI = pI ? pI: pJ;

    cout << *pI << endl;


    return 0;
}

