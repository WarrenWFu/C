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
#include <boost/type.hpp>

using namespace std;
using namespace boost;

int main()
{
    struct type<int> t;

    cout << sizeof t << endl;

    return 0;
}

