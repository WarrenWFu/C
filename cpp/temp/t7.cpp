/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

class Foo
{
public:
    map<int, string> m_map1;
};

int main()
{
    double dNum = 12.34;
    printf("[%09.2lf]\n", dNum);
//    system("scp /home/strt/upps.118106.selector.cpp upp2016@172.168.41.122:/home/upp2016/");
    //system("/mnt/winshared/it/cpp/tests/temp/tt.sh /home/strt/upps.118106.selector.cpp upp2016@172.168.41.122:/home/upp2016/");
    
    long lNum = 10;
    printf("[%-11ld]\n", lNum);
    int iNum = 110101001;
    printf("[%d]\n", iNum);
    //printf("[%-04s]\n", "abc");//不能补0


    char szBuf[15] = {0};
    memcpy(szBuf+5, "12 3 45", strlen("12 3 45"));
    memcpy(szBuf, "    7", 5);
    printf("[%s]\n", szBuf);
    printf("[%d]\n", strlen(szBuf+3));

    Foo foo;
    foo.m_map1[0] = "123";


    return 0;

}

