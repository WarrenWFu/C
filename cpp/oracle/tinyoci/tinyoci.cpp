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
                        Many idea is ported from Jason's DBi.

Copyright (c) ShenZhen COMEXE Communication Technology Co. Ltd.  
***************************************************************************H*/
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include "tinyoci.hpp"

using std::vector;
using std::string;

/*M***************************************************************************
Method Name  : TinyNamedPtrList::*
Return       :                
Process      :
Note         : Append: TinyNamedPtrList不维护pPtr !
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyNamedPtrList::Append( const char*pszName, void *pPtr )
{
    TinyNamedPtr *pTinyNamedPtr;

    pTinyNamedPtr = _Get( pszName );
    if( NULL == pTinyNamedPtr )
    {
        pTinyNamedPtr          = new TinyNamedPtr;
        pTinyNamedPtr->pszName = new char[strlen(pszName)+1];
        strcpy( pTinyNamedPtr->pszName, pszName );
        pTinyNamedPtr->pPtr    = pPtr;

        m_PtrList.push_back( pTinyNamedPtr );
    }
    else
    {
        // Memory leak ! If ...
        pTinyNamedPtr->pPtr = pPtr;
    }

    return true;
}

TinyNamedPtr* TinyNamedPtrList::_Get( const char *pszName )
{
    TinyNamedPtr *pTinyNamedPtr;
    int i;

    for( i=0; i<(int)m_PtrList.size(); i++ )
    {
        pTinyNamedPtr = (TinyNamedPtr *)m_PtrList.at(i);
        if( strcmp( pszName, pTinyNamedPtr->pszName ) == 0 )
        {
            return pTinyNamedPtr;
        }
    }    
    
    return (TinyNamedPtr *)NULL;
}

void* TinyNamedPtrList::Get( const char* pszName )
{
    TinyNamedPtr *pTinyNamedPtr;
    pTinyNamedPtr = _Get( pszName );
    if( NULL == pTinyNamedPtr )
    {
        return NULL;
    }

    return pTinyNamedPtr->pPtr;
}

bool TinyNamedPtrList::Delete( const char *pszName )
{
    TinyNamedPtr *pTinyNamedPtr;

    for(vector<TinyNamedPtr*>::iterator iter = m_PtrList.begin() ; iter<m_PtrList.end();  )
    {
        pTinyNamedPtr = *iter;
        if( strcmp( pszName, pTinyNamedPtr->pszName ) )
        {
            delete [] pTinyNamedPtr->pszName;
            delete pTinyNamedPtr;

            iter = m_PtrList.erase(iter);
            return true;
        }
        else
        {
            iter++;
        }
    }    
    
    return false;
}

bool TinyNamedPtrList::Clean( void )
{
    TinyNamedPtr *pTinyNamedPtr;
    int i;

    for( i=0; i<(int)m_PtrList.size(); i++ )
    {
        pTinyNamedPtr = (TinyNamedPtr *)m_PtrList.at(i);
        
        delete [] pTinyNamedPtr->pszName;
        pTinyNamedPtr->pszName = NULL;
        delete pTinyNamedPtr;        
    }    
    
    m_PtrList.clear();
    return true;
}

long TinyNamedPtrList::GetCount( void )
{
    return m_PtrList.size();
}

void* TinyNamedPtrList::GetAt( int i )
{
    TinyNamedPtr *pTinyNamedPtr;
    pTinyNamedPtr = (TinyNamedPtr *)m_PtrList.at(i);

    return pTinyNamedPtr->pPtr;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/*M***************************************************************************
Method Name  : TinyOci::TinyOci
               TinyOci::~TinyOci
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
TinyOci::TinyOci()
{
    m_phOCIEnv      = NULL;
    m_phOCIServer   = NULL;
    m_phOCISession  = NULL;
    m_phErrorHandle = NULL;    
    m_phStmtHandle  = NULL;          
    m_phOCISvcCtx   = NULL;
    m_StmtType      = 0;    // Unknow !
    m_Status        = OCI_SUCCESS;    

    m_nIter         = 1;
    m_lMaxFetch     = 1;
    m_lPrefetch     = 50;
    m_lRowCountSoFar= 0;
    m_lRowFetched   = 0; 
}

/*M***************************************************************************
Method Name  : TinyOci::Init
               
Return       :                
Process      : Allocate all needed OCI handles
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::Init( void )
{    
    if( OCI_SUCCESS != (m_Status = OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0,
                                     0,//(dvoid * (*)(dvoid *, size_t)) 0,
                                     0,//(dvoid * (*)(dvoid *, dvoid *, size_t))0,
                                     0 //(void (*)(dvoid *, dvoid *)) 0 
                                    )) )
    {
        return false;
    }    
    if( OCI_SUCCESS != (m_Status = OCIEnvInit( (OCIEnv **) &m_phOCIEnv, OCI_DEFAULT, (size_t) 0, (dvoid **) 0 )) )
    {
        return false;
    }
        
    if( OCI_SUCCESS != (m_Status = OCIHandleAlloc( (dvoid *) m_phOCIEnv, 
                                       (dvoid **) &m_phErrorHandle, 
                                       OCI_HTYPE_ERROR, (size_t) 0, 
                                       (dvoid **) 0)) )
    {
        return false;
    }

    if( OCI_SUCCESS != (m_Status = OCIHandleAlloc( (dvoid *) m_phOCIEnv, 
                                       (dvoid **) &m_phOCIServer, 
                                       OCI_HTYPE_SERVER, 
                                       (size_t) 0, 
                                       (dvoid **) 0)) )
    {
        return false;
    }
    if( OCI_SUCCESS != (m_Status = OCIHandleAlloc( (dvoid *) m_phOCIEnv, 
                                       (dvoid **) &m_phOCISession, 
                                       OCI_HTYPE_SESSION, 
                                       (size_t) 0, (dvoid **) 0)) )
    {
        return false;
    }

    if( OCI_SUCCESS != (m_Status = OCIHandleAlloc( (dvoid *) m_phOCIEnv, 
                                       (dvoid **) &m_phStmtHandle,
                                       OCI_HTYPE_STMT, 
                                       (size_t) 0, 
                                       (dvoid **) 0)) )
    {
        return false;
    }

    if( OCI_SUCCESS != (m_Status = OCIHandleAlloc( (dvoid *) m_phOCIEnv, 
                                       (dvoid **) &m_phOCISvcCtx, 
                                       (ub4) OCI_HTYPE_SVCCTX, 
                                       (size_t) 0, 
                                       (dvoid **) 0)) )
    {
        return false;
    }

    return true;
}

TinyOci::~TinyOci()
{
    // Clean all Binding and Defining List
    ResetList();
    
    if(NULL != m_phOCIEnv)
    {
        OCIHandleFree( (dvoid *) m_phOCIEnv, OCI_HTYPE_ENV );
    }
}

/*M***************************************************************************
Method Name  : TinyOci::GetError
            
Return       :  ORACLE Error Code is returned               
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
sb4 TinyOci::GetError( char *pszMsg )
{
    char TempBuffer[512];
    long errcode=0;

    printf("[%d]\n", m_Status);

    switch ( m_Status )
    {
    case OCI_SUCCESS:
        if( NULL != pszMsg ) 
            strcpy( pszMsg, "NO ERROR MSG" );
        break;

    case OCI_SUCCESS_WITH_INFO:
        if( NULL != pszMsg )
            strcpy( pszMsg, (char*)"Error - OCI_SUCCESS_WITH_INFO" );
        break;

    case OCI_NEED_DATA:
        if( NULL != pszMsg )
            strcpy( pszMsg, (char*)"Error - OCI_NEED_DATA" );
        break;

    case OCI_NO_DATA:
        if( NULL != pszMsg )
            strcpy( pszMsg, (char*)"Error - OCI_NODATA" );
        break;

    case OCI_ERROR:
        OCIErrorGet((dvoid *)m_phErrorHandle, (ub4) 1, (OraText *) NULL, (sb4*)&errcode,
                    (ub1*)TempBuffer, (ub4) sizeof(TempBuffer)-1, OCI_HTYPE_ERROR);
        if( NULL != pszMsg )
            sprintf( pszMsg, "(ErrorCode=%ld): %s", errcode, TempBuffer ); 
        break;

    case OCI_INVALID_HANDLE:
        if( NULL != pszMsg )
            strcpy( pszMsg, (char*)"Error - OCI_INVALID_HANDLE" );
        break;

    case OCI_STILL_EXECUTING:
        if( NULL != pszMsg )
            strcpy( pszMsg, (char*)"Error - OCI_STILL_EXECUTE" );
        break;

    case OCI_CONTINUE:
        if( NULL != pszMsg )
            strcpy( pszMsg, (char*)"Error - OCI_CONTINUE" );
        break;

    default:
        if( NULL != pszMsg )
            strcpy( pszMsg, (char*)"Error - Unknown" );
        break;
    }

    return errcode;
}

/*M***************************************************************************
Method Name  : TinyOci::Connect
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool  TinyOci::Connect( const char *pszConnectStr, const char *pszUser, const char *pszPasswd )
{    
    // Attach to ORACLE
    m_Status = OCIServerAttach( m_phOCIServer, m_phErrorHandle, (OraText *)pszConnectStr, strlen((char*)pszConnectStr), OCI_DEFAULT);
    if( OCI_SUCCESS != m_Status )
    {        
        return false;
    }

    // Associate DBServer with Service Context
    m_Status = OCIAttrSet ( m_phOCISvcCtx, OCI_HTYPE_SVCCTX, m_phOCIServer, 0, OCI_ATTR_SERVER, m_phErrorHandle );    
    if(OCI_SUCCESS != m_Status)
    {        
        return false;
    }

    // Set User name
    m_Status = OCIAttrSet( m_phOCISession, OCI_HTYPE_SESSION, (void*)pszUser, strlen(pszUser), OCI_ATTR_USERNAME, m_phErrorHandle );
    if(m_Status != OCI_SUCCESS)
    {
        return false;
    }
    
    // Set password
    m_Status = OCIAttrSet( m_phOCISession, OCI_HTYPE_SESSION, (void*)pszPasswd, strlen( pszPasswd ), OCI_ATTR_PASSWORD, m_phErrorHandle );
    if(m_Status != OCI_SUCCESS)
    {
        return false;
    }

    // Authenticate
    m_Status = OCISessionBegin ( m_phOCISvcCtx, m_phErrorHandle, m_phOCISession, OCI_CRED_RDBMS, OCI_DEFAULT );
    if(OCI_SUCCESS != m_Status)
    {        
        return false;
    }

    // Set the Authentication handle in the service handle
    m_Status = OCIAttrSet( m_phOCISvcCtx, OCI_HTYPE_SVCCTX, m_phOCISession, 0,  OCI_ATTR_SESSION, m_phErrorHandle );
    if (OCI_SUCCESS != m_Status)
    {        
        return false;
    }

    return true;
}


/*M***************************************************************************
Method Name  : TinyOci::Disconnect
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool  TinyOci::Disconnect( void )
{
    sword m_Status;

    m_Status = OCISessionEnd( m_phOCISvcCtx, m_phErrorHandle, m_phOCISession, (ub4)0 );
    if (OCI_SUCCESS != m_Status)
    {     
        return false;
    }
    m_Status = OCIServerDetach( m_phOCIServer, m_phErrorHandle, (ub4)OCI_DEFAULT );
    if (OCI_SUCCESS != m_Status)
    {     
        return false;
    }

    return true;
}


/*M***************************************************************************
Method Name  : TinyOci::IsSelect
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool  TinyOci::IsSelect( void )
{
    return ( OCI_STMT_SELECT == m_StmtType );
}


/*M***************************************************************************
Method Name  : TinyOci::Commit
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool  TinyOci::Commit( void )
{
    sword m_Status;

    m_Status = OCITransCommit( m_phOCISvcCtx, m_phErrorHandle, OCI_DEFAULT );
    if (OCI_SUCCESS != m_Status)
    {     
        return false;
    }

    return true;
}


/*M***************************************************************************
Method Name  : TinyOci::RollBack
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool  TinyOci::RollBack( void )
{
    sword m_Status;

    m_Status = OCITransRollback( m_phOCISvcCtx, m_phErrorHandle, OCI_DEFAULT );
    if (OCI_SUCCESS != m_Status)
    {     
        return false;
    }

    return true;
}

/*M***************************************************************************
Method Name  : TinyOci::Bind
            
Return       :                
Process      :
Note         : IndicatorArray is allocated here !
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::Bind( void )
{
    OCIBind  *phBind;
    TinyItem *pTinyItem;
    int i;

    for(i=0; i<BindNameList.GetCount(); i++ )
    {
        pTinyItem = (TinyItem *)BindNameList.GetAt(i);                

        // 有需要用到Indicator吗? 也许可以提供一些高级功能，如
        // 指定某行某列为“空值”。
        pTinyItem->IndicatorArray = new sb2[m_nIter];
        memset( pTinyItem->IndicatorArray, 0, m_nIter*sizeof(sb2) );
        
        m_Status = OCIBindByName( m_phStmtHandle, 
                                  (OCIBind**)&phBind,
                                  m_phErrorHandle, 
                                  (ub1*)pTinyItem->szName, 
                                  strlen( pTinyItem->szName ), 
                                  pTinyItem->pValueArray, 
                                  pTinyItem->lSize,
                                  pTinyItem->nType,
                                  pTinyItem->IndicatorArray, 
                                  (ub2 *) 0, 
                                  (ub2 *) 0, 
                                  (ub4)   0,
                                  (ub4*)  0,
                                  OCI_DEFAULT );
        if( OCI_SUCCESS != m_Status )
            return false;

        // 只有非SELECT语句才能支持数组输入绑定。
        if( ( m_nIter > 1 ) && !IsSelect() )
        {
            m_Status = OCIBindArrayOfStruct( (OCIBind*)phBind,
                                             (OCIError*)m_phErrorHandle,
                                             (ub4)pTinyItem->lSize,
                                             (ub4)sizeof(sb2),
                                             (ub4)0,
                                             (ub4)0
                                             );
            if( OCI_SUCCESS != m_Status )
                return false;
        }
    }

    return true;
}

/*M***************************************************************************
Method Name  : TinyOci::Define
            
Return       :                
Process      :
Note         : IndicatorArray is allocated here !
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::Define( void )
{
    OCIDefine   *phDefine;

    TinyItem *pTinyItem;
    int i;

    for(i=0; i<DefineNameList.GetCount(); i++ )
    {
        pTinyItem = (TinyItem *)DefineNameList.GetAt(i);
        
        pTinyItem->IndicatorArray = new sb2[m_lMaxFetch];
        memset( pTinyItem->IndicatorArray, 0, m_lMaxFetch * sizeof( sb2 ) );        

        m_Status = OCIDefineByPos( m_phStmtHandle, 
                                   (OCIDefine**)&phDefine,
                                   m_phErrorHandle, 
                                   i+1,
                                   pTinyItem->pValueArray, 
                                   pTinyItem->lSize, 
                                   pTinyItem->nType,
                                   pTinyItem->IndicatorArray, 
                                   (ub2 *) 0, 
                                   (ub2 *) 0, 
                                   OCI_DEFAULT );
        if( OCI_SUCCESS != m_Status )
            return false;

        if( m_lMaxFetch > 1 )
        {
            m_Status = OCIDefineArrayOfStruct(  (OCIDefine*)phDefine,
                                                (OCIError*)m_phErrorHandle,
                                                (ub4)pTinyItem->lSize,
                                                (ub4)sizeof(sb2),
                                                (ub4)0,
                                                (ub4)0
                                                );
            if( OCI_SUCCESS != m_Status )
                return false;
        }
    }

    return true;
}



/*M***************************************************************************
Method Name  : TinyOci::TranslateSizeType
            
Return       :                
Process      : Oracle Type System Type(Attribute geting) 
               to SQLT Type (bind,define).

Note         : Any OCI Type Code will be maped to the followings only:
               SQLT_FLT - double
               SQLT_INT - long
               SQLT_STR - sz char

               注：可以把所有基本数据类型都按 SQLT_STR 进行处理，但有以下的问题：
               1. 必须假定OCI_TYPECODE_NUMBER，OCI_TYPECODE_REAL，OCI_TYPECODE_DOUBLE，
                  OCI_TYPECODE_FLOAT，OCI_TYPECODE_DECIMAL，OCI_TYPECODE_OCTET，
                  OCI_TYPECODE_INTEGER，OCI_TYPECODE_SMALLINT类型的最大值，如假定
                  最多只能有十进制30位；
               2. 这样做可以很容易确定某一行的某一字段是否为“空值”:即是否为空字符串。

Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::TranslateSizeType( sb4 &lSize, ub2 &nType, ub2 nScale, ub2 nPrecision )
{
    bool bRc;

    bRc = true;
    switch( nType )
    {
    case OCI_TYPECODE_REF:    
        bRc = false;
        break;

    case OCI_TYPECODE_DATE:
        nType = SQLT_STR;
        lSize = 21;
        break;

    case OCI_TYPECODE_NUMBER:        
        if( 0 != nScale )
        {
            nType = SQLT_FLT;
            lSize = sizeof(double);
        }
        else if( (0 == nScale) && (0 != nPrecision) )
        {
            nType = SQLT_INT;
            lSize = sizeof(long);
        }
        else
        {
            nType = SQLT_FLT;
            lSize = sizeof(double);
        }

        // For Debug
        nType = SQLT_STR;
        lSize = 30;
        break;

    case OCI_TYPECODE_REAL: 
    case OCI_TYPECODE_DOUBLE: 
    case OCI_TYPECODE_FLOAT:
        nType = SQLT_FLT;
        lSize = sizeof(double);

        // For Debug
        nType = SQLT_STR;
        lSize = 30;
        break;
    
    case OCI_TYPECODE_DECIMAL: 
    case OCI_TYPECODE_OCTET: 
    case OCI_TYPECODE_INTEGER: 
    case OCI_TYPECODE_SMALLINT: 
        nType = SQLT_INT;
        lSize = sizeof(long);

        // For Debug
        nType = SQLT_STR;
        lSize = 30;
        break;

    case OCI_TYPECODE_RAW: 
        bRc = false;
        break;

    case OCI_TYPECODE_VARCHAR2:   
    case OCI_TYPECODE_VARCHAR: 
    case OCI_TYPECODE_CHAR:     
        nType = SQLT_STR;
        lSize = lSize + 1;
        break;

    case OCI_TYPECODE_VARRAY:
    case OCI_TYPECODE_TABLE: 
    case OCI_TYPECODE_CLOB: 
    case OCI_TYPECODE_BLOB: 
    case OCI_TYPECODE_BFILE: 
    case OCI_TYPECODE_OBJECT: 
    case OCI_TYPECODE_NAMEDCOLLECTION:
    default:
        bRc = false;
        break;
    }

    return bRc;
}

/*M***************************************************************************
Method Name  : TinyOci::DescribeDefine
            
Return       :                
Process      :
Note         : IndicatorArray is allocated here !
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::DescribeDefine( void )
{
    ub4       i = 0;
    ub4       nNameLen = 0;
    char     *pszName= 0;
    sb4       lSize  = 0;
    ub2       nType  = 0;
    ub2       nScale = 0;
    ub2       nPrecision = 0;
    ub4       nPara  = 0;
    OCIParam  *pOCIParam = 0; 
    TinyItem  *pTinyItem = 0;
    OCIDefine *phDefine  = 0;    

    if( !IsSelect() )
        return false;

    // get the number of columns in the select list 
    m_Status = OCIAttrGet ( (dvoid *)m_phStmtHandle, 
                            (ub4)OCI_HTYPE_STMT, 
                            (dvoid *)&nPara, 
                            (ub4 *) 0, 
                            (ub4)OCI_ATTR_PARAM_COUNT, 
                            m_phErrorHandle ); 
    if( OCI_SUCCESS != m_Status )
        return false;
    
    // Clean pre-define list
    CleanDescDefineList();

    // get describe information for each column 
    for(i = 0; i<nPara; i++) 
    {
        // 必须初始化这些变量，
        // 否则OCIAttrGet可能给出不正确结果 !
        nNameLen   = 0;
        pszName    = 0;
        lSize      = 0;
        nType      = 0;
        nScale     = 0;
        nPrecision = 0;

        OCIParamGet( (dvoid *)m_phStmtHandle, OCI_HTYPE_STMT, m_phErrorHandle, (void**)&pOCIParam, i+1 ); 
        m_Status = OCIAttrGet( (dvoid*)pOCIParam, 
                               (ub4) OCI_DTYPE_PARAM, 
                               (dvoid*) &nType,
                               (ub4 *) 0, 
                               (ub4) OCI_ATTR_DATA_TYPE, 
                               (OCIError *)m_phErrorHandle );
        if( OCI_SUCCESS != m_Status )
            return false;

        // Should I FREE the returned pszName ?!!!
        // NO, IT IS OCI TO DO !
        m_Status = OCIAttrGet( (dvoid*)pOCIParam, 
                               (ub4) OCI_DTYPE_PARAM, 
                               (dvoid**)&pszName,
                               (ub4 *)&nNameLen, 
                               (ub4) OCI_ATTR_NAME, 
                               (OCIError *)m_phErrorHandle );
        if( OCI_SUCCESS != m_Status )
            return false;

        m_Status = OCIAttrGet( (dvoid*)pOCIParam, 
                               (ub4) OCI_DTYPE_PARAM, 
                               (dvoid*)&lSize,
                               (ub4 *)0, 
                               (ub4) OCI_ATTR_DATA_SIZE, 
                               (OCIError *)m_phErrorHandle );
        if( OCI_SUCCESS != m_Status )
            return false;

        m_Status = OCIAttrGet( (dvoid*)pOCIParam, 
                               (ub4) OCI_DTYPE_PARAM, 
                               (dvoid*)&nPrecision,
                               (ub4 *)0, 
                               (ub4) OCI_ATTR_PRECISION, 
                               (OCIError *)m_phErrorHandle );
        if( OCI_SUCCESS != m_Status )
            return false;

        m_Status = OCIAttrGet( (dvoid*)pOCIParam, 
                               (ub4) OCI_DTYPE_PARAM, 
                               (dvoid*)&nScale,
                               (ub4 *)0, 
                               (ub4) OCI_ATTR_SCALE, 
                               (OCIError *)m_phErrorHandle );
        if( OCI_SUCCESS != m_Status )
            return false;
        
        // OCI TypeCode to SQLT
        if( !TranslateSizeType( lSize, nType, nScale, nPrecision ) )
            return false;

        // Setup Define Item                        
        pTinyItem = new TinyItem;
        pTinyItem->IndicatorArray = new sb2[m_lMaxFetch];                
        pTinyItem->lSize          = lSize;
        pTinyItem->nType          = nType;
        // 统一放成char
        pTinyItem->pValueArray    = (void*)new char[lSize*m_lMaxFetch];

        memset( pTinyItem->pValueArray, 0, m_lMaxFetch * pTinyItem->lSize );
        memset( pTinyItem->IndicatorArray, 0, m_lMaxFetch * sizeof( sb2 ) );
        
        if( nNameLen >= TINYOCI_MAX_NAME_LEN )
            nNameLen = TINYOCI_MAX_NAME_LEN-1;
        strncpy( pTinyItem->szName, pszName, nNameLen );
        pTinyItem->szName[nNameLen] = 0;

        // Push into our define list
        DescDefineNameList.Append( pszName, pTinyItem );        

        // Start defining
        m_Status = OCIDefineByPos( m_phStmtHandle, 
                                   (OCIDefine**)&phDefine,
                                   m_phErrorHandle, 
                                   i+1,
                                   pTinyItem->pValueArray, 
                                   pTinyItem->lSize, 
                                   pTinyItem->nType,
                                   pTinyItem->IndicatorArray, 
                                   (ub2 *) 0, 
                                   (ub2 *) 0, 
                                   OCI_DEFAULT );//OCI_DYNAMIC_FETCH
        if( OCI_SUCCESS != m_Status )
            return false;

        if( m_lMaxFetch > 1 )
        {
            m_Status = OCIDefineArrayOfStruct(  phDefine,
                                                m_phErrorHandle,
                                                (ub4)pTinyItem->lSize,
                                                (ub4)sizeof(sb2),
                                                (ub4)0,
                                                (ub4)0
                                                );
            if( OCI_SUCCESS != m_Status )
                return false;
        }

    }// End for loop

    return true;
}

/*M***************************************************************************
Method Name  : TinyOci::Prepare
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::Prepare( const char *pszSql )
{
    ub4	  sizep;

    m_Status = OCIStmtPrepare( m_phStmtHandle,
                               m_phErrorHandle,
                               (OraText*)pszSql,
                               (ub4)strlen((char*)pszSql),
                               (ub4)OCI_NTV_SYNTAX,
                               (ub4)OCI_DEFAULT );
    if( OCI_SUCCESS != m_Status )
        return false;

    // Get statement type
    m_Status = OCIAttrGet( (dvoid *)m_phStmtHandle, 
                           (ub4) OCI_HTYPE_STMT, 
                           (dvoid *) &m_StmtType, 
                           (ub4*) &sizep, 
                           (ub4) OCI_ATTR_STMT_TYPE , 
                           m_phErrorHandle );
    if( OCI_SUCCESS != m_Status )
        return false;

    if( ( m_lPrefetch > 0 ) && IsSelect() )
    {
        m_Status = OCIAttrSet( m_phStmtHandle,
                               OCI_HTYPE_STMT,
                               &m_lPrefetch,
                               0,
                               OCI_ATTR_PREFETCH_ROWS,
                               m_phErrorHandle );
        if( OCI_SUCCESS != m_Status )
            return false;
    }

    return true;
}

/*M***************************************************************************
Method Name  : TinyOci::Execute
            
Return       :                
Process      :
Note         : 1. Only BLOCK mode is supported.
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::Execute( const char *pszSql, int nIter )
{
    // Keep it
    m_nIter = nIter;

    // 调用OCIStmtPrepare准备该SQL语句
    if( !Prepare( pszSql ) )    
        return false;    
    
    // 检查BindNameList是否为空，如果非空，则根据名称绑定所有输入变量
    if( !Bind() )    
        return false;    

    // 当执行一条SELECT语句时，nIter参数被忽略，且重复执行的次数设置为0。
    if( IsSelect() )    
        nIter = 0;    

    // Reset counters
    m_lRowCountSoFar= 0;
    m_lRowFetched   = 0;     

    // 调用OCIStmtExecute执行该SQL语句。
    m_Status = OCIStmtExecute( m_phOCISvcCtx,
                               m_phStmtHandle,
                               m_phErrorHandle,
                               nIter,
                               (ub4)0,
                               (OCISnapshot*)0,
                               (OCISnapshot*)0,
                               (ub4)OCI_DEFAULT );
    if( OCI_SUCCESS != m_Status )
        return false;   

    // 如果是OCI_STMT_SELECT，则：
    if( IsSelect() )
    {
        // 检查DefineNameList是否为空，如果非空，则根据名称绑定所有输出变量。
        if( DefineNameList.GetCount() > 0 )
        {
            if( !Define() )
                return false;
        }
        // 如果DefineNameList为空，则:Desribe Select-List and Define
        else
        {
            if( !DescribeDefine( ) )
                return false;
        }
    }

    return true;
}

/*M***************************************************************************
Method Name  : TinyOci::CleanDefineBuffer
            
Return       :                               
Process      :
Note         : Called by short TinyOci::Fetch( long &lRows ) ONLY !
   
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::CleanDefineBuffer( void )
{
    int i;
    TinyNamedPtrList* pDefineList;
    TinyItem *pTinyItem;

    pDefineList = CurrentDefineList( );
    if( NULL == pDefineList )
        return false;

    for( i=0; i<pDefineList->GetCount(); i++ )
    {        
        pTinyItem = (TinyItem *)pDefineList->GetAt(i);
        if( NULL != pTinyItem->pValueArray )
        {
            memset( pTinyItem->pValueArray, 0, m_lMaxFetch * pTinyItem->lSize );         
        }
        if( NULL != pTinyItem->IndicatorArray )
        {         
            memset( pTinyItem->IndicatorArray, 0, m_lMaxFetch * sizeof( sb2 ) );
        }
    }

    return true;
}


/*M***************************************************************************
Method Name  : TinyOci::Fetch
            
Return       : TINYOCI_FETCH_ERROR 
               TINYOCI_FETCH_DONE   -> 取了一批数据  
               TINYOCI_FETCH_MORE   -> 取了一批数据              
               TINYOCI_FETCH_NODATA
                                             
Process      :
Note         : 
   
Author       : 
Date         :
Revision     :
***************************************************************************M*/
short TinyOci::Fetch( long &lRows )
{
    short rc;
    ub4   lRowCountSoFar;
    sword Status;

    if( !IsSelect() )
        return TINYOCI_FETCH_ERROR;

    lRows = 0;
    rc    = TINYOCI_FETCH_DONE;
        
    // 清除前一次FETCH得到的数据
    if( !CleanDefineBuffer() )
        return TINYOCI_FETCH_ERROR;

    m_Status = OCIStmtFetch( m_phStmtHandle, 
                             m_phErrorHandle,// Notes:
                             m_lMaxFetch,                                           
                             OCI_FETCH_NEXT,
                             OCI_DEFAULT );
    if( ( OCI_SUCCESS           != m_Status ) && 
        ( OCI_SUCCESS_WITH_INFO != m_Status ) &&
        ( OCI_NO_DATA           != m_Status ) )
        return TINYOCI_FETCH_ERROR;

    Status = OCIAttrGet( (dvoid *)m_phStmtHandle, 
                         (ub4)OCI_HTYPE_STMT, 
                         (dvoid *) &lRowCountSoFar, 
                         (ub4 *) 0, 
                         (ub4)OCI_ATTR_ROW_COUNT, 
                         m_phErrorHandle ); 
    if( OCI_SUCCESS != Status )
    {
        m_Status = Status;
        return TINYOCI_FETCH_ERROR;
    }
        
    switch( m_Status )
    {
    case OCI_NO_DATA:
        rc = TINYOCI_FETCH_NODATA;

        // 也有可能是最后一批数据                
        m_lRowFetched    = lRowCountSoFar - m_lRowCountSoFar;
        m_lRowCountSoFar = lRowCountSoFar;        
        if( m_lRowFetched > 0 )
            rc = TINYOCI_FETCH_DONE;
        break;

    case OCI_SUCCESS:
    case OCI_SUCCESS_WITH_INFO:
        rc = TINYOCI_FETCH_MORE;
        
        // 也有可能是最后一批数据                
        m_lRowFetched    = lRowCountSoFar - m_lRowCountSoFar;
        m_lRowCountSoFar = lRowCountSoFar;                           
        if( m_lRowFetched < m_lMaxFetch )
            rc = TINYOCI_FETCH_DONE;
        break;
    }

    lRows = m_lRowFetched;
    return rc;
}

