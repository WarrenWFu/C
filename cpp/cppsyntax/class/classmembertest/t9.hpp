#include <cstddef>

template <typename T>
class Foo
{
public:
    Foo(){}
    ~Foo(){}
    static T *pT;
};

void func();

template <typename T>
T* Foo<T>::pT = NULL;
