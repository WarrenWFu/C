/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include<iostream>
using namespace std;

#define DEFINE_FOR_DYN_CALL(baseclass, subclass, uppersubclass) \
    extern "C" baseclass *create##uppersubclass() \
{ return new subclass(); } \
extern "C" void destroy##uppersubclass(baseclass *ptr) \
{ delete ptr; }

class Foo
{

};

class Bar: public Foo
{

};

DEFINE_FOR_DYN_CALL(Foo, Bar, BAR)

//int main(int argc, char *argv[])
//{
//    Foo *foo = createBAR();
//
//    if (!foo)
//        cout << "NULL" << endl;
//    else
//        cout << "Not NULL" << endl;
//
//    return 0;
//}
