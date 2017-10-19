#include <iostream>

using namespace std;

class Foo1
{
public:
    Foo1(){ cout << "from Foo1 constructor" << endl;}
    ~Foo1(){ cout << "from Foo1 destructor" << endl;}
};

class Foo2
{
public:
    Foo2(){ cout << "from Foo2 constructor" << endl;}
    ~Foo2(){ cout << "from Foo2 destructor" << endl;}

    Foo1 foo1;
};

int main()
{
    Foo2 foo2;

    return 0;
}

