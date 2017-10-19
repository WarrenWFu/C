/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * @brief:assign可以很方便的给新建字符串赋值，find子字符串得到的位置为原字符串中位置
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string strA = "AAAA|BBB|123";

    string strB;
    string strC;
    int iPos = strA.find('|');
    strB.assign(strA, 0, iPos);
    //strC.assign(strA, iPos+1, strA.find('|', iPos+1)-1-iPos);
    strC.assign(strA, iPos+1, strA.rfind('|')-1-iPos);

    cout << strA.find('|', iPos+1) << endl;
    cout << strB << endl;
    cout << strC << endl;

    return 0;
}

