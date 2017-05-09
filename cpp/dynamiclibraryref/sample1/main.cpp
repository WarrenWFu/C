/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:测试linux下使用C++编写动态库的主程序
 *
*******************************************************************************/
#include "main.hpp"

using namespace std;

int main()
{
    Foo1 *pFoo1 = new Foo1();
    Foo2 *pFoo2 = new Foo2();

    while(true)
    {
        string strCommand;
        getline(cin, strCommand);

        if (strCommand == "q")
            break;
    
        pFoo1->func1();
        pFoo2->func2();
    }

    delete pFoo1;
    delete pFoo2;

    return 0;
}

