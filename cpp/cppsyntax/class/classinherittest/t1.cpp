/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:调用默认赋值重载函数，可以实现私有成员的赋值
 *
*******************************************************************************/
#include <iostream>
using std::cout;
using std::endl;


class Foo1
{
	public:
		int numpub1;
		void setNumpri1(int num){numpri1 = num;}
		int getNumpri1(){return numpri1;}
		//Foo1 &operator=(const Foo1& foo1par)
		//{
		//	this->numpub1 = foo1par.numpub1;
		//	this->numpri1 = foo1par.numpri1;
		//	cout << "from Foo1 operator=" << endl;
		//}
	private:
		//Foo1 &operator=(const Foo1& foo1pam);
		int numpri1;
};

class Foo2:public Foo1
{
	public:
		int numpub2;
		Foo2 &operator=(const Foo2& foo2par)
		{
			if ( &foo2par == this)
			{
				return *this;	
			}
			Foo1::operator=(foo2par);
			this->numpub1 = foo2par.numpub1;
			this->numpub2 = foo2par.numpub2;
			cout << "from Foo2 operator=" << endl;
		}
	private:
		int numpri2;
};

int main()
{
	Foo2 foo21;	
	Foo2 foo22;	

	foo21.numpub1 = 10;
	foo21.numpub2 = 11;
	foo21.setNumpri1(20);
	foo22.numpub1 = 12;
	foo22.numpub2 = 13;
	foo22.setNumpri1(21);

	foo22 = foo21;

	cout << foo22.numpub1 << endl;
	cout << foo22.numpub2 << endl;
	cout << foo22.getNumpri1() << endl;


	return 0;

}
