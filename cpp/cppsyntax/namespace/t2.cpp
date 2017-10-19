/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:定义在类中的typedef，使用时必须使用类名,如果是private类型的则不能
 * 被外部使用
 *
*******************************************************************************/
#include <iostream>

namespace UPP
{
	class Foo
	{
		public:
			//typedef UPP::Foo uf;
			typedef int uf;
			static int num;
	};

}
int UPP::Foo::num;

int main()
{
	using UPP::Foo;
	Foo::uf foo; 
	//foo.num = 10;

	//std::cout << foo.num << std::endl;

	return 0;
}
