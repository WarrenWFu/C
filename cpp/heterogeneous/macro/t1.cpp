/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:由GCC预先定义的5个宏，最后一个默认是10进制常量1
 *
*******************************************************************************/
#include <iostream>

int main()
{
	std::cout << __LINE__ << std::endl;
	std::cout << __FILE__<< std::endl;
	std::cout << __DATE__ << std::endl;
	std::cout << __TIME__ << std::endl;
	std::cout << __STDC__ << std::endl;


	return 0;

}
