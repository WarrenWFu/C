/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:读写MQ操作
 * 使用方式:./myMQ -w ~/tmp/singlepay.txt 1 MYQL_A "MYQMGR|127.0.0.1(9905)|MYMQCHANNEL"
 *          ./myMQ -r ~/tmp/singlepay.txt 1 MYQL_B "MYQMGR|127.0.0.1(9905)|MYMQCHANNEL"
 *          
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
#include <base/strHelper.hpp>

using namespace std;

CMQAgent *pMQ = new CMQAgent();
vector<string> vMsgIDs;
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

int writeMQ(const char* val1, int val2, const char* val3)
{
    if (0 == strcmp(val1, "null"))
    {
        printf("can't read from null\n");
        return (-1);
    }

    //执行脚本使用TradID自增1
    //string strCmd = "./changeSeq.sh " + string(val1);
    //system(strCmd.c_str());

    // 读取文件作为写入MQ的信息
    MemBuffer mem;
    if (mem.loadFromFile(val1) < 0)
    {
        printf("加载文件信息失败\n");
        return -1;
    }

    char cStrMsgID[24+1] = {0};
    strcpy(cStrMsgID, "ReqFromTest");
    int iCount2 = 0;
    char *pStr = strstr(mem.getBuffer(), "TRADID");
    char *pStr1 = strstr(mem.getBuffer(), "BSID");
    char *pStr2 = strstr(mem.getBuffer(), "TxtId");
    if (!pStr2)
        pStr2 = strstr(mem.getBuffer(), "txtid");

    int iSeq = 0;
    int iSeq1 = 0;
    int iSeq2 = 0;
    char cRestore[8+1] = {0};
    if (pStr)
    {
        string sSeq(pStr+19, 8);
        iSeq = atoi(sSeq.c_str());
    }

    if (pStr1)
    {
        string sSeq1(pStr1+21, 8);
        iSeq1 = atoi(sSeq1.c_str());
    }

    if (pStr2)
    {
        string sSeq2(pStr2+14, 8);
        iSeq2 = atoi(sSeq2.c_str());
    }

    while (val2 > 0)
    {
        strcpy(&cStrMsgID[11], StrHelper::randomString(13).c_str());
        vMsgIDs.push_back(string(cStrMsgID));
        //修改报文中的TradID
        if (pStr)
        {
            iSeq ++;
            sprintf(cRestore, "%08d", iSeq);
            memcpy(pStr+19, cRestore, 8);
        }
        //修改报文中的BSID
        if (pStr1)
        {
            iSeq1 ++;
            sprintf(cRestore, "%08d", iSeq1);
            memcpy(pStr1+21, cRestore, 8);
        }
        //修改报文中的TxtID
        if (pStr2)
        {
            iSeq2 ++;
            sprintf(cRestore, "%08d", iSeq2);
            memcpy(pStr2+14, cRestore, 8);
        }

        if (0 != pMQ->PutWithMsgId(val3, string(mem.getBuffer()), cStrMsgID))
        {
            printf("写入MQ失败, [%d]:[%s]\n", pMQ->GetErrCode(), pMQ->GetErrMsg());
            return -1;
        }
        //注意要commit
        pMQ->Commit();


        val2 --;
        iCount2 ++;

        printf("写入[%d]笔\n", iCount2);
    }

    if (mem.saveToFile(val1, false) < 0)
    {
        printf("保存文件信息失败\n");
        return -1;
    }

    printf("写入完成\n");
    return 0;
}

int readMQ(int val1, const char *val2)
{
    //char cStrMsgID[24+1] = {0};
    //strcpy(cStrMsgID, "ReqFromTest");
    int iCount2 = 0;
    string strMsg;
    while (val1 > 0)
    {
        strMsg = "";
        if (0 != pMQ->GetMsg(val2, strMsg, 600))
        {
            printf("读取MQ失败, [%d]:[%s]\n", pMQ->GetErrCode(), pMQ->GetErrMsg());
            return -1;
        }
        //printf("读取到的信息[%s]n", strMsg.c_str());
        //注意要commit
        pMQ->Commit();

        val1 --;
        iCount2 ++;

        printf("读取[%d]笔\n", iCount2);
        printf("读取到得信息[%s]\n", strMsg.c_str());
    }

    printf("读取完成\n");
    return 0;
}


int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        printf("usage: myMQ <-w|-r|-a> <filename|null> <count> <queuename> <QMGR|MQConnStr|MQChannel>\n");
        return -1;
    }

    int iCount = 0;
    if (argc >= 6)
    {
        for (int i = 0; i < (int)strlen(argv[3]); i++)
        {
            if (argv[3][i] < 48 || argv[3][i] > 57)
            {
                printf("The count parameter is not a number\n");
                return -1;
            }
        }
        iCount = atoi(argv[3]);
        g_strMQ = argv[5];
    }

    int iRes = 0;
    if (0 == strcmp(argv[1], "-w"))
    {
        iRes = connectMQ();
        if (iRes < 0)
        {
            printf("连接MQ失败\n");
            return -1;
        }
        iRes = writeMQ(argv[2], iCount, argv[4]);
        if (iRes < 0)
            printf("写入MQ失败\n");
    }
    else if (0 == strcmp(argv[1], "-a"))
    {
        //TODO
    }
    else if (0 == strcmp(argv[1], "-r"))
    {
        iRes = connectMQ();
        if (iRes < 0)
        {
            printf("连接MQ失败\n");
            return -1;
        }
        iRes = readMQ(iCount, argv[4]);
        if (iRes < 0)
            printf("读取MQ失败\n");
    }
    else
    {
        printf("the second parameter must be -r or -w\n");
        return -1;
    }



    return 0;
}

