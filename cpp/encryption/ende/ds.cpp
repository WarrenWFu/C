/**
 * @file        
 * @brief       用于测试验签，参数1的文件中为签名，长串字符串为加密后的报文
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/
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
        printf("usage: ds 要验签的报文文件 验签的公钥文件\n");
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

    RSAEncrypter *pRSA = new RSAEncrypter();
    if (pRSA->getPublicKey(argv[2]))
    {
        cout << "获取公钥失败" << endl;
        return -1;
    }

    string strForChkSig;
    strForChkSig = "gatewayversion=1";
    strForChkSig += "&msgbody=";
    strForChkSig += "5a8388319b1595f5c0475d0740bb6ebb6d442f7a34699efa160ae69ecb91348c83930e9740a709d4a83657ba5aa76b76697dc0d07f96935e018dae26ea80930d89a306065afd8d47dc7cea2b2df585266d45cca99728ff88e43a2e56260422251164ec80990fd8f45d6037d1f31e980972a7f0794393b404d31a696426265e23da46fe128173d1b00dcc7ec9da39c97fb7f7ad50756076401e8393eb5edfe9251d4fe1cdf002dc4001ee0dfcd73d7816faab7d2ec999914e64d049345ee04b67d8f741ba9b3f14a6b120656966e338829f9d5781c23fa5fdea9ae6a352153e5e6b760dc2d5c319b4304a5e79abf1ad6a3edc9da06bd5a013c2d0621ece4824c90c1755a2d3ebc16d215f3eaa9604e992c222eddd43815a63a49d01af3694b199523a131f483885113d5b4e9ea43362e4ba5ba036737584119a386e0c4adbc48f96bffff43df2a85a2968baeccfe5f5b4a1901e90ad510e6f28e449aca75bb4637afeefeb5d0f12cd562849ae0d8ed059cfd130f2b99f00f0a370d45248ba2b9d0ad9096f8857085b46761f50fd0681d0c40db44ad2933c4c9eb64c7305a38cd2cf6ed1f2668dde535b3a577306e2f0d08439351590c65a7f8cf1320a00297630fc880710d14b2dcc82ab174521d3fe4151eff06e8c665cedecdabc1d0469500ed29580ffceee9d66f8fac5f3e588286203ab2370734f5071ea493d2af7662c410bc2fe29020080e661a2de6f010b440e7482c809783e268b322685bec2311a074df7cf7a0ffcbe5634738e0beaa476fd76857364142690c5d9695a318d87607ccb92715bc883ef085ed1a945fab53076d05f785711ac2ea56e4ccdcf31f17a8da916e075abf827fc697be3f6075101cae59b077465c274495aa49052781abc2fafa3efdfd1b87b980ebb6bdae0b5ead645c3a4331f4646290b5b10405e31b5f2a69130be75972f662af4919a9e952337a79e993b63a4a07fc841dd99fb523b3cc3b02ee0a3c4bad1f032f43be5746cd0d75ddb2b36cef6e6d4c11ed46aec584562d2c5d6cbaa4d8bfb7ba1ae6f8713c8a4ce97adffb7c080eaf2174252353306";
    strForChkSig += "&msgno=1004";
    strForChkSig += "&msgtype=SINGLEPAY";
    strForChkSig += "&resptype=1";
    strForChkSig += "&returnencrypt=1";
    strForChkSig += "&sendtime=20170309131800";
    strForChkSig += "&subnode=A09700000001";
    strForChkSig += "&version=1";
    strForChkSig += "&ziptype=0";

    if (pRSA->rsaVerify(strForChkSig.c_str(), strForChkSig.length(), 
                strMsg))
    {
        cout << "验签失败" << endl;
        delete pRSA;
        return -1;
    }
    cout << "验签成功" << endl;

    return 0;
}

