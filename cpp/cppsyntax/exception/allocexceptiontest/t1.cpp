/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:测试new的时候内存不够的情况，可以通过如下方式捕捉
 *
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

class MyTest
{
	public:
		static int foo();
	protected:
	private:
};

int MyTest::foo()
{
	int abc = 10;
	return abc;
}


int main(int argc, char* argv[])
{
/*
	string testString = string(argv[1]);

	cout << testString.size() << endl;
	cout << testString.length() << endl;
	cout << testString.length() << endl;

	const char *testCA = testString.c_str();

	printf("[%u][%u][%u]\n", *testCA, *(testCA+1), *(testCA+2));

*/
//	cout << MyTest::foo() << endl;
	int* testP = NULL;

	try{
		testP = new int[100000000000];
	}
	catch(std::bad_alloc &e)
	{
		cout << e.what() << endl;	
	}

	delete [] testP;

	return 0;

}