short TinyOci::Fetch( vector<AnyValue> &val )
{
    long  i;
    short f;
    long  lRows;
    short rc;
    TinyNamedPtrList *pDefineList;
    TinyItem *pTinyItem;
    char cStrRes[128] = {0};
    AnyValue sResult;

    rc = Fetch( lRows );
    switch( rc )
    {
    case TINYOCI_FETCH_ERROR:
    case TINYOCI_FETCH_NODATA:
        break;

    case TINYOCI_FETCH_DONE:
    case TINYOCI_FETCH_MORE:        
        if( NULL == (pDefineList = CurrentDefineList()) )
            return TINYOCI_FETCH_ERROR;

        val.clear();
        val.reserve(lRows);
        for( i=0; i<lRows; i++ )
        {
            for( f=0; f < pDefineList->GetCount(); f++ )
            {
                // 把每一个字段转换成字符串
                // 检查每一个字段是否为空值。空字符串可以用来表示“空值”。
                pTinyItem = (TinyItem *)pDefineList->GetAt(f);                                
                memset(cStrRes, 0x00, sizeof(cStrRes));
                switch( pTinyItem->nType )
                {
                    case SQLT_FLT:// - double
                        if( -1 == pTinyItem->IndicatorArray[i] )
                            sResult.setNull();
                        else
                            sResult.setDouble(((double*)pTinyItem->pValueArray)[i]);
                        break;
                    case SQLT_INT:// - long
                        if( -1 == pTinyItem->IndicatorArray[i] )
                            sResult.setNull();
                        else
                            sResult.setInt64(((long long*)(pTinyItem->pValueArray))[i]);
                        break;
                    case SQLT_STR:// - sz char                    
                        if( ( -1 == pTinyItem->IndicatorArray[i] ) ||
                                ((((const char*)pTinyItem->pValueArray) + i*pTinyItem->lSize)[0] == 0) )
                            sResult.setNull();
                        else
                            sResult.setString(string(((const char*)pTinyItem->pValueArray) +
                                    i*pTinyItem->lSize, pTinyItem->lSize));
                        break;
                    default:
                        return TINYOCI_FETCH_ERROR;
                }
                
                // 取得一个字段
                val.push_back(sResult);
            }
        }

        break;
    }

    return rc;
}

