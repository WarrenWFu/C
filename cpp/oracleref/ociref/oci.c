#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oci.h>


static text *username = (text *) "spring_oracle";
static text *password = (text *) "123123";
static text *dbname   = (text *) "MYDBORACLE";

static text *selectSQL = (text *)"SELECT BIGTXTIDEX FROM T_USI_BIGTXTDATA WHERE BIGTXTIDEX = :1";
static text *insertSQL = (text *)"INSERT INTO T_USI_BIGTXTDATA\
                      (PFWRKDATE, BIGTXTIDEX, BIGTXTTYPE, BIGTXTLEN, BIGTXTCNT, STATE)\
                      VALUES ('20160830', :BIGTXTIDEX, 'testtype', 10, 'testtxt', 'TEST')";
static text *updateSQL = (text *)"UPDATE T_USI_BIGTXTDATA SET STATE = 'RETE' WHERE BIGTXTIDEX = :1";
static text *deleteSQL = (text *)"DELETE FROM T_USI_BIGTXTDATA WHERE BIGTXTIDEX = :1";

static OCIEnv *envhp;
static OCIError *errhp;
static OCISession *authp;
static OCIServer *srvhp;
static OCISvcCtx *svchp;
static OCIStmt   *stmthp;
static OCIDefine *defnp;

static OCIBind  *bnd1p;             /* the 1 bind handle */
static OCIBind  *bnd2p;             /* the 2 bind handle */
static OCIBind  *bnd3p;             /* the 3 bind handle */
static OCIBind  *bnd4p;             /* the 4 bind handle */
static OCIBind  *bnd5p;             /* the 5 bind handle */
static OCIBind  *bnd6p;             /* the 6 bind handle */

static sword    myIndex, myLength;
static text     *myDate, *myType, *myTxt, *myState;

static sword status;
static sword errcode;
static int iLoop;

void checkerr(errhp, status)
    OCIError *errhp;
    sword status;
{
    text errbuf[512];
    sb4 errcode = 0;

    switch (status)
    {
        case OCI_SUCCESS:
            break;
        case OCI_SUCCESS_WITH_INFO:
            (void) printf("Error - OCI_SUCCESS_WITH_INFO\n");
            break;
        case OCI_NEED_DATA:
            (void) printf("Error - OCI_NEED_DATA\n");
            break;
        case OCI_NO_DATA:
            (void) printf("Error - OCI_NODATA\n");
            break;
        case OCI_ERROR:
            (void) OCIErrorGet((dvoid *)errhp, (ub4) 1, (text *) NULL, &errcode,
                    errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);
            (void) printf("Error - %.*s\n", 512, errbuf);
            break;
        case OCI_INVALID_HANDLE:
            (void) printf("Error - OCI_INVALID_HANDLE\n");
            break;
        case OCI_STILL_EXECUTING:
            (void) printf("Error - OCI_STILL_EXECUTE\n");
            break;
        case OCI_CONTINUE:
            (void) printf("Error - OCI_CONTINUE\n");
            break;
        default:
            break;
    }
}

void cleanup()
{
    if(myDate)
    {
        free(myDate);
        myDate = NULL;
    }
    if(myType)
    {
        free(myType);
        myType = NULL;
    }
    if(myTxt)
    {
        free(myTxt);
        myTxt = NULL;
    }
    if(myState)
    {
        free(myState);
        myState = NULL;
    }

    if (stmthp)
        checkerr(NULL, OCIHandleFree((dvoid *) stmthp, (ub4) OCI_HTYPE_STMT));

    checkerr(errhp, OCISessionEnd(svchp, errhp, authp, (ub4) OCI_DEFAULT));
    checkerr(errhp, OCIServerDetach( srvhp, errhp, (ub4) OCI_DEFAULT ));

    if (authp)
        checkerr(NULL, OCIHandleFree((dvoid *) authp,  (ub4) OCI_HTYPE_SESSION));
    if (srvhp)
        checkerr(NULL, OCIHandleFree((dvoid *) srvhp,  (ub4) OCI_HTYPE_SERVER));
    if (svchp)
        checkerr(NULL, OCIHandleFree((dvoid *) svchp,  (ub4) OCI_HTYPE_SVCCTX));
    if (errhp)
        checkerr(NULL, OCIHandleFree((dvoid *) errhp,  (ub4) OCI_HTYPE_ERROR));
    if (envhp)
        checkerr(NULL, OCIHandleFree((dvoid *) envhp,  (ub4) OCI_HTYPE_ENV));

    return;
}



