/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:
 *
*******************************************************************************/
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> vStr;
    vStr.push_back("a");
    vStr.push_back("a");
    vStr.push_back("a");
    vStr.push_back("a");

    printf("[%s]\n", vStr.at(4).c_str());

    return 0;
}

