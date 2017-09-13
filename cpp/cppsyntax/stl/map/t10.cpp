/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:map中使用vector作为value的情况,使用很方便
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
    map<double, vector<int> > m1;
    pair<map<double, vector<int> >::iterator, bool> ret;

    for (int i = 0; i < 10; i ++)
    {
        vector<int> v1;
        v1.push_back(i);

        //m1[(double)i] = v1;
        ret = m1.insert(pair<double, vector<int> >(i%2, v1));
        if (ret.second == false)
        {
            cout << i%2 << endl; 
        }
    }
    

    for (int i = 0; i< 10; i++)
    {
        //cout << m1[i][0] << endl;
    }


    return 0;
}

