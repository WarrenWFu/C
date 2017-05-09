#include <iostream>
using std::cout;
using std::endl;
using std::hex;

class Foo1
{
	public:
		Foo1(){a = 10;}
		Foo1(int num):Foo1(){ pi = &num;}
		Foo1(Foo1 &foo1){ cout << "from copy constructor" << endl; }
		const Foo1 &operator =(Foo1 &foo1){cout << "from copy assignment" << endl;}
		int a;
		int *pi;
		void foo3();
	private:
		void foo2();

};

int main()
{
	int num1 = 10;
	int num2 = 11;
	int num3 = 12;

    Foo1 foo1(num1);
    Foo1 foo2(num2);
    Foo1 foo3(num3);

    foo2 = foo1;

    //foo3 = foo1 + foo2;
    cout << foo1.a << endl;
    cout << foo2.a << endl;
    cout << *foo1.pi << endl;
	cout << *foo2.pi << endl;
	cout << hex << foo1.pi << endl;
	cout << hex << foo2.pi << endl;

	return 0;

}
