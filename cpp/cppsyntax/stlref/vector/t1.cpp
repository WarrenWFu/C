/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查vector的排序方式,插入的时候没有排序,如果想用sort排序要重载<
 * 操作符
 *
*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Foo
{
public:
    Foo(int val):num1(val),str1("")
    {}
    int getNum1(){ return num1; }
private:
    int num1;
    string str1;
};

int main()
{
    vector<Foo> v1;

    v1.push_back(Foo(2));
    v1.push_back(Foo(3));
    v1.push_back(Foo(1));
    v1.push_back(Foo(2));

    //sort(v1);

    for (vector<Foo>::iterator iter = v1.begin(); iter < v1.end(); iter++)
    {
        cout << iter->getNum1() << endl;
    }

    return 0;
}