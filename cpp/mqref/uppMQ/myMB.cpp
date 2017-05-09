/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:模拟前置读写MQ操作并生成回应
 * 使用方式:/mnt/winshared/it/cpp/tests/mqref/myFE 作为回应信息的文件 读取队列名 写入队列名 处理笔数
 *
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <string>

#include <MQAgent.hpp>
#include <base/membuffer.hpp>
#include <base/toolkit.hpp>
#include <base/strHelper.hpp>
#include <base/kvString.hpp>

using namespace std;

CMQAgent *pMQ = new CMQAgent();
KVString kvsMsgInfo;
vector<string> vMsgIDs;

int connectMQ()
{
    string QMName("QMU_UPPS_SVR");
    //根据需要修改IP和端口
    string MQConnStr("127.0.0.1(9905)");
    string MQConnCHL("U.UPPS.SVRCHL");
    
    if (0 != pMQ->Connect(QMName.c_str(), MQConnStr.c_str(), MQConnCHL.c_str()))
    {
        printf("连接MQ失败\n");
        return -1;
    }

    return 0;
}

//val1:队列名 val2:报文 val3:correlationID  val4:等待时间
int writeMQ(const char *val1, const char *val2, const char *val3, int val4)
{
    //暂时写死是8s延迟
    if (0 != pMQ->PutWithCorrelId(val1, val2, val3, val4))
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

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        printf("usage: myFE <readFromQ> <writeToQ> <count>\n");
        return -1;
    }

    int iRes = 0;
    iRes = connectMQ();
    if (iRes < 0)
    {
        printf("连接MQ失败\n");
        return -1;
    }

    //ThreadPool* threadPool(argv[4]);

    string strMsg;
    MemBuffer mem;
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

        //要做的只是获取这笔报文的MsgID作为CorrelationID发回去,等待时间先写死为8s
        char strBuf[30] = {0};
        Toolkit::hex2bin(kvsMsgInfo.getString("MsgIdHex"), strBuf, 30, false);
        iRes = writeMQ(argv[3], mem.getBuffer(), strBuf, 8);
        if (iRes < 0)
        {
            printf("写入MQ失败\n");
            sleep(5000);
            continue;
        }
        //printf("处理[%d]笔\n", i);
    }

    return 0;
}