/*M***************************************************************************
Method Name  : TinyOci::CurrentDefineList
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
TinyNamedPtrList* TinyOci::CurrentDefineList( void )
{
    if( DescDefineNameList.GetCount() > 0 )
        return &DescDefineNameList;
    else if( DefineNameList.GetCount() > 0 )
        return &DefineNameList;
    else 
        return (TinyNamedPtrList*)NULL;    
}

/*M***************************************************************************
Method Name  : TinyOci::CheckNull
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
void TinyOci::CheckNull( void )
{
}

/*M***************************************************************************
Method Name  : TinyOci::SetPrefetch
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool  TinyOci::SetPrefetch( long lPrefetch )
{
    m_lPrefetch = lPrefetch;
    return true;
}

/*M***************************************************************************
Method Name  : TinyOci::SetMaxFetch
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool  TinyOci::SetMaxFetch( long lMaxFetch )
{
    m_lMaxFetch = (lMaxFetch > TINYOCI_MAXFETCH) ? TINYOCI_MAXFETCH:lMaxFetch;
    return true;
}

/*M***************************************************************************
Method Name  : TinyOci::IsCommBreak
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::IsCommBreak( void )
{
    sb4 aErrCode[] = 
    {
        TINYOCI_CONNECTION_BROKEN,
        TINYOCI_SESSION_KILLED,   
        TINYOCI_IVALID_SESSION,   
        TINYOCI_EOF_COMM_CHANNEL 
    };
    sb4 ErrorCode;
    int nItem;
    int i;

    ErrorCode = GetError( NULL );    
    nItem     = sizeof( aErrCode )/sizeof( aErrCode[0] );
    for( i=0; i<nItem; i++ )
    {
        if( ErrorCode == aErrCode[i] )
            return true;
    }

    return false;
}

/*M***************************************************************************
Method Name  : TinyOci::PushBindList
            
Return       :                
Process      :
Note         : IndicatorArray allocation is defered !
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::PushBindList( const char *pszName, ub2 DataType, long lSize, void *pValue )
{
    TinyItem *p;
    
    p = new TinyItem;
    strcpy( p->szName, pszName );
    p->nType          = DataType;
    p->lSize          = lSize;
    p->pValueArray    = pValue;
    p->IndicatorArray =  NULL; // Defered

    return BindNameList.Append( pszName, p );
}

/*M***************************************************************************
Method Name  : TinyOci::PushDefineList
            
Return       :                
Process      :
Note         : IndicatorArray allocation is defered !
               
               DataType只能取以下的值：
               SQLT_FLT
               SQLT_INT
               SQLT_STR
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::PushDefineList( const char *pszName, ub2 DataType, long lSize, void *pValue )
{
    bool bRc = false;
    TinyItem *p;
    
    switch( DataType )
    {
    case SQLT_FLT:
    case SQLT_INT:
    case SQLT_STR:
        p = new TinyItem;
        strcpy( p->szName, pszName );
        p->nType          = DataType;
        p->lSize          = lSize;
        p->pValueArray    = pValue;
        p->IndicatorArray =  NULL; // Defered
        
        bRc = DefineNameList.Append( p->szName, p );
        break;

    default:
        bRc = false;
        break;
    }
    
    return bRc;
}

/*M***************************************************************************
Method Name  : TinyOci::CleanBindList,CleanDefineList
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::CleanBindList( void )
{
    TinyItem *pTinyItem;
    int i;

    for(i=0; i<BindNameList.GetCount(); i++ )
    {
        pTinyItem = (TinyItem *)BindNameList.GetAt(i);
        if( NULL != pTinyItem->IndicatorArray )
        {
            delete [] pTinyItem->IndicatorArray;
            pTinyItem->IndicatorArray = NULL;
        }
        delete pTinyItem;
    }

    BindNameList.Clean();    
    return true;
}

bool TinyOci::CleanDefineList( void )
{
    TinyItem *pTinyItem;
    int i;

    for(i=0; i<DefineNameList.GetCount(); i++ )
    {
        pTinyItem = (TinyItem *)DefineNameList.GetAt(i);
        if( NULL != pTinyItem->IndicatorArray )
        {
            delete [] pTinyItem->IndicatorArray;
            pTinyItem->IndicatorArray = NULL;
        }
        delete pTinyItem;
    }
    
    DefineNameList.Clean();
    return true;
}

bool TinyOci::CleanDescDefineList( void )
{
    TinyItem *pTinyItem;
    int i;

    for(i=0; i<DescDefineNameList.GetCount(); i++ )
    {
        pTinyItem = (TinyItem *)DescDefineNameList.GetAt(i);
        if( NULL != pTinyItem->IndicatorArray )
        {            
            delete [] (char*)(pTinyItem->IndicatorArray);
            pTinyItem->IndicatorArray = NULL;
        }

        if( NULL != pTinyItem->pValueArray )
        {            
            delete [] (char*)(pTinyItem->pValueArray);
            pTinyItem->pValueArray = NULL;
        }

        delete pTinyItem;
    }
    
    DescDefineNameList.Clean();
    return true;
}

bool TinyOci::ResetList( void )
{
    return ( CleanBindList() &&
             CleanDefineList() &&
             CleanDescDefineList()
           );
}

/*M***************************************************************************
Method Name  : TinyOci::SetDateFormat
            
Return       :                
Process      :
Note         : 
Author       : 
Date         :
Revision     :
***************************************************************************M*/
bool TinyOci::SetDateFormat( short nFormat )
{    
    char szFormat[256];

    switch( nFormat )
    {
    case TINYOCI_DATEFORMAT_1:
        strcpy( szFormat, "Alter session set NLS_DATE_FORMAT = 'YYYYMMDD' ");
        break;
    case TINYOCI_DATEFORMAT_3:
        strcpy( szFormat, "Alter session set NLS_DATE_FORMAT = 'YYYY-MM-DD HH24:MI:SS' ");
        break;
    case TINYOCI_DATEFORMAT_4:
        strcpy( szFormat, "Alter session set NLS_DATE_FORMAT = 'DD-MON-YY' ");
        break;
    case TINYOCI_DATEFORMAT_5:
        strcpy( szFormat, "Alter session set NLS_DATE_FORMAT = 'DD-MON-YYYY' ");
        break;
    case TINYOCI_DATEFORMAT_2:
    default:
        strcpy( szFormat, "Alter session set NLS_DATE_FORMAT = 'YYYYMMDDHH24MISS' ");
        break;
    }

    return Execute( szFormat );
}



