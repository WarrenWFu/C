/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * @brief:const修饰函数返回值为const型引用的情况，不能直接修改
 *
*******************************************************************************/
#include <iostream>
using std::cout;
using std::endl;

const int &foo(int &val1)
{
	return val1;
}

int *foo1(int *val1)
{
	return val1;
}

class Foo
{
public:
	int *pnum1;
	int **ppnum;
	Foo(int *val):pnum1(val),ppnum(&pnum1){}

};


int main()
{
	int num1 = 10;
	int num2 = foo(num1);
//如果返回值是一个const型，那么就不能直接进行修改
//	foo(num2)++;//此句报错
	const Foo *foo5 = new Foo(foo1(&num2));
	**(foo5->ppnum) = 100;

	cout << ++num2 << endl;
	cout << num1 << endl;

    delete foo5;

	return 0;
}
