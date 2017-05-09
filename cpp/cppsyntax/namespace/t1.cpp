/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:匿名命名空间中的变量可以被同一编译单元中的命名空间使用，但是不能
 * 被其它编译单元中的函数使用和static一样,两者最大的却别是后者不能修饰class或
 * struct的声明,基本可以将匿名命名空间看成是static修饰的全局变量
 *
*******************************************************************************/
#include <iostream>

using namespace std;

extern void foo4();

//static class Foo//这句会报错,因为无法为一个声明在数据区分配空间
class Foo
{
public:
	int num3;
};

namespace
{
    string str1;
	int num1 = 0;
	Foo foo1;
	class Foo5
	{
		public:
			int num3;
	};

}

static int num = 1;
static Foo foo2;

namespace UPP
{
	int foo()
	{
		std::cout << "nothing" << std::endl;	
		std::cout << "from anonymous num:" << num << std::endl;	
	
		return 0;
	}

}

int main()
{
	using namespace UPP;	

	foo();
	foo1.num3 = 1;
	foo2.num3 = 2;

	return 0;

}