bool AnyValue::isNull()
{
    return bNull;
}

void AnyValue::freeVal()
{
    switch(Type)
    {
    case eIntVal:
        delete Val.pInt;
        break;
    case eInt64Val:
        delete Val.pInt64;
        break;
    case  eDoubleVal:
        delete Val.pDouble;
        break;
    case  eStringVal:
        delete Val.pString;
        break;
    //case  eDateVal:
    //    delete Val.pDate;
    //    break;
    //case  eTimeVal:
    //    delete Val.pTime;
    //    break;
    //case  eDatetimeVal:
    //    delete Val.pDatetime;
    //    break;
    //case  eBinaryVal:
    //    delete Val.pBinary;
    //    break;
    case eNullVal:
    default:
        ;
    }

    bNull = true;
    Val.pInt = NULL;
}


void AnyValue::setNull()
{
    bNull = true;
    freeVal();
}


void AnyValue::setType(Type_t type_)
{
    if (type_==Type)
        return ;

    bNull = false;
    Type = type_;
    switch(Type)
    {
    case eIntVal:
        Val.pInt = new int;
        break;
    case eInt64Val:
        Val.pInt64 = new TInt64;
        break;
    case  eDoubleVal:
        Val.pDouble = new double;
        break;
    case  eStringVal:
        Val.pString = new std::string("");
        break;
    //case  eDateVal:
    //    Val.pDate = new Date();
    //    break;
    //case  eTimeVal:
    //    Val.pTime = new Time();
    //    break;
    //case  eDatetimeVal:
    //    Val.pDatetime = new Datetime();
    //    break;
    //case  eBinaryVal:
    //    Val.pBinary = new MemBuffer();
    //    break;
    case eNullVal:
        setNull();
        break;
    default:
        ;
    }
}


