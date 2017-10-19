#include "foo.hpp"
#include <string>

using std::string;

class Foo1:public Foo
{
public:
    Foo1();
    ~Foo1();


    void func();

    string str2;

};
