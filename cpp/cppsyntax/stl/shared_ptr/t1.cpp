/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main()
{
    //int iA = 10;
    std::auto_ptr<char> pAuto(new char[10]);

    cout << pAuto.get() << endl;





    return 0;
}