void myConnect()
{
    //初始化执行环境
    errcode = OCIEnvCreate((OCIEnv **) &envhp, (ub4) OCI_DEFAULT,
            (dvoid *) 0, (dvoid * (*)(dvoid *,size_t)) 0,
            (dvoid * (*)(dvoid *, dvoid *, size_t)) 0,
            (void (*)(dvoid *, dvoid *)) 0, (size_t) 0, (dvoid **) 0);

    if (errcode != 0)
    {
        printf("OCIEnvCreate failed with errcode = %d.\n", errcode);
        exit(1);
    }

    //获取记录错误信息的handle
    OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, OCI_HTYPE_ERROR,
            (size_t) 0, (dvoid **) 0);

    //获取服务器句柄
    OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, OCI_HTYPE_SERVER,
            (size_t) 0, (dvoid **) 0);

    //获取服务句柄
    OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, OCI_HTYPE_SVCCTX,
            (size_t) 0, (dvoid **) 0);

    //检查连接是否有效
    checkerr(errhp, OCIServerAttach ( srvhp, errhp, (text *)dbname,
                (sb4) strlen((char *)dbname), 0));

    //将服务器handle作为属性赋值给服务handle
    (void) OCIAttrSet( (dvoid *) svchp, OCI_HTYPE_SVCCTX, (dvoid *)srvhp,
            (ub4) 0, OCI_ATTR_SERVER, (OCIError *) errhp);

    //获取会话handle
    (void) OCIHandleAlloc((dvoid *) envhp, (dvoid **)&authp,
            (ub4) OCI_HTYPE_SESSION, (size_t) 0, (dvoid **) 0);

    //将用户名作为属性赋值给会话handle
    (void) OCIAttrSet((dvoid *) authp, (ub4) OCI_HTYPE_SESSION,
            (dvoid *) username, (ub4) strlen((char *)username),
            (ub4) OCI_ATTR_USERNAME, errhp);

    //将密码作为属性赋值给会话handle
    (void) OCIAttrSet((dvoid *) authp, (ub4) OCI_HTYPE_SESSION,
            (dvoid *) password, (ub4) strlen((char *)password),
            (ub4) OCI_ATTR_PASSWORD, errhp);

    //用用户名和密码开始会话
    checkerr(errhp, OCISessionBegin ( svchp,  errhp, authp, OCI_CRED_RDBMS,
                (ub4) OCI_DEFAULT));

    //将会话handle作为属性赋值给服务handle
    (void) OCIAttrSet((dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX,
            (dvoid *) authp, (ub4) 0,
            (ub4) OCI_ATTR_SESSION, errhp);

}

void mySelect()
{
    //获取语句handle
    checkerr(errhp, OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &stmthp,
                OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0));

    //------------------查找------------------
    //使用查询字符串给语句handle赋值
    checkerr(errhp, OCIStmtPrepare(stmthp, errhp, selectSQL,
                (ub4) strlen((char *) selectSQL),
                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));

    sword testInt = 0;

    if ((status = OCIBindByName(stmthp, &bnd1p, errhp, (text *) ":1",
                    -1, (dvoid *) &myIndex, (sword) sizeof(sword), SQLT_INT, (dvoid *) 0,
                    (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)))
    {
        checkerr(errhp, status);
        cleanup();
    }

    myIndex = iLoop;

    //指定获取结果的变量，这里为testInt
    checkerr(errhp, OCIDefineByPos(stmthp, &defnp, errhp, 1, (dvoid *) &testInt,
                (sword) sizeof(sword), SQLT_INT, (dvoid *) 0, (ub2 *)0,
                (ub2 *)0, OCI_DEFAULT));

    /* execute and fetch */
    if ((status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 1, (ub4) 0,
                    (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT)))
    {
        if (status == OCI_NO_DATA)
            printf("未获取到结果");
        else
        {
            checkerr(errhp, status);
            cleanup();
        }
    }
    else
    {
    //    printf("结果是[%d]\n", testInt);
    }

    if (stmthp)
    {
        checkerr(NULL, OCIHandleFree((dvoid *) stmthp, (ub4) OCI_HTYPE_STMT));
        stmthp = NULL;
    }

}

