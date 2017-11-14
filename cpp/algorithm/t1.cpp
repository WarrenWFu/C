/**
 * @file        
 * @brief       输出一段斐波那契数列
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void foo(int nl, int nr, int num)
{
    if (num > 2)
    {
        int tmp = nl + nr;
        cout << tmp << " ";
        foo(nr, tmp, --num);
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "usage: ./a.out 数列长度" << endl;
        return 0;
    }

    int num = atoi(argv[1]);

    if (num <= 1)
        cout << "0 ";
    else
    {
        cout << "0 1 ";
        foo(0, 1, num);
    }

    cout << endl;

    return 0;
}

