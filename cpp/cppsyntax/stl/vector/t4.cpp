/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:当vector中放指针的时，push_back的时候相当于将指针进行拷贝，原指针
 * 如果delete，vector中的对象同样也被delete，所以如果必要可以将原来的指针指向NULL
 *
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Foo
{
public:
    Foo():str1("123"){}
    string str1;

};

int main()
{
    vector<Foo *> v1;
    Foo *pfoo1 = new Foo();

    v1.push_back(pfoo1);

    cout << v1[0]->str1 << endl;
    cout << hex << v1[0] << endl;
    cout << hex << pfoo1 << endl;

    delete pfoo1;

    cout << v1[0]->str1 << endl;

    return 0;
}

