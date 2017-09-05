/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstring>
#include <base/toolkit.hpp>
#include <base/membuffer.hpp>
#include <log/logger.hpp>
#include <sys/types.h>
#include <unistd.h>
#include <webservicepublic.hpp>

using namespace std;
using namespace aps;

void PrintHex(unsigned char *str, unsigned int len)  
{  
    int i = 0;  
    for(i =0;i < (int)len; i++)  
    {  
        if(i%4 == 0)  
    {  
       printf("0x");  
    }  
        printf("%02x",str[i]);  
    if(i%4 == 3)  
        {  
           printf(" ");  
        }  
        if(i%16 == 15)  
        {  
        printf("\n");  
        }  
    }  
    printf("\n");  
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("usage: en 要加密加签的报文文件 加密的公钥文件 加签的私钥文件\n");
        return 0;
    }

    //LogManager::init(Z_DEFAULT_LOGDRIVER_NAME, "./test.xml");
    MemBuffer mem;

    mem.loadFromFile(argv[1]);

    string strMsg((char *)mem.getRawBuffer());
    char cTail = ((char *)mem.getRawBuffer())[mem.size()-1];
    char cTailSec = ((char *)mem.getRawBuffer())[mem.size()-2];
    if (cTail != 0x0a && cTail != 0x0d)
    {
        //do nothing
    }
    else if ((cTailSec == 0x0d && cTail == 0x0a) || cTail == 0x0d)
    {
        for (size_t iPos = 0; (iPos = strMsg.rfind(0x0d)) != string::npos && 
                (iPos == strMsg.length()-1 || (iPos == strMsg.length() - 2 && strMsg.at(iPos+1) == 0x0a));)
            strMsg.erase(iPos);
    }
    else
    {
        for (size_t iPos = 0; (iPos = strMsg.rfind(0x0a)) != string::npos &&
                iPos == strMsg.length()-1;)
            strMsg.erase(iPos);
    }

    //组成签名串
    int iTagBegin = 0;
    int iTagEnd   = 0;

    string strForChkSig;
    iTagBegin = strMsg.find("<gatewayversion>") + strlen("<gatewayversion>");
    iTagEnd   = strMsg.find("</gatewayversion>");
    strForChkSig = "gatewayversion=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    iTagBegin = strMsg.find("<msgbody>") + strlen("<msgbody>");
    iTagEnd   = strMsg.find("</msgbody>");
    strForChkSig += "&msgbody=";
    //strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    string strMsgBody(strMsg.substr(iTagBegin, iTagEnd-iTagBegin));

    iTagBegin = strMsg.find("<msgno>") + strlen("<msgno>");
    iTagEnd   = strMsg.find("</msgno>");
    strForChkSig += "&msgno=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    iTagBegin = strMsg.find("<msgtype>") + strlen("<msgtype>");
    iTagEnd   = strMsg.find("</msgtype>");
    strForChkSig += "&msgtype=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    iTagBegin = strMsg.find("<resptype>") + strlen("<resptype>");
    iTagEnd   = strMsg.find("</resptype>");
    strForChkSig += "&resptype=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    if (strMsg.find("<respurl>") != string::npos)
    {
    iTagBegin = strMsg.find("<respurl>") + strlen("<respurl>");
    iTagEnd   = strMsg.find("</respurl>");
        strForChkSig += "&respurl=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    }
    if (strMsg.find("<returnencrypt>") != string::npos)
    {
    iTagBegin = strMsg.find("<returnencrypt>") + strlen("<returnencrypt>");
    iTagEnd   = strMsg.find("</returnencrypt>");
        strForChkSig += "&returnencrypt=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    }
    iTagBegin = strMsg.find("<sendtime>") + strlen("<sendtime>");
    iTagEnd   = strMsg.find("</sendtime>");
    strForChkSig += "&sendtime=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    iTagBegin = strMsg.find("<subnode>") + strlen("<subnode>");
    iTagEnd   = strMsg.find("</subnode>");
    strForChkSig += "&subnode=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    iTagBegin = strMsg.find("<version>") + strlen("<version>");
    iTagEnd   = strMsg.find("</version>");
    strForChkSig += "&version=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);
    iTagBegin = strMsg.find("<ziptype>") + strlen("<ziptype>");
    iTagEnd   = strMsg.find("</ziptype>");
    strForChkSig += "&ziptype=";
    strForChkSig += strMsg.substr(iTagBegin, iTagEnd-iTagBegin);

    RSAEncrypter::initEncrypter();
    RSAEncrypter rsaEnc;
    if (rsaEnc.getPublicKey(argv[2]))
        cout << "获取公钥失败" << endl;

    if (rsaEnc.getPrivateKey(argv[3], "123456"))
        cout << "获取私钥失败" << endl;

    string strEnced = rsaEnc.rsaEncrypt(strMsgBody.c_str(), strMsgBody.length());
    //cout << ((strMsgBody == rsaEnc.rsaDecrypt(strEnced.c_str(), strEnced.length()))? "相等": "不等") << endl;

    //将加密后的报文放入待签名串
    iTagBegin = strForChkSig.find("&msgbody=") + strlen("&msgbody=");
    string strTmpA(strForChkSig.substr(0, iTagBegin));
    strTmpA += strEnced;
    string strTmpB(strForChkSig.substr(iTagBegin));
    strTmpA += strTmpB;

    //cout << strTmpA << endl;

    string strSignHex = rsaEnc.rsaSign(strTmpA.c_str(), strTmpA.length());
    //cout << strSignHex << endl;

    //if (rsaEnc.rsaVerify(strTmpA.c_str(), strTmpA.length(), strSignHex))
    //    cout << "失败" << endl;
    //else
    //    cout << "成功" << endl;

    //新报文体写入
    iTagBegin = strMsg.find("<msgbody>") + strlen("<msgbody>");
    iTagEnd   = strMsg.find("</msgbody>");
    strTmpA = strMsg.substr(0, iTagBegin);
    strTmpA += strEnced;
    strTmpB = strMsg.substr(iTagEnd);
    strTmpA += strTmpB;

    //cout << strTmpA << endl;

    //签名放入报文体
    iTagBegin = strTmpA.find("<signature>") + strlen("<signature>");
    iTagEnd   = strTmpA.find("</signature>");
    string strTmpC(strTmpA.substr(0, iTagBegin));
    strTmpB = strTmpA.substr(iTagEnd);
    strTmpC += strSignHex;
    strTmpC += strTmpB;

    cout << strTmpC << endl;
    RSAEncrypter::releaseEncrypter();

    return 0;
}

