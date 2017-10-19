/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:检查map的iterator是不能相减的！！！
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
    map<string, int*> m1;
    vector<int*> v1;
    int i1 = 1;
    int i2 = 2;
    int i3 = 3;

   // m1["1"] = &i1;
   // m1["2"] = &i2;
   // m1["3"] = &i3;

    v1.push_back(&i1);
    v1.push_back(&i2);
    v1.push_back(&i3);

//    for (map<string, int*>::iterator iter = m1.begin(); iter != m1.end();
//            iter ++)
    for (vector<int*>::iterator iter = v1.begin(); iter != v1.end();
            iter ++)
    {
        cout << iter - m1.begin() << endl;
    }



    return 0;
}

