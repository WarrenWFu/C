/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:检查UPPS平台的数据库类的性能
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstring>
#include <db/cdbc.hpp>

using namespace std;
using namespace aps::db;

int main()
{
    try
    {
        //获取数据库连接
        Connection *pConn = 
            DriverManager::getConnection(";dbDriver=oracle;dbHost=172.168.6.66;dbPort=1521;dbName=strt;");
    }
    catch (aps::Exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

