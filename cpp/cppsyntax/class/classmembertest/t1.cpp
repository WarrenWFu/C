/*******************************************************************************
 *                                                                                 
 * author:Warren Fu                                                                
 * date:                                                                           
 * description:
 *                                                                                 
 ******************************************************************************/
#include <iostream>
#include <typeinfo>
#include <cstring>
#include <unistd.h>
#include <cstdlib>

class TestClass
{
	public:
		TestClass(int numpra1, int numpra2, int numpra3):
			num1(numpra1),num1u(numpra2),num2u(numpra3),
			num1uR(num1u),num2uR(num2u)
   			{
				num1uP = &num1u;
				num2uP = &num2u;
				num1P = &num1;
				num2P = &num1;
				nameCA = new char[10];
				memset(name2CA, '\0', 10);
				memset(name2uCA, '\0', 10);
				name2CA[0] = 'a';
				name2CA[1] = '2';
				name2CA[2] = '3';
				name2uCA[0] = 'c';
				name2uCA[1] = 'c';
			}
		~TestClass() {delete [] nameCA;}
		int getNum1()const {return num1;}
		int *getNum1uP() const {return num1uP;}
		const int *getNum2uP(){return num2uP;}
		int *getNum1P() const
	   	{std::cout<< "from const" << std::endl;return num1P;}
		int *getNum1P()
	   	{std::cout<< "from normal" << std::endl;return num1P;}
		const int *getNum2P(){return num2P;}
		char *getNameCA() const;// {return nameCA;}
		char *getName2CA() {return name2CA;}
		const char *getName2CA() const{return name2CA;}

		int num1u;
		const int num2u;
		int *num1uP;
		const int *num2uP;
		int &num1uR;
		const int &num2uR;
		char name2uCA[10];
	private:
		int num1;
		int *num1P;
		const int *num2P;
		char *nameCA;
		char name2CA[10];
};

char *TestClass::getNameCA() const
{
	return nameCA;
}


//class TestClass1:TestClass
//{
//	public:
//		TestClass1():TestClass(1){}
//};

//class TestClass2:virtual TestClass
//{};

//class TestClass3:TestClass1,TestClass2
//{};

int main(int argc, char* argv[])
{
	if(argc <= 3)
	{
		std::cout << "input the parameters" << std::endl;
		return 0;
	}
	TestClass tc1(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	const TestClass tc2(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

	tc1.getNum1();
	tc2.getNum1();
	tc1.getNum1uP();
	tc2.getNum1uP();
	tc1.getNum2uP();
	int *numP = tc1.getNum1P();
	tc2.getNum1P();
	const int *numP2 = tc1.getNum2P();
	tc1.getNameCA();
	char *name1P = tc2.getNameCA();
	const char *name2P = tc1.getName2CA();
	//tc2.getName2CA();


	return 0;
}
