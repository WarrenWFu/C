/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:set的erase之后，iter并不会自动++，还是需要明确进行++，
 * 和vector不同
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
    set<string> setNames;

    setNames.insert("a");
    setNames.insert("b");
    setNames.insert("c");
    setNames.insert("d");
    setNames.insert("e");

    for (set<string>::iterator iter = setNames.begin();
            iter != setNames.end();iter ++)
    {
        if (*iter == "b" || *iter == "d" || *iter == "e")
        //if (*iter == "b" || *iter == "d" )
            setNames.erase(iter);
    }

    for (set<string>::iterator iter = setNames.begin();
            iter != setNames.end();
            iter ++)
    {
        cout << *iter << endl; 
    }


    return 0;
}