void myInsert()
{
    //获取语句handle
    checkerr(errhp, OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &stmthp,
                OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0));

    //------------------插入------------------
    //使用插入字符串给会话句柄赋值
    checkerr(errhp, OCIStmtPrepare(stmthp, errhp, insertSQL,
                (ub4) strlen((char *) insertSQL),
                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));

    //分配内存,没有使用上面的获取handle时分配的内存
    //memset(myDate, 0x00, 8+2);
    //memset(myType, 0x00, 8+2);
    //memset(myTxt, 0x00, 10+2);
    //memset(myState, 0x00, 4+2);

    //模仿尽量不适用bind
    //绑定变量
    //if ((status = OCIBindByName(stmthp, &bnd1p, errhp, (text *) ":PFWRKDATE",
    //                -1, (dvoid *) myDate, 8+1, SQLT_STR, (dvoid *) 0,
    //                (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)) || 
    //        (status = OCIBindByName(stmthp, &bnd2p, errhp, (text *) ":BIGTXTIDEX", 
    //                                -1, (dvoid *) &myIndex, (sword) sizeof(sword), SQLT_INT, (dvoid *) 0,
    //                                (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)) ||
    //        (status = OCIBindByName(stmthp, &bnd3p, errhp, (text *) ":BIGTXTTYPE",
    //                                -1, (dvoid *) myType, 8+1, SQLT_STR, (dvoid *) 0,
    //                                (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)) ||
    //        (status = OCIBindByName(stmthp, &bnd4p, errhp, (text *) ":BIGTXTLEN",
    //                                -1, (dvoid *) &myLength, (sword) sizeof(myLength), SQLT_INT, (dvoid *) 0,
    //                                (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)) ||
    //        //clob要使用特定的对象处理
    //        (status = OCIBindByName(stmthp, &bnd5p, errhp, (text *) ":BIGTXTCNT",
    //                                -1, (dvoid *) myTxt, 10+1, SQLT_STR, (dvoid *) 0,
    //                                (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)) ||
    //        (status = OCIBindByName(stmthp, &bnd6p, errhp, (text *) ":STATE",
    //                                -1, (dvoid *) myState, 4+1, SQLT_STR, (dvoid *) 0,
    //                                (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)))
    if ((status = OCIBindByName(stmthp, &bnd2p, errhp, (text *) ":BIGTXTIDEX", 
                                    -1, (dvoid *) &myIndex, (sword) sizeof(sword), SQLT_INT, (dvoid *) 0,
                                    (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)))
    {
        checkerr(errhp, status);
        cleanup();
    }

    //strcpy((char *)myDate, "20160830");
    myIndex = iLoop;
    //strcpy((char *)myType, "testtype");
    //myLength = 10;
    //strcpy((char *)myTxt, "testtxt");
    //strcpy((char *)myState, "TEST");

    if ((status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 1, (ub4) 0,
                    (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
            && status != 1)
    {
        checkerr(errhp, status);
        cleanup();
    }

    //提交结果
    if ((status = OCITransCommit(svchp, errhp, 0)))
    {
        checkerr(errhp, status);
        cleanup();
    }

    if (stmthp)
    {
        checkerr(NULL, OCIHandleFree((dvoid *) stmthp, (ub4) OCI_HTYPE_STMT));
        stmthp = NULL;
    }
}

void myUpdate()
{
    //获取语句handle
    checkerr(errhp, OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &stmthp,
                OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0));

    //------------------修改------------------
    //使用修改字符串给会话句柄赋值
    checkerr(errhp, OCIStmtPrepare(stmthp, errhp, updateSQL,
                (ub4) strlen((char *) updateSQL),
                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));

    if ((status = OCIBindByName(stmthp, &bnd1p, errhp, (text *) ":1",
                    -1, (dvoid *) &myIndex, (sword) sizeof(sword), SQLT_INT, (dvoid *) 0,
                    (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)))
    {
        checkerr(errhp, status);
        cleanup();
    }

    myIndex = iLoop;

    if ((status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 1, (ub4) 0,
                    (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
            && status != 1)
    {
        checkerr(errhp, status);
        cleanup();
    }

    //提交结果
    if ((status = OCITransCommit(svchp, errhp, 0)))
    {
        checkerr(errhp, status);
        cleanup();
    }

    if (stmthp)
    {
        checkerr(NULL, OCIHandleFree((dvoid *) stmthp, (ub4) OCI_HTYPE_STMT));
        stmthp = NULL;
    }

}

void myDelete()
{
    //获取语句handle
    checkerr(errhp, OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &stmthp,
                OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0));

    //------------------删除------------------
    //使用修改字符串给会话句柄赋值
    checkerr(errhp, OCIStmtPrepare(stmthp, errhp, deleteSQL,
                (ub4) strlen((char *) deleteSQL),
                (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT));

    if ((status = OCIBindByName(stmthp, &bnd1p, errhp, (text *) ":1",
                    -1, (dvoid *) &myIndex, (sword) sizeof(sword), SQLT_INT, (dvoid *) 0,
                    (ub2 *) 0, (ub2 *) 0, (ub4) 0, (ub4 *) 0, OCI_DEFAULT)))
    {
        checkerr(errhp, status);
        cleanup();
    }

    myIndex = iLoop;

    if ((status = OCIStmtExecute(svchp, stmthp, errhp, (ub4) 1, (ub4) 0,
                    (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT))
            && status != 1)
    {
        checkerr(errhp, status);
        cleanup();
    }

    //提交结果
    if ((status = OCITransCommit(svchp, errhp, 0)))
    {
        checkerr(errhp, status);
        cleanup();
    }

    if (stmthp)
    {
        checkerr(NULL, OCIHandleFree((dvoid *) stmthp, (ub4) OCI_HTYPE_STMT));
        stmthp = NULL;
    }
}

int main(int argc, char *argv[])
{
    iLoop = argc > 1? atoi(argv[1]): 1; 
    myConnect();

    myDate = malloc(8+2);
    myType = malloc(8+2);
    myTxt = malloc(10+2);
    myState = malloc(4+2);

    for(; iLoop > 0; iLoop--)
    {
        //mySelect();
        //myInsert();
        //myUpdate();
        myDelete();
    }

    cleanup();
    return 0;
}


