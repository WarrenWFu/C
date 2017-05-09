/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:本程序模仿UPP连接使用oracle数据库的过程
 *
*******************************************************************************/
#include <iostream>
#include <string>

#include <db/cdbc.hpp>
#include <base/threadKey.hpp>

using namespace std;
using namespace aps;
using namespace aps::db;

namespace 
{
    int iLoop;
    char buffer[10+1];
}

void mySelect(db::Connection *val)
{
    memset(buffer, 0x00, sizeof(buffer));
    sprintf(buffer, "%d", iLoop);
    aps::db::SimpleQuery simpleQuery(val);
    string sql = "SELECT BIGTXTIDEX FROM T_USI_BIGTXTDATA WHERE BIGTXTIDEX = "; 
    sql += string(buffer);

    SQLRtn_t emSqlRtn = simpleQuery.query(sql);
    if (emSqlRtn == eSQLRtnNotFound)
    {
        //cout << "未找到" << endl;
    }
    else if (emSqlRtn != eSQLRtnOK)
    {                                                                              
        cout << "执行SQL失败" << endl;
    }                                                                              
    else
    {
        bool bNext = true;
        aps::db::ResultSet &resultSet = simpleQuery.getResultSet();
        for (; bNext; bNext = resultSet.next())
        {
            //cout << "结果是[" << resultSet.getInt(0) << "]" << endl;
        }
    }
}

void myInsert(Connection *val)
{
    memset(buffer, 0x00, sizeof(buffer));
    sprintf(buffer, "%d", iLoop);
    string sql = "INSERT INTO T_USI_BIGTXTDATA(PFWRKDATE, BIGTXTIDEX, \
                  BIGTXTTYPE, BIGTXTLEN, BIGTXTCNT, STATE) \
                  VALUES('33330831', ";
    sql += buffer;
    sql += ", 'testtype', 10, 'testtxt', 'TEST')"; 
    //sql += Datetime::now().format("YMDHIS");

    Statement* pStmt = val->prepareStatement(sql);
    try
    {
        pStmt->executeUpdate(sql);
    }
    catch (Exception& e)
    {
        cout << "错误码:[" << e.code() << "] 错误信息：" << e.what() << endl; 
    }
    catch (...)
    {
        cout << "发生了未知错误" << endl;
    }

    val->commit();
    val->freeStatement(pStmt);
}

void myUpdate(Connection *val)
{
    memset(buffer, 0x00, sizeof(buffer));
    sprintf(buffer, "%d", iLoop);
    string sql = "UPDATE T_USI_BIGTXTDATA SET STATE = 'RETE' WHERE BIGTXTIDEX = ";
    sql += buffer;

    Statement* pStmt = val->prepareStatement(sql);
    try
    {
        pStmt->executeUpdate(sql);
    }
    catch (Exception& e)
    {
        cout << "错误码:[" << e.code() << "] 错误信息：" << e.what() << endl; 
    }
    catch (...)
    {
        cout << "发生了未知错误" << endl;
    }

    val->commit();
    val->freeStatement(pStmt);
}

void myDelete(Connection *val)
{
    memset(buffer, 0x00, sizeof(buffer));
    sprintf(buffer, "%d", iLoop);
    string sql = "DELETE FROM T_USI_BIGTXTDATA WHERE BIGTXTIDEX = ";
    sql += buffer;

    Statement* pStmt = val->prepareStatement(sql);
    try
    {
        pStmt->executeUpdate(sql);
    }
    catch (Exception& e)
    {
        cout << "错误码:[" << e.code() << "] 错误信息：" << e.what() << endl; 
    }
    catch (...)
    {
        cout << "发生了未知错误" << endl;
    }

    val->commit();
    val->freeStatement(pStmt);
}

int main(int argc, char *argv[])
{
    const string url = ";dbDriver=oracle;dbHost=myCentOS6.8;dbPort=1522;dbName=MYDBORACLE;";

    string strDriverDir = "/mnt/winshared/myyb/product/Linux64/lib/";
    DriverManager::setDriverDir(strDriverDir);
    DriverManager::loadDriver("oracle");

    //线程安全方式
    //ThreadKey<db::Connection> threadDbConn;
    //Connection *pConn = threadDbConn.get();
    //pConn = DriverManager::getConnection(url);
    //threadDbConn.set(pConn);

    //非线程安全方式
    Connection *pConn = DriverManager::getConnection(url);
    pConn->connect("spring_oracle", "123123");

    iLoop = argc > 1? atoi(argv[1]): 1;

    //这个函数第一次进入肯定会去读配置，这个程序不能用啊
    //Connection *pConn2 = GlobalData::dbConn();

    for (; iLoop > 0; iLoop--)
    {
        //mySelect(pConn);
        //myInsert(pConn);
        //myUpdate(pConn);
        myDelete(pConn);
    }

    return 0;
}
