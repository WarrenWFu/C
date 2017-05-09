/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:注意string的三种初始化为空的格式，是相同的，空string执行find
 * 也是可以的
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str1;
    string str2 = "";
    //string str3("");
    string str3();//这句报错
    string str4("");

    void func();

//    if (str1 == str2 && str1 == str3 && str1 == str4)
//        cout << "equal" << endl;
//    else
//        cout << "unequal" << endl;

    //str3 += "123";

    if (string::npos != str1.find("abc"))
        cout << "found" << endl;
    else
        cout << "not found" << endl;

    func();

    return 0;
}

