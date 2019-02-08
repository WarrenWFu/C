/**
 * @file        
 * @brief       
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
 */

#include <iostream>
#include <string>

using namespace std;

class Foo {
    int i;
};

void bar(int *pI) {
    *pI = 10;
}

int main(int argc, char *argv[])
{
    int i = 1;

    cout << i << endl;

    bar(&i);
    cout << i << endl;

    return 0;
}
