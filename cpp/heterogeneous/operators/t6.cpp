/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查try catch对性能的影响
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <exception>

using namespace std;

void func(int val)
{
    if (val > 10000000)
        throw exception();
}

int main()
{
    //try
    {
        for (int i = 0; i < 10000000-1; i++) 
        {
            func(i); 
        }
    }
   // catch(exception err)
    {
   //     cout << err.what() << endl;  
    }

    return 0;
}

