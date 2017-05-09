/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:抽象类可以被抽象类继承
 *
*******************************************************************************/
#include <iostream>
using std::cout;
using std::endl;

class Foo1
{
public:
	virtual void fun1() = 0;
	virtual ~Foo1(){ cout << "from ~Foo1()" << endl; }

};

class Foo2: public Foo1
{
public:
	virtual void fun1() = 0;//这一句有没有都不影响
	virtual ~Foo2(){cout << "from ~Foo2()" << endl;};
};

class Foo3: public Foo2
{
public:
	void fun1() { cout << "from Foo3" << endl; }

};

int main()
{
	Foo3 foo3;
	foo3.fun1();

	return 0;
}
