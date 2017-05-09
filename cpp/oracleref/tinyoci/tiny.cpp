/*H***************************************************************************
File            : tiny.cpp
Subsystem       :
Function Name(s):

Description     : Testing TinyOci
Author          : Ben
Date            : 2002.05.22
Revision        :

History
-------
2002.05.22      Ben     Create

Copyright (c) ShenZhen COMEXE Communication Technology Co. Ltd.
***************************************************************************H*/
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include "tinyoci.hpp"

using std::string;
using std::vector;

namespace 
{
    string username = "spring_oracle";
    string password = "123123";
    string dbname   = "MYDBORACLE";

    string selectSQL ="SELECT BIGTXTIDEX FROM T_USI_BIGTXTDATA WHERE BIGTXTIDEX = :1";
    string insertSQL ="INSERT INTO T_USI_BIGTXTDATA\
                     (PFWRKDATE, BIGTXTIDEX, BIGTXTTYPE, BIGTXTLEN, BIGTXTCNT, STATE)\
                     VALUES ('20160830', :1, 'testtype', 10, 'testtxt', 'TEST')";
    string updateSQL = "UPDATE T_USI_BIGTXTDATA SET STATE = 'RETE' WHERE BIGTXTIDEX = :1";
    string deleteSQL = "DELETE FROM T_USI_BIGTXTDATA WHERE BIGTXTIDEX = :1";
    int iLoop;

    //用于操作数据的封装了OCI的类
    TinyOci TinyDb;
    char szError[512];
}

void myConnect()
{
    // 初始化部分
    if( !TinyDb.Init() )
    {
        printf("Init 失败\n");
    }
    if( !TinyDb.Connect( "MYDBORACLE", "spring_oracle", "123123" ) )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
    }

    //以下是设置日期时间的格式，暂时不用
    //if( !TinyDb.SetDateFormat() )
    //{
    //    TinyDb.GetError( szError );
    //    printf( "\n%s", szError );
    //    return -1;
    //}
}

void mySelect()
{
    //后面参数表示执行次数，缺省为1
    if( !TinyDb.Execute( selectSQL.c_str(), 1 ) )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
        return;
    }

    vector<AnyValue> vRessult;
    TinyDb.Fetch(vRessult);

    //printf( "结果是[%lld]\n", vRessult.at(0).getInt64());
    //printf( "结果是[%s]\n", vRessult.at(0).getString().c_str());

}

void myInsert()
{
    //后面参数表示执行次数，缺省为1
    if( !TinyDb.Execute( insertSQL.c_str(), 1 ) )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
    }
    if( !TinyDb.Commit() )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
    }

    // 执行INSERT后回显一次
    //
    // 下一次执行Execute前应该清除前一次的所有绑定
    //
    //if( !TinyDb.ResetList() )
    //    return false;
}
void myUpdate()
{
    //后面参数表示执行次数，缺省为1
    if( !TinyDb.Execute( updateSQL.c_str(), 1 ) )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
    }
    if( !TinyDb.Commit() )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
    }
}
void myDelete()
{
    //后面参数表示执行次数，缺省为1
    if( !TinyDb.Execute( deleteSQL.c_str(), 1 ) )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
    }
    if( !TinyDb.Commit() )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
    }
}