void AnyValue::setInt( const int& v )
{
    setType(eIntVal);
    *(Val.pInt) = v;
}

void AnyValue::setInt64( const TInt64& v )
{
    setType(eInt64Val);
    *(Val.pInt64) = v;
}


void AnyValue::setDouble( const double& v )
{
    setType(eDoubleVal);
    *(Val.pDouble) = v;
}

void AnyValue::setString( const string& v )
{
    setType(eStringVal);
    *(Val.pString) = v;
}

//void AnyValue::setDate( const Date& v )
//{
//    setType(eDateVal);
//    *(Val.pDate) = v;
//}
//
//void AnyValue::setTime( const Time& v )
//{
//    setType(eTimeVal);
//    *(Val.pTime) = v;
//}
//
//void AnyValue::setDatetime( const Datetime& v )
//{
//    setType(eDatetimeVal);
//    *(Val.pDatetime) = v;
//}
//
//void AnyValue::setBinary( void )
//{
//    setType(eBinaryVal);
//}

AnyValue::AnyValue():
bNull(true),
Type(eNullVal)
{
    Val.pInt = NULL;
}


AnyValue::AnyValue( Type_t t ):
bNull(true),
Type(eNullVal)
{
    Val.pInt = NULL;
    //Z_ASSERT( t>=eNullVal && t<=eBinaryVal );
    setType(t);
}

