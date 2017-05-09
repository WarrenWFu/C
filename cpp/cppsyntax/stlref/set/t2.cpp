/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:查看set的size函数，在clear之后返回0
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
#include <set>
#include <string>

using namespace std;

int main()
{
	set<string> set1;

	set1.insert("a");
	set1.insert("b");
	set1.insert("c");

	cout << set1.size() << endl;

	set1.clear();

	cout << set1.size() << endl;

	set1.insert("a");
	set1.insert("b");
	set1.insert("a");
	set1.insert("d");
	cout << set1.size() << endl;

	return 0;
}
