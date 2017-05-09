#include <string>

using std::string;

class Foo
{
public:
    Foo();
    virtual ~Foo();
    
    virtual void func() = 0;

    string str1;
};