AnyValue::AnyValue( const AnyValue& other ):
bNull(true),
Type(eNullVal)
{
    Val.pInt = NULL;
    copyVal(other, *this);
}


AnyValue& AnyValue::operator=( const AnyValue& other )
{
    if (&other != this)
    {
        copyVal(other, *this);
    }
    return *this;
}


void AnyValue::copyVal(const AnyValue& from, AnyValue& to)
{
    to.bNull = from.bNull;
    to.setType(from.Type);
    switch(from.Type)
    {
    case eIntVal:
        *(to.Val.pInt) = *(from.Val.pInt);
        break;
    case eInt64Val:
        *(to.Val.pInt64) = *(from.Val.pInt64);
        break;
    case  eDoubleVal:
        *(to.Val.pDouble) = *(from.Val.pDouble);
        break;
    case  eStringVal:
        *(to.Val.pString) = *(from.Val.pString);
        break;
    //case  eDateVal:
    //    *(to.Val.pDate) = *(from.Val.pDate);
    //    break;
    //case  eTimeVal:
    //    *(to.Val.pTime) = *(from.Val.pTime);
    //    break;
    //case  eDatetimeVal:
    //    *(to.Val.pDatetime) = *(from.Val.pDatetime);
    //    break;
    //case  eBinaryVal:
    //    *(to.Val.pBinary) = *(from.Val.pBinary);
    //    break;
    case eNullVal:
    default:
        ;
    }
}


