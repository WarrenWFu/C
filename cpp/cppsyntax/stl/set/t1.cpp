/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:简单的使用set用于去除相同值
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
	string str1("a");
	string str2("b");
	string str3("c");
	string str4("d");
	string str5("e");

	string strArray[5] = {str1, str2, str3, str4, str5};

	set<string> set1(strArray, strArray+4); 
	pair<set<string>::iterator, bool> ret;

	ret = set1.insert("f");
	
	if (ret.second)
	{
		cout << "succeed" << endl;	
	}
	else 
	{
		cout << "failed" << endl;	
	}

	return 0;


}
