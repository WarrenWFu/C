/*H***************************************************************************
File            : tinyoci.h
Subsystem       : 
Function Name(s):

Description     : 
Author          : Ben
Date            : 2002.05.20
Revision        : 

History
-------
2002.05.20      Ben     Create

Copyright (c) ShenZhen COMEXE Communication Technology Co. Ltd.  
***************************************************************************H*/
#ifndef _TINYOCI_H_20020520
#define _TINYOCI_H_20020520

#include <vector>
#include <string>
#include "oci.h"

class AnyValue;

/*C********************************************************************
  Class      :  TinyNamedPtrList
  Description:      

  Methods    :                  
**********************************************************************C*/
typedef struct TinyNamedPtr
{
    char *pszName;
    void *pPtr;

}TinyNamedPtr;

class TinyNamedPtrList
{
public:
    TinyNamedPtrList() {};
    ~TinyNamedPtrList(){};
    
private:
    std::vector<struct TinyNamedPtr*> m_PtrList;
    
    TinyNamedPtr* _Get( const char *pszName );
    
public:
    bool  Append( const char*pszName, void *pPtr );
    void* Get( const char* pszName );
    void* GetAt( int i );
    bool  Delete( const char *pszName );
    bool  Clean( void );
    long  GetCount( void );
};


/*C********************************************************************
  Class      :  TinyOci
  Description:  

    Value Array Demo:
    Field1 [0] [1] [2] [3] [4] ... 
    Field2 [0] [1] [2] [3] [4] ...
    Field3 [0] [1] [2] [3] [4] ...
    Field4 [0] [1] [2] [3] [4] ...
    Field5 [0] [1] [2] [3] [4] ...

    Each vertical collumn comprise a record(row), Ex:
    Field1[0], Field2[0], Field3[0], Field4[0], Field5[0]
    Field1[1], Field2[1], Field3[1], Field4[1], Field5[1]

  Methods    :                  
**********************************************************************C*/
typedef struct TinyItem
{
    char  szName[128];
#define TINYOCI_MAX_NAME_LEN  128

    sb4   lSize;
    ub2   nType;
    void *pValueArray;
    sb2  *IndicatorArray;

}TinyItem;


class TinyOci
{
public:
    TinyOci();
    ~TinyOci();

private:
    OCIEnv     *m_phOCIEnv;
    OCIServer  *m_phOCIServer;
    OCISession *m_phOCISession;
    OCIError   *m_phErrorHandle;    
    OCIStmt    *m_phStmtHandle;     
    OCISvcCtx  *m_phOCISvcCtx;
    ub2         m_StmtType;
    sword       m_Status;

    long        m_lMaxFetch;
    long        m_lPrefetch;
    int         m_nIter;
    long        m_lRowCountSoFar;
    long        m_lRowFetched;

    TinyNamedPtrList  DescDefineNameList; 
    TinyNamedPtrList  DefineNameList; 
    TinyNamedPtrList  BindNameList;

private:
    void CheckNull( void );
    bool DescribeDefine( void );
    bool Bind( void );
    bool Define( void );
    bool Prepare( const char *pszSql );
    bool CleanDescDefineList( void );
    TinyNamedPtrList* CurrentDefineList( void );
    bool TranslateSizeType( sb4 &lSize, ub2 &nType, ub2 nScale, ub2 nPrecision );
    bool CleanDefineBuffer( void );

public:
    bool  Init( void );
    bool  Connect( const char *pszConnectStr, const char *pszUser, const char *pszPasswd );
    bool  Disconnect( void );
    bool  IsSelect( void );
    bool  Commit( void );
    bool  RollBack( void );
    bool  Execute( const char *pszSql, int nIter=1 );
#define TINYMAX_ITER 500
    
    short Fetch(std::vector<AnyValue>&);
    short Fetch(long &lRows);
#define TINYOCI_FETCH_ERROR -1
#define TINYOCI_FETCH_DONE   0
#define TINYOCI_FETCH_MORE   1
#define TINYOCI_FETCH_NODATA 2  


#define TINYOCI_MAXFETCH     500
    
    bool  IsCommBreak( void );
// Define Database connection broken Code(internal)
#define TINYOCI_CONNECTION_BROKEN            1041 //ORA_01041
#define TINYOCI_SESSION_KILLED                 28 //ORA_00028
#define TINYOCI_IVALID_SESSION                 22 //ORA_00022
#define TINYOCI_EOF_COMM_CHANNEL             3113 //ORA_03113
#define TINYOCI_TABLE_VIEW_NOT_EXIST          942 //ORA_00942 
#define TINYOCI_INDEX_NOT_EXIST              1418 //ORA_01418 

    bool  SetPrefetch( long lPrefetch );
    bool  SetMaxFetch( long lMaxFetch );
    long  GetMaxFetch( void ) { return m_lMaxFetch; }

    sb4  GetError( char *pszMsg );
    
    bool PushBindList( const char *pszName, ub2 DateType, long lSize, void *pValue );
    bool PushDefineList( const char *pszName, ub2 DataType, long lSize, void *pValue );
    bool CleanBindList( void );
    bool CleanDefineList( void );
    bool ResetList( void );

    bool SetDateFormat( short nFormat = 2 );
#define TINYOCI_DATEFORMAT_1   1   // YYYYMMDD
#define TINYOCI_DATEFORMAT_2   2   // YYYYMMDDHH24MISS
#define TINYOCI_DATEFORMAT_3   3   // YYYY-MM-DD HH24:MI:SS
#define TINYOCI_DATEFORMAT_4   4   // DD-MON-YY
#define TINYOCI_DATEFORMAT_5   5   // DD-MON-YYYY
};

typedef long long TInt64;

class AnyValue
{
    public:
        enum Type_t
        {
            eNullVal=0,     ///< 空数据
            eIntVal,        ///< Int
            eInt64Val,      ///< Int64
            eDoubleVal,     ///< Double
            eStringVal,     ///< 字符串/CLOB
            //eDateVal,       ///< 时间
            //eTimeVal,       ///< 时间
            //eDatetimeVal,   ///< 时间
            //eBinaryVal      ///< 二进制
        };

    public:
        AnyValue();
        AnyValue(Type_t t);
        virtual ~AnyValue();

        AnyValue& operator=(const AnyValue& other);
        AnyValue(const AnyValue& other);

        bool bNull;

        // 内部使用
        union
        {
            int *pInt;
            TInt64 *pInt64;
            double *pDouble;
            std::string *pString;
            //Date *pDate;
            //Time *pTime;
            //Datetime *pDatetime;
            //MemBuffer *pBinary;
        }
        Val;

        Type_t Type;

        bool isNull();
        void setNull();
        void setInt(const int& v);
        void setInt64(const TInt64& v);
        void setDouble(const double& v);
        void setString(const std::string& v);
        //void setDate(const Date& v);
        //void setTime(const Time& v);
        //void setDatetime(const Datetime& v);
        //void setBinary(void);

        // 若类型不对则抛异常!
        int& getInt();
        TInt64& getInt64();
        double& getDouble();
        std::string& getString();
        //Date& getDate();
        //Time& getTime();
        //Datetime& getDatetime();
        //MemBuffer& getBinary();

    protected:

        void setType(Type_t type_);
        void freeVal();
        static void copyVal(const AnyValue& from, AnyValue& to);
};

#endif
// End Of File
