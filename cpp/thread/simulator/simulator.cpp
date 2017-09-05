/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:通过多线程模拟多个客户端连接发送业务报文，并同步等待回应
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <base/thread.hpp>
#include <base/membuffer.hpp>
#include <base/tcpSocket.hpp>
#include <sys/time.h>

using namespace std;
using namespace aps;

MemBuffer mem;
string g_strIp;
int    g_iPort;
Mutex  g_mtx;
long   g_lJYBSH;
string g_strJYLSHHead;
long   g_lJYLSHSeq;
int    g_iTimeout;
int    g_lSendTimes;
long   g_lCount;

struct Args
{
    long lNum1;
    long lNum2;
    long lNum3;
};

void getTime(long& lSecond, long& lUSecond, int& iYear, int& iMonth, int& iDay, 
int& iHour, int& iMinite, int& iSecond, int& iMiSecond)
{
    #define BEIJINGTIME 8;
	struct timeval tv;
	struct timezone tz;
	long sec = 0, usec = 0;
	int yy = 0, mm = 0, dd = 0, hh = 0, mi = 0, ss = 0, ms =0;
	int m[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i;
	gettimeofday(&tv, &tz);
	sec = tv.tv_sec;
	sec = sec + 60*60*BEIJINGTIME;
    lSecond = sec;
	usec = tv.tv_usec;
    lUSecond = usec;
	//年
	yy = sec/(60*60*24*(365*4+1)/4) + 1970;
	//日
	dd = sec/(60*60*24) - ((yy - 1970)*365 + (yy - 1968)/4);
	//月
	if(0 == yy%1000)
	{
		if(0 == (yy/1000)%4)
		{
			m[1] = 29;
		}
	}
	else
	{
		if(0 == yy%4)
		{
			m[1] = 29;
		}
	}
	for(i = 1; i <= 12; i++)
	{
		if(dd - m[i] < 0)
		{
			break;
		}
		else
		{
			dd = dd -m[i];
		}
	}
	mm = i;
	//小时
	hh = sec/(60*60)%24;
	//分
	mi = sec/60 - sec/(60*60)*60;
	//秒
	ss = sec - sec/60*60;
	ms = usec;
	//printf("%d-%02d-%02d %02d:%02d:%02d.%06d\n", yy, mm, dd, hh, mi, ss, ms);
	iYear = yy;
	iMonth = mm;
	iDay = dd;
	iHour = hh;
	iMinite = mi;
	iSecond = ss;
	iMiSecond = ms;
}

void putReq(void *ptr)
{
    Args *pArgs = (struct Args*) ptr;

    char *pSz = new char[mem.size()+1];
    memcpy(pSz, mem.getBuffer(), mem.size());
    long lJYBSHBegin = pArgs->lNum1;
    long lJYLSHBegin = pArgs->lNum2;
    long lSendTimes  = pArgs->lNum3;

    delete pArgs;

    char szJYBSH[10+1] = {0};
    char szJYLSH[24+1] = {0};
    char szLength[10+1] = {0};
    int iReadedBytes = 0;
    int iMsgLen = 0;
    char *pMsg = NULL;
    long tBegin = 0L;
    long tsBegin = 0L;
    long tEnd = 0L;
    long tsEnd = 0L;
    int iYear; int iMonth; int iDay;
    int iHour; int iMinite; int iSecond; int iMiSecond;

    for (int i = 0; i < lSendTimes; i ++)
    {
        memset(szJYBSH, 0x00, sizeof(szJYBSH));
        memset(szJYLSH, 0x00, sizeof(szJYLSH));

        //修改交易标识号
        sprintf(szJYBSH, "%010ld", lJYBSHBegin+i);
        memcpy(pSz+66, szJYBSH, 10);
        {
            Mutex::ScopedLock scope(g_mtx);
            g_lCount++;
            printf("%d: 发送了%ld\n", __LINE__, g_lCount-1);
        }

        //修改交易流水号
        sprintf(szJYLSH, "%s%08ld", g_strJYLSHHead.c_str(), lJYLSHBegin+i);
        memcpy(pSz+254, szJYLSH, 24);

        getTime(tBegin, tsBegin, iYear, iMonth, iDay, iHour, iMinite, iSecond, iMiSecond);
        printf("[%s]发送的时间[%d:%d:%d.%d]\n", szJYBSH, iHour, iMinite, iSecond, iMiSecond);

        TcpSocket tcpsocket;
        tcpsocket.setBlock(false);
        if (!tcpsocket.connect(g_strIp, g_iPort))
        {
            printf("%d:连接失败\n", __LINE__);
            sleep(1);
            continue;
        }

        if (!tcpsocket.send(pSz, mem.size()))
        {
            printf("%d:发送消息失败", __LINE__);
            sleep(1);
            tcpsocket.close(); 
            continue;
        }
#if 1
        //接收同步回应
        memset(szLength, 0x00, sizeof(szLength));
        tcpsocket.recv(szLength, 10, &iReadedBytes, g_iTimeout*1000);
        if (iReadedBytes != 10)
        {
            printf("%d:读取长度失败，读到的字节数为[%d]\n", __LINE__, iReadedBytes);
            sleep(1);
            tcpsocket.close(); 
            continue;
        }

        iMsgLen = atoi(szLength);
        if (iMsgLen == 0)
        {
            printf("%d:读取长度失败，读到的信息为[%s]\n", __LINE__, szLength);
            tcpsocket.close(); 
            continue;
        }

        pMsg = new char[iMsgLen + 1];
        memset(pMsg, 0x00, iMsgLen + 1);
        tcpsocket.recv(pMsg, iMsgLen, &iReadedBytes, g_iTimeout*1000);
        if (iReadedBytes != iMsgLen)
        {
            printf("%d:读取到的报文长度小于报文指定的长度[%d]\n", __LINE__, iMsgLen);
            delete []pMsg;
            sleep(1);
            tcpsocket.close(); 
            continue;
        }
        //printf("%d: 收到报文[%s%s]\n", __LINE__, szLength, pMsg);
        getTime(tEnd, tsEnd, iYear, iMonth, iDay, iHour, iMinite, iSecond, iMiSecond);
        printf("[%s]接收的时间[%d:%d:%d.%d]\n", szJYBSH, iHour, iMinite, iSecond, iMiSecond);

        long tsDiff = tsEnd - tsBegin;
        long tDiff = tEnd - tBegin;
        if (tsDiff < 0)
        {
            tDiff -= 1;
            tsDiff += 1000000;
        }
        printf("[%s]消耗的时间[%ld.%06ld]\n", szJYBSH, tDiff, tsDiff);

        delete pMsg;
#endif

        tcpsocket.close();
    }

    delete []pSz;

}

int main(int argc, char *argv[])
{
    int iThdNum = 0;
    if (argc < 2)
    {
        printf("usage: simulator reqmsgfile [threadnum] [ip] \
                [port] [timeout] [sendtimes]\n");
        return -1;
    }

    if (argc > 6)
    {
        iThdNum = atoi(argv[2]);
        g_strIp = argv[3];
        g_iPort = atoi(argv[4]);
        if (g_iPort == 0)
            g_iPort = 5299;
        g_iTimeout = atoi(argv[5]);
        g_lSendTimes = atol(argv[6]);
    }
    else
    {
        iThdNum = 10;
        g_strIp = "127.0.0.1";
        g_iPort = 5299;
        g_iTimeout = 5;
        g_lSendTimes = 10;
    }
    printf("%d:线程数[%d]\n", __LINE__, iThdNum); 

    // 读取文件作为写入MQ的信息
    if (mem.loadFromFile(argv[1]) < 0)
    {
        printf("%d:加载文件信息失败\n", __LINE__);
        return -1;
    }

    g_lJYBSH = atol(string(mem.getBuffer()+66, 10).c_str());
    g_strJYLSHHead = string(mem.getBuffer()+254, 16);
    g_lJYLSHSeq = atol(string(mem.getBuffer()+254+16, 8).c_str());

    ThreadPool threadPool(iThdNum);
    for (int i = 0; i < iThdNum; i++)
    {
        Args *pArgs = new Args();
        //每个线程的发送次数
        pArgs->lNum3 = g_lSendTimes/iThdNum;
        pArgs->lNum1 = (g_lJYBSH += pArgs->lNum3);
        pArgs->lNum2 = (g_lJYLSHSeq += pArgs->lNum3);

        threadPool.dispatch(putReq, pArgs);
    }

    //将信息保存会文件
    char szJYBSH[10+1] = {0};
    sprintf(szJYBSH, "%010ld", g_lJYBSH);
    char *pSz = mem.getBuffer();
    memcpy(pSz+66, szJYBSH, 10);

    char szJYLSH[24+1] = {0};
    sprintf(szJYLSH, "%s%08ld", g_strJYLSHHead.c_str(), g_lJYLSHSeq);
    memcpy(pSz+254, szJYLSH, 24);

    mem.saveToFile(argv[1]);

    while(true)
    {
        Thread::sleep((g_lSendTimes/iThdNum) * g_iTimeout *1000);
        if (threadPool.activeCount() == 0)
            break;
    }

    threadPool.stop();
    threadPool.wait();

    return 0;
}

