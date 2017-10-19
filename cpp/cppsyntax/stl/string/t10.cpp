/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * @brief:
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    //string str1 = "select col1,col2,col3,col4 from t_ust_bigtxtdata";
    //str1 += "where col1 = '";
    //str1 += "val1";
    //str1 += "where col1 = '";
    //str1 += "val1";
    //str1 += "where col1 = '";
    //str1 += "val1";
    //str1 += "where col1 = '";
    //str1 += "val1";
    //str1 += "where col1 = '";
    //str1 += "val1";

    string str1 = "select col1,col2,col3,col4 from t_ust_bigtxtdatawhere col1 = 'val1where col1 = 'val1where col1 = 'val1where col1 = 'val1where col1 = 'val1";

    cout << str1 << endl;

    return 0;
}

