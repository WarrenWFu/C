/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:常量类指针，可以调用非常量数据成员，但是不能修改,但是如果成员是
 * 指针，却可以修改指针指向的对象的值，此时如果将类数据成员的地址赋值给这个指针
 * 就可以达到修改类数据成员值的效果，风险巨大
 *
*******************************************************************************/
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Foo
{
public:
	int num;
	string str;
	int *pnum;
	Foo():num(1),str("abc"),pnum(&num){}
protected:
private:

};
int main()
{
	Foo *foo = new Foo();
	cout << foo->num << endl;
	cout << foo->str << endl;

	delete foo;

	const Foo *foo1 = new Foo();
	cout << foo1->num << endl;
	cout << foo1->str << endl;
	cout << foo1->pnum << endl;

	//foo1->num = 10;//此句报错
	int num2 = 10;
	//foo1->pnum = &num2;//此句报错
	*(foo1->pnum) = 12;//修改了Foo中的num的值
	cout << foo1->num << endl;
	delete foo1;
	return 0;
}
