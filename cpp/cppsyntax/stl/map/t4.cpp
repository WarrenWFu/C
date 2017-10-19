#include <iostream>

using namespace std;

int counter = 0;

bool foo()
{
    if (counter < 10)
        return true;

    return false;
}

int main()
{
    for (int i = 0; i< 10; i++)
    {
        cout << i << endl; 
        continue;
    }

    return 0;
}
