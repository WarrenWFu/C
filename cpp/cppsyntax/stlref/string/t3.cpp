/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:对于string的size来说取到的是实际编码格式中对应如 我的abc你', ' 
 * 这几个字符的字节的长度，那么如果本文件是gb2312编码或utf-8编码，打出来的长度
 * 可能是不同的，必须清楚这一点
 *
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    return 0;
}
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string str1("我的abc你', '");

	cout << "[" << str1.size() <<  "]" << str1 <<endl;

	str1.erase(str1.length() - 3, 3);

	cout << "[" << str1.size() << "]" << str1 << endl;

	return 0;
}	
