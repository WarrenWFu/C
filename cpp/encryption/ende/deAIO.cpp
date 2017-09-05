/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pkcs12.h>

using namespace std;

namespace
{
    EVP_PKEY *m_priKey;
    int RSA_KEY_LENGTH = 256;
}

bool hex2bin(const string& inHexStr, void*outBuffer, unsigned int bufferLen, bool bZeroTail = false)
{
    if (inHexStr.length() % 2 !=0)
        return false;

    unsigned char charVal;
    char szBuffer[3] = {0,0,0};
    unsigned char *pBuffer = (unsigned char *)outBuffer;

    size_t i=0;
    for (; i<inHexStr.length()/2 && i<bufferLen; i++)
    {
        charVal = 0;
        memcpy(szBuffer, inHexStr.c_str() + i*2, 2);

        if (szBuffer[0] >= '0' && szBuffer[0] <= '9')
            charVal = szBuffer[0] - '0';
        else if (szBuffer[0] >= 'A' && szBuffer[0] <= 'F')
            charVal = szBuffer[0] - 'A' + 10;
        else
            charVal = szBuffer[0] - 'a' + 10;

        charVal *= 16;

        if (szBuffer[1] >= '0' && szBuffer[1] <= '9')
            charVal += szBuffer[1] - '0';
        else if (szBuffer[1] >= 'A' && szBuffer[1] <= 'F')
            charVal += szBuffer[1] - 'A' + 10;
        else
            charVal += szBuffer[1] - 'a' + 10;

        pBuffer[i] = charVal;
    }

    if (bZeroTail && i<bufferLen)
        pBuffer[i] = '\0';

    return true;
}

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

int loadFromFile(const string &filePath, char *pBuffer)
{
    FILE *fp = NULL;
    fp = fopen(filePath.c_str(), "rb");
    if (NULL==fp)
        return -1;

    fseek(fp, 0, SEEK_END);
    size_t fileSize = ftell(fp);

    size_t toReadSize = fileSize;

    size_t leftBytes = toReadSize;
    int perReadBytes = 0;
    int perReadedBytes = 0;

    fseek(fp, 0, SEEK_SET);
    int nOff_ = 0;
    for(; leftBytes>0;)
    {
        if (leftBytes<1024)
            perReadBytes = leftBytes;
        else
            perReadBytes = 1024;
        perReadedBytes = fread(pBuffer+(toReadSize-leftBytes), 1, perReadBytes, fp );
        leftBytes -= perReadedBytes;
        nOff_ += perReadedBytes;
    }
    fclose(fp);
    pBuffer[nOff_] = '\0';
    return toReadSize;
}

int getPrivateKey(const string &strPath, const string &strPWD)
{
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    FILE *fp;
    PKCS12 *p12;

    if ((fp = fopen(strPath.c_str(), "rb")) == NULL)
    {
        printf("打开私钥文件失败\n");
        return -1;
    }
    p12 = d2i_PKCS12_fp(fp, NULL);
    fclose(fp);

    if (!p12)
    {
        printf("解析私钥文件失败\n");
        return -1;
    }

    if (!PKCS12_parse(p12, strPWD.c_str(), &m_priKey, NULL, NULL))
    {
        printf("获取私钥失败\n");
        PKCS12_free(p12);
        return -1;
    }
    PKCS12_free(p12);

    return 0;
}

string rsaDecrypt(const char* szToDecry, int iLen)
{
    if (!m_priKey)
    {
        printf("未设置私钥，解密失败\n");
        return "";
    }

    if (szToDecry  == NULL)
    {
        printf("待加密字符串为空\n");
        return "";
    }

    if (iLen % RSA_KEY_LENGTH*2 != 0)
    {
        printf("加密报文长度错误，验密失败\n");
        return "";
    }

    RSA *rsa = EVP_PKEY_get1_RSA(m_priKey);
    if (!rsa)
    {
        printf("获取RSA失败, 原因[%s]\n", 
                ERR_reason_error_string(ERR_get_error()));

        return NULL;
    }

    char szBuf[256 + 1] = {0};
    char szBinBuf[256 + 1] = {0};
    string strDeced;

    int iLenTmp = RSA_KEY_LENGTH * 2;
    for (int i = 0; i < iLen/(RSA_KEY_LENGTH*2); i++)
    {
        memset(szBinBuf, 0x00, sizeof(szBinBuf));
        memset(szBuf, 0x00, sizeof(szBuf));

        string strTmp(szToDecry + iLenTmp * i, iLenTmp);

        hex2bin(strTmp, szBinBuf, iLenTmp);

        if(RSA_private_decrypt(RSA_KEY_LENGTH, (unsigned char *)szBinBuf, 
                    (unsigned char*)szBuf, rsa, RSA_PKCS1_PADDING) < 0)
        {
            printf("RSA验密失败, 原因[%s]\n", 
                    ERR_reason_error_string(ERR_get_error()));

            return "";
        }
        strDeced += szBuf;
    }

    return strDeced;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("usage: deAIO 要解密的报文文件 解密的私钥文件 秘钥密码\n");
        return 0;
    }

    char szBuffer[4096+1] = {0};
    if (loadFromFile(argv[1], szBuffer) < 0)
    {
        printf("载入报文文件失败\n");

        return -1;
    }

    string strMsg(szBuffer);
    char cTail = strMsg.at(strMsg.length() - 1);
    char cTailSec = strMsg.at(strMsg.length() - 2);
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

    if (getPrivateKey(argv[2], argv[3]))
        return -1;

    string strPlainMsg(rsaDecrypt(strMsg.c_str(), strMsg.length()));
    cout << "[" << (strPlainMsg.empty()? "解密失败": strPlainMsg) << "]" << endl;

    EVP_PKEY_free(m_priKey);

    return 0;
}

