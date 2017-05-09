/*******************************************************************************
 *
 * author:Warren Fu
 * date:20140407
 * description:new使用的时候也可以不带括号
 *
*******************************************************************************/
#include <iostream>
struct foo
{
	foo(){}
};

class foo1
{
public:
	foo1(){ std::cout << "from foo1()" << std::endl;}	

};

int main()
{
	foo *myfoo = new foo;
	foo1 *myfoo1 = new foo1;

	return 0;

}
