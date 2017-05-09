/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查使用引用作为返回值的情况，用起来很方便
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

class Foo
{
public:
    Foo(int val):v(){ v.push_back(val); }
    vector<int> &getV() { return v;};
private:
    vector<int> v;

};

using namespace std;

int main(int argc, char *argv[])
{
    Foo foo(atoi(argv[1]));

    cout << foo.getV().at(0) << endl;




    return 0;
}