AnyValue::~AnyValue()
{
    //U_LOG_X(eTRACE) << "AnyValue::Freeing #"<< this << "(" << Type << ")";
    freeVal();
}


int& AnyValue::getInt()
{
//    if (Type!=eIntVal)
//        logSQLExceptionX(Z_SOURCEINFO, -1, "Internal type is not Int");
//
//    Z_ASSERT( Val.pInt != NULL );
    return *(Val.pInt);
}

TInt64& AnyValue::getInt64()
{
//    if (Type!=eInt64Val)
//        logSQLExceptionX(Z_SOURCEINFO, -1, "Internal type is not Int64");
//
//    Z_ASSERT( Val.pInt64 != NULL );
    return *(Val.pInt64);
}


double& AnyValue::getDouble()
{
//    if (Type!=eDoubleVal)
//        logSQLExceptionX(Z_SOURCEINFO, -1, "Internal type is not Double");
// 
//    Z_ASSERT( Val.pDouble != NULL );
    return *(Val.pDouble);
}


string& AnyValue::getString()
{
//    if (Type!=eStringVal)
//        logSQLExceptionX(Z_SOURCEINFO, -1, "Internal type is not string");
//
//    Z_ASSERT( Val.pString != NULL );
    return *(Val.pString);
}


//Date& AnyValue::getDate()
//{
//    if (Type!=eDateVal)
//        logSQLExceptionX(Z_SOURCEINFO, -1, "Internal type is not Date");
//
//    Z_ASSERT( Val.pDate != NULL );
//    return *(Val.pDate);
//}
//
//
//Time& AnyValue::getTime()
//{
//    if (Type!=eTimeVal)
//        logSQLExceptionX(Z_SOURCEINFO, -1, "Internal type is not Time");
//
//    Z_ASSERT( Val.pTime != NULL );
//    return *(Val.pTime);
//}
//
//
//Datetime& AnyValue::getDatetime()
//{
//    if (Type!=eDatetimeVal)
//        logSQLExceptionX(Z_SOURCEINFO, -1, "Internal type is not Datetime");
//
//    Z_ASSERT( Val.pDatetime != NULL );
//    return *(Val.pDatetime);
//}
//
//
//MemBuffer& AnyValue::getBinary()
//{
//    if (Type!=eBinaryVal)
//        logSQLExceptionX(Z_SOURCEINFO, -1, "Internal type is not Binary");
//
//    Z_ASSERT( Val.pBinary != NULL );
//    return *(Val.pBinary);
//}

// End Of File
