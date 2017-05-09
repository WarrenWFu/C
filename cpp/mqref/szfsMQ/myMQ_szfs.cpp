/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmqc.h>
#include <cctype>
#include <string>

#include <api/include/mq.hpp>
#include <api/include/mqagent.hpp>
#include <util/include/cstring.hpp>

#include <MQAgent.hpp>
#include <base/membuffer.hpp>
#include <base/strHelper.hpp>

using namespace std;

#if 1
CMQAgent *pMQ = new CMQAgent();
vector<string> vMsgIDs;

int connectMQ()
{
    //根据需要修改IP和端口
    string QMName("MYQMGR");
    //根据需要修改IP和端口, 如果没有表示以服务端方式连接，就是这个QMGR在本地
    string MQConnStr("127.0.0.1(9905)");
    string MQConnCHL("MYQL_A");
    
    if (0 != pMQ->Connect(QMName.c_str(), MQConnStr.c_str(), MQConnCHL.c_str()))
    {
        printf("连接MQ失败\n");
        return -1;
    }

    return 0;
}

int writeMQ(const char *val1, const char *val2)
{
    // 读取文件作为写入MQ的信息
    MemBuffer mem;
    if (mem.loadFromFile(val1) < 0)
    {
        printf("加载文件信息失败\n");
        return -1;
    }

    char cStrMsgID[24+1] = {0};
    strcpy(cStrMsgID, "ReqFromTest");
    strcpy(&cStrMsgID[11], StrHelper::randomString(13).c_str());

    if (0 != pMQ->PutWithMsgId(val2, string(mem.getBuffer()), cStrMsgID))
    {
        printf("写入MQ失败, [%d]:[%s]\n", pMQ->GetErrCode(), pMQ->GetErrMsg());
        return -1;
    }
    //注意要commit
    pMQ->Commit();

    return 0;
}

int readMQ(const char *val1, string &strMsg)
{
    strMsg = "";
    if (0 != pMQ->GetMsg(val1, strMsg, 600))
    {
        printf("读取MQ失败, [%d]:[%s]\n", pMQ->GetErrCode(), pMQ->GetErrMsg());
        return -1;
    }
    //注意要commit
    pMQ->Commit();

    return 0;
}
#endif

int main()
{
    cout << "开始了" << endl;

    MQAgent mqAgent;
    mqAgent.Init("MYQMGR");

#if 1
    CString cstrA;
    BOOL boolA = -2;
    MQLONG mqlongA;

    //int iResA = mqAgent.GetMsg("MYQL_B", cstrA, boolA);
    //int iResA =mqAgent.GetFile("MYQL_B", cstrA);
    //mqAgent.Commit();

    FILE *fp = NULL;
    const char *pSzFilePath = "/home/spring/project/qhjk/product/Linux64/bin/625.xml";
    fp = fopen(pSzFilePath, "rb");
    if (!fp)
    {
        cout << "open failer errno[" << errno << "]" << endl;
        return 0;
    }

    char szBuf[3072 + 1] = {0};

    for (int i = 0; i < 10; i++)
    {
        memset(szBuf, 0x00, sizeof(3072+1));
        fread(szBuf, 1, 3072, fp);
        fseek(fp, 0, SEEK_SET);
        string str1(szBuf);
        str1 += szBuf;
        cout << str1.length() << endl;
        int iResC = mqAgent.PutMsg("MYQL_C", str1.c_str(), str1.length());
        mqAgent.Commit();

        if (iResC)
        {
            cout << iResC << endl;
            cout << mqAgent.GetErrorText().GetBuffer(0) << endl;
        }
    }
    fclose(fp);
#endif
    if (connectMQ())
        cout << "CMQ连接失败" << endl;

    if (writeMQ(pSzFilePath, "MYQL_C"))
        cout << "CMQ写入失败" << endl;

    string str1;
    if (readMQ("MYQL_C", str1))
        cout << "CMQ读取失败失败" << endl;
    else
        cout << "CMQ读取长度" << str1.length() << endl;
    

    return 0;
}

