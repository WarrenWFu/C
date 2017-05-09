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
    if (argc < 3)
    {
        printf("usage: de 要解密的报文文件 解密的私钥文件\n");
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

    RSAEncrypter::initEncrypter();
    RSAEncrypter rsaEnc;
    if (rsaEnc.getPrivateKey(argv[2], "123456"))
        cout << "获取私钥失败" << endl;

    string strPlainMsg(rsaEnc.rsaDecrypt(strMsg.c_str(), strMsg.length()));
    cout << "[" << (strPlainMsg.empty()? "解密失败": strPlainMsg) << "]" << endl;

    RSAEncrypter::releaseEncrypter();

    return 0;
}