int main( int argc, char *argv[] )
{
    iLoop = argc > 1? atoi(argv[1]): 1;
    myConnect();

    if( !TinyDb.PushBindList( ":1", SQLT_INT, sizeof(iLoop), &iLoop ) )
        return -1;

#if 0
    //可以执行后在define并获取
    int testInt = 0;
    //设置输出变量
    if( !TinyDb.PushDefineList( "BIGTXTIDEX", SQLT_INT, sizeof(testInt), &testInt ) )
        return -1;
#endif

    for(; iLoop > 0; iLoop--)
    {
        mySelect();
        //myInsert();
        //myUpdate();
        //myDelete();
    }

    return 0;

#if 0
    long lTotal;
    short nRc;
    TinyOci TinyDb;
    char szError[512];
    CMXList< CMXList<CMXString> > RowsList;
    CMXList<CMXString> *pFieldsList;
    CMXString *pField;
    LIST_CURSOR cur1,cur2;

    // 测试用的SQL
    //const char *szSql = "SELECT * FROM netinfo";
    //const char *szSql = "SELECT * FROM trouble";
    //const char *szSql = "SELECT * FROM tinyoci";
    //const char *szSql = "SELECT * FROM tinyoci WHERE num_1=:num_1";
    const char *szSql = "INSERT INTO tinyoci( num_1, varchar2_4 ) VALUES ( :num_1, :varchar2_4 )";
    long num_1[10];          // 可以同时执行10次，取不同的值。
    char varchar2_4[10][80];
    long out_num_1[10];          // 可以同时执行10次，取不同的值。
    char out_varchar2_4[10][80];

    // 初始化部分
    if( !TinyDb.Init() )
        return -1;
    if( !TinyDb.Connect( "mydb", "obs", "123456" ) )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
        return -1;
    }
    if( !TinyDb.SetDateFormat() )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
        return -1;
    }

    // 如果有需要的话，应该在Execute之前调用SetMaxFetch。
    // 如果在Execute之后调用SetMaxFetch的话，MaxFetch的值
    // 必须小于“输出数组”的下标值，否则超出“输出数组”的
    // 范围(数组越界)，将导致CORE DUMP !
    TinyDb.SetMaxFetch( 3 );

    // 如果有需要的话，可以设置输入变量:
    // bool PushBindList( const char *pszName, ub2 DateType, long lSize, void *pValue );
    // 其中pszName为输入变量在SQL中名称(包括冒号':')。
    if( !TinyDb.PushBindList( ":num_1", SQLT_INT, sizeof(num_1[0]), &num_1[0] ) )
        return -1;
    if( !TinyDb.PushBindList( ":varchar2_4", SQLT_STR, sizeof(varchar2_4[0]), varchar2_4[0] ) )
        return -1;

    // 如果设置了输入变量，则应该为输入变量赋值：
    memset( &num_1[0], 0, sizeof( num_1 ) );
    num_1[0] = 17;
    num_1[1] = 18;
    num_1[2] = 19;
    num_1[3] = 20;
    strcpy( varchar2_4[0], "Array Bind 17" );
    strcpy( varchar2_4[1], "Array Bind   18" );
    strcpy( varchar2_4[2], "Array Bind     19" );
    strcpy( varchar2_4[3], "Array Bind 20" );

    // Execute方法有一个缺省参数nIter,表示对非SELECT语句重复执行的次数:
    // bool  Execute( const char *pszSql, int nIter=1 );
    //
    if( !TinyDb.Execute( szSql, 4 ) )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
        return -1;
    }
    if( !TinyDb.Commit() )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
        return -1;
    }

    // 执行INSERT后回显一次
    //
    // 下一次执行Execute前应该清除前一次的所有绑定
    //
    if( !TinyDb.ResetList() )
        return false;

    // 如果有需要的话，可以设置输出变量:
    // bool PushDefineList( const char *pszName, ub2 DataType, long lSize, void *pValue );
    // 其中pszName为输入变量在SQL中名称,该名称不影响SQL的执行，只是作为一个索引，就是说，
    // 它可以是你所喜欢任何字符串(一般为字段名)。
    //
    // DataType只能取以下的值：
    //           SQLT_FLT
    //           SQLT_INT
    //           SQLT_STR
    // 这里建立的DefineList的顺序必须与SELECT语句的结果集的字段顺序相一致 !!
    //
    if( !TinyDb.PushDefineList( "out_num_1", SQLT_INT, sizeof(out_num_1[0]), &out_num_1[0] ) )
        return -1;
    if( !TinyDb.PushDefineList( "out_varchar2_4", SQLT_STR, sizeof(out_varchar2_4[0]), &out_varchar2_4[0] ) )
        return -1;
    memset( &out_num_1[0], 0, sizeof( out_num_1 ) );
    memset( &out_varchar2_4[0], 0, sizeof( out_varchar2_4 ) );
    // 请在Execute->Fetch之后，用QickWatch查看以上两个“输出变量”。

    // 执行
    if( !TinyDb.Execute( "SELECT num_1, varchar2_4 FROM tinyoci" ) )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
        return -1;
    }

    lTotal = 0;
    nRc    = TinyDb.Fetch( RowsList );
    printf("\n\r");
    while( ( TINYOCI_FETCH_MORE == nRc ) ||
           ( TINYOCI_FETCH_DONE == nRc ) )
    {
        pFieldsList = RowsList.GetFirst( &cur1 );
        while( NULL != pFieldsList )
        {
            pField = pFieldsList->GetFirst( &cur2 );
            while( NULL != pField )
            {
                printf( "%s\t", pField->C_str() );
                pField = pFieldsList->GetNext( &cur2 );
            }
            printf("\n\r");

            pFieldsList = RowsList.GetNext( &cur1 );
        }

        lTotal += RowsList.GetCount();
        RowsList.DestroyList();

        if( TINYOCI_FETCH_DONE == nRc )
            break;
        nRc = TinyDb.Fetch( RowsList );
    }
    printf("\nTotal %ld records", lTotal );

    if( !TinyDb.Disconnect() )
    {
        TinyDb.GetError( szError );
        printf( "\n%s", szError );
        return -1;
    }

    return 0;
#endif
}

