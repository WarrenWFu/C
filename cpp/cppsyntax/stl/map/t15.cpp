/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * brief:注意map的clear，是不会执行所指向的对象的析构函数的，要自行释放
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

map<int, std::list<string> > g_map;
map<int, std::list<string> > g_map2;

void loadMap()
{
    std::list<string> l1;
    l1.push_back("A");
    g_map[1] = l1;

    std::list<string> l2;
    l2.push_back("B");
    g_map[2] = l2;

    l2.pop_back();
    l2.push_back("C");
    g_map2[1] = l2;

}


int main()
{
    loadMap();

    cout << g_map[2].front() << endl;
    cout << g_map2[1].front() << endl;

    return 0;
}

