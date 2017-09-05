/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:模拟前置读写MQ操作并生成回应
 * 使用方式:myFE 作为回应信息的文件 读取队列名 写入队列名 处理笔数 QMGR|连接串|通道名 
 *
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <string>
#include <unistd.h>

#include <MQAgent.hpp>
#include <base/membuffer.hpp>
#include <base/toolkit.hpp>
#include <base/strHelper.hpp>
#include <base/kvString.hpp>

using namespace std;

CMQAgent *pMQ = new CMQAgent();
KVString kvsMsgInfo;
vector<string> vMsgIDs;
MemBuffer mem;
string g_str302TxId;
long g_l302Amt;
string g_strMQ;

int connectMQ()
{
    int iPosTmpA = g_strMQ.find('|');
    int iPosTmpB = g_strMQ.rfind('|');
    string strQMName;
    strQMName.assign(g_strMQ, 0, iPosTmpA);
    string strMQConnStr;
    strMQConnStr.assign(g_strMQ, iPosTmpA+1, iPosTmpB-iPosTmpA-1);
    string strMQConnCHL;
    strMQConnCHL.assign(g_strMQ, iPosTmpB+1, g_strMQ.length()-iPosTmpB-1);
    
    if (0 != pMQ->Connect(strQMName.c_str(), strMQConnStr.c_str(), strMQConnCHL.c_str()))
    {
        printf("连接MQ失败\n");
        return -1;
    }

    return 0;
}

//val1:队列名
int writeMQ(const char *val1)
{
    //写入之前修改字段
    char *pSz = mem.getBuffer();
    char *pTxtId = strstr(pSz, "<TxId>");
    long lTxtId = atol(string(pTxtId+6, 8).c_str());
    lTxtId++;
    if (lTxtId == 99999990)
        lTxtId = 0;
    char szTxtId[8+1] = {0};
    sprintf(szTxtId, "%08ld", lTxtId);
    memcpy(pTxtId+6, szTxtId, sizeof(szTxtId)-1);

    char *pOrgnlMsgIdA = strstr(pSz, "<OrgnlMsgId>");
    //char *pOrgnlMsgIdB = strstr(pSz, "</OrgnlMsgId>");
    memcpy(pOrgnlMsgIdA+12, g_str302TxId.c_str(), g_str302TxId.length());

    printf("发送的报文[%s]", pSz);

    //暂时写死是8s延迟
    if (0 != pMQ->PutMsg(val1, pSz, 8))
    {
        printf("写入MQ失败, [%d]:[%s]\n", pMQ->GetErrCode(), pMQ->GetErrMsg());
        return -1;
    }
    //注意要commit
    pMQ->Commit();

    //printf("写入完成\n");
    return 0;
}

int readMQ(const char *val1, string &val2)
{
    if (0 != pMQ->GetMsg(val1, val2, 600, &kvsMsgInfo))
    {
        printf("读取MQ失败, [%d]:[%s]\n", pMQ->GetErrCode(), pMQ->GetErrMsg());
        return -1;
    }
    //printf("读取到的信息[%s]n", val2.c_str());
    //注意要commit
    pMQ->Commit();

    //获取原报文中的
    int iTmpA = val2.find("<Amt>");
    int iTmpB = val2.find("</Amt>");

    g_l302Amt = atol(string(val2, iTmpA+5, iTmpB - iTmpA -5).c_str());

    iTmpA = val2.find("<TxId>");
    iTmpB = val2.find("</TxId>");
    g_str302TxId = string(val2, iTmpA+6, iTmpB - iTmpA - 6);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        printf("usage: myFE <rspfile> <readFromQ> <writeToQ> <count> <QMGR|ConnStr|Channel>\n");
        return -1;
    }

    int iRes = 0;
    g_strMQ = argv[5];
    iRes = connectMQ();
    if (iRes < 0)
    {
        printf("连接MQ失败\n");
        return -1;
    }

    //ThreadPool* threadPool(argv[4]);

    string strMsg;
    if (mem.loadFromFile(argv[1]) < 0)
    {
        printf("加载文件信息失败\n");
        return -1;
    }

    for (int i = 0; i < atoi(argv[4]); i++)
    {
        strMsg = "";
        iRes = readMQ(argv[2], strMsg);
        if (iRes < 0)
        {
            printf("读取MQ失败\n");
            sleep(5000);
            continue;
        }

        iRes = writeMQ(argv[3]);
        if (iRes < 0)
        {
            printf("写入MQ失败\n");
            sleep(5000);
            continue;
        }
        printf("处理[%d]笔\n", i+1);
    }

    mem.saveToFile(argv[1]);

    return 0;
}

