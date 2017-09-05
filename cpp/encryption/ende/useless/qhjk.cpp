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
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <openssl/x509.h>
#include <openssl/engine.h>
#include <openssl/conf.h>
#include <sys/types.h>
#include <unistd.h>

namespace
{
    const int RSA_KEY_LENGTH = 256;
}

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

//载入公钥
RSA *getPublicKey(const string &strPath)
{
    FILE *fp = fopen(strPath.c_str(), "rb") ;  
    if(!fp) 
    {
        ULog(eERROR, "打开证书文件失败，请检查证书[%s]是否存在", strPath.c_str());
        return NULL;
    }
    unsigned char szFileBuf[2048 + 1] = {0};
    unsigned int iLen = fread(szFileBuf, 1, 2048, fp);  
    fclose(fp);  

    X509 *x509 = X509_new();
    unsigned char* pBuf = szFileBuf;

    if (!d2i_X509(&x509, (const unsigned char **)&pBuf, iLen))
    {
        ULog(eERROR, "解析公钥文件失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        X509_free(x509);   
        return NULL;
    }

    EVP_PKEY *evpPKey = X509_get_pubkey(x509);
    if (!evpPKey)
    {
        ULog(eERROR, "获取公钥失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        X509_free(x509);   
        return NULL;
    }

    RSA *rsa = EVP_PKEY_get1_RSA(evpPKey);
    if (!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        EVP_PKEY_free(evpPKey);
        X509_free(x509);   
        return NULL;
    }

    //EVP_PKEY_free(evpPKey);
    //X509_free(x509);   

    return rsa;
}

//载入私钥
RSA *getPrivateKey(const string &strPath)
{
    FILE *fp = fopen(strPath.c_str(), "rb");  
    if(!fp) 
    {
        ULog(eERROR, "打开证书文件失败，请检查证书[%s]是否存在", strPath.c_str());
        return NULL;
    }

    RSA *rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
    if(!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));
        fclose(fp);  
        return NULL;
    }
    fclose(fp);  

    return rsa;
}

void releaseRSA(RSA *rsa)
{
    RSA_free(rsa);
}

string rsaSign(const string &strPath, const char* szToSign, int iToSignLen)
{
    FILE *fp = fopen(strPath.c_str(), "rb");  
    if(!fp) 
    {
        ULog(eERROR, "打开证书文件失败，请检查证书[%s]是否存在", strPath.c_str());
        return NULL;
    }

    RSA *rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
    if(!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));
        fclose(fp);  
        return NULL;
    }
    fclose(fp);  

    //获得md5摘要字符串
    unsigned char szMD5[MD5_DIGEST_LENGTH + 1] = {0}; 
    MD5((const unsigned char*)szToSign, iToSignLen, szMD5);

    //TODO MD5后是否存在空字符
    unsigned char szSHA1[SHA_DIGEST_LENGTH + 1] = {0};
    SHA1(szMD5, strlen((const char*)szMD5), szSHA1);

    //加签
    char *szSign = (char *)malloc(RSA_size(rsa) + 1);

    memset(szSign, 0x00, RSA_size(rsa) + 1);
    int iSignLen = 0;
    //if(!RSA_sign(NID_sha1, szSHA1, SHA_DIGEST_LENGTH, (unsigned char*)szSign, (unsigned int*)&iSignLen, rsa))
    if(!RSA_sign(NID_sha1, szSHA1, SHA_DIGEST_LENGTH, (unsigned char*)szSign, (unsigned int*)&iSignLen, rsa))
    {
        ULog(eERROR, "SHA1withRSA加签失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));
        free(szSign);
        return "";
    }

    char *szHexBuf = (char *)malloc(iSignLen*2 + 1);
    memset(szHexBuf, 0x00, iSignLen*2 + 1);
    aps::Toolkit::bin2hex(szSign, iSignLen, (unsigned char*)szHexBuf, iSignLen*2);

    string strSignHex(szHexBuf);

    free(szSign);
    free(szHexBuf);

    return strSignHex;
}

int rsaVerify(const string &strPath, const char* szToVerify, int iLen, const std::string &strSignHex)
{
    FILE *fp = fopen(strPath.c_str(), "rb") ;  
    if(!fp) 
    {
        ULog(eERROR, "打开证书文件失败，请检查证书[%s]是否存在", strPath.c_str());
        return -1;
    }
    unsigned char szFileBuf[2048 + 1] = {0};
    unsigned int iReadLen = fread(szFileBuf, 1, 2048, fp);  
    fclose(fp);  

    X509 *x509 = X509_new();
    unsigned char* pBuf = szFileBuf;

    if (!d2i_X509(&x509, (const unsigned char **)&pBuf, iReadLen))
    {
        ULog(eERROR, "解析公钥文件失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        X509_free(x509);   
        return -1;
    }

    EVP_PKEY *evpPKey = X509_get_pubkey(x509);
    if (!evpPKey)
    {
        ULog(eERROR, "获取公钥失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        X509_free(x509);   
        return -1;
    }

    RSA *rsa = EVP_PKEY_get1_RSA(evpPKey);
    if (!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        EVP_PKEY_free(evpPKey);
        X509_free(x509);   
        return -1;
    }

    //获得md5摘要字符串
    unsigned char szMD5[MD5_DIGEST_LENGTH + 1] = {0}; 
    MD5((const unsigned char*)szToVerify, iLen, szMD5);

    //TODO MD5后是否存在空字符
    unsigned char szSHA1[SHA_DIGEST_LENGTH + 1] = {0};
    SHA1(szMD5, strlen((const char*)szMD5), szSHA1);
    

    char szSignBin[1000 + 1] = {0};
    aps::Toolkit::hex2bin(strSignHex, szSignBin, 1000);

    //加签
    char *szSign = (char *)malloc(RSA_size(rsa) + 1);
    memset(szSign, 0x00, RSA_size(rsa) + 1);
    //if(!RSA_verify(NID_sha1, szSHA1, SHA_DIGEST_LENGTH, 
    if(!RSA_verify(NID_sha1, szSHA1, SHA_DIGEST_LENGTH, 
                (const unsigned char*)szSignBin, strSignHex.length()/2, rsa))
    {
        ULog(eERROR, "SHA1withRSA验签失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));
        free(szSign);
        return -1;
    }

    free(szSign);
    
    releaseRSA(rsa);
    EVP_PKEY_free(evpPKey);
    X509_free(x509);   

    return 0;
}

//验密
string rsaDecrypt(const string &strPath, const char* szToDecry, int iLen)
{
    if (iLen % RSA_KEY_LENGTH*2 != 0)
    {
        ULog(eERROR, "加密报文长度错误，验密失败", strPath.c_str());
        return "";
    }

    FILE *fp = fopen(strPath.c_str(), "rb");  
    if(!fp) 
    {
        ULog(eERROR, "打开证书文件失败，请检查证书[%s]是否存在", strPath.c_str());
        return NULL;
    }

    RSA *rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
    if(!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));
        fclose(fp);  
        return NULL;
    }
    fclose(fp);  

    char szBuf[RSA_KEY_LENGTH + 1] = {0};
    char szBinBuf[RSA_KEY_LENGTH + 1] = {0};
    string strDeced;

    int iLenTmp = RSA_KEY_LENGTH * 2;
    for (int i = 0; i < iLen/(RSA_KEY_LENGTH*2); i++)
    {
        memset(szBinBuf, 0x00, sizeof(szBinBuf));
        memset(szBuf, 0x00, sizeof(szBuf));

        string strTmp(szToDecry + iLenTmp * i, iLenTmp);

        aps::Toolkit::hex2bin(strTmp, szBinBuf, iLenTmp);

        if(RSA_private_decrypt(RSA_KEY_LENGTH, (unsigned char *)szBinBuf, 
                    (unsigned char*)szBuf, rsa, RSA_PKCS1_PADDING) < 0)
        {
            ULog(eERROR, "RSA验密失败, 原因[%s]", 
                    ERR_reason_error_string(ERR_get_error()));

            releaseRSA(rsa);
            return "";
        }
        strDeced += szBuf;
    }

    releaseRSA(rsa);

    return strDeced;
}

//加密
string rsaEncrypt(const string& strPath, const char* szToEnc, int iLen)
{
    FILE *fp = fopen(strPath.c_str(), "rb") ;  
    if(!fp) 
    {
        ULog(eERROR, "打开证书文件失败，请检查证书[%s]是否存在", strPath.c_str());
        return "";
    }
    unsigned char szFileBuf[2048 + 1] = {0};
    unsigned int iReadLen = fread(szFileBuf, 1, 2048, fp);  
    fclose(fp);  

    X509 *x509 = X509_new();
    unsigned char* pBuf = szFileBuf;

    if (!d2i_X509(&x509, (const unsigned char **)&pBuf, iReadLen))
    {
        ULog(eERROR, "解析公钥文件失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        X509_free(x509);   
        return "";
    }

    EVP_PKEY *evpPKey = X509_get_pubkey(x509);
    if (!evpPKey)
    {
        ULog(eERROR, "获取公钥失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        X509_free(x509);   
        return "";
    }

    RSA *rsa = EVP_PKEY_get1_RSA(evpPKey);
    if (!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        EVP_PKEY_free(evpPKey);
        X509_free(x509);   
        return "";
    }

    int iBlockLen = RSA_KEY_LENGTH - 11 - 1;  //分段大小
    char szBuf[RSA_KEY_LENGTH + 1] = {0};
    char szHexBuf[RSA_KEY_LENGTH*2 + 1] = {0};

    string strEnced;
    //strEnced.reserve((iLen/iRsaLen+1)*iRsaLen*2);
    //strEnced.clear();

    int iLenTmp = iLen>=iBlockLen? iBlockLen: iLen;
    for (int i = 0; i < iLen/iBlockLen + 1; i++)
    {
        memset(szBuf, 0x00, sizeof(szBuf));
        memset(szHexBuf, 0x00, sizeof(szHexBuf));
        if (i == iLen/iBlockLen)
            iLenTmp = iLen - iBlockLen*i;

        if(RSA_public_encrypt(iLenTmp, (unsigned char *)szToEnc + iBlockLen*i, 
                    (unsigned char*)szBuf, rsa, RSA_PKCS1_PADDING) < 0)
        {
            ULog(eERROR, "RSA加密失败, 原因[%s]", 
                    ERR_reason_error_string(ERR_get_error()));
            
            return "";
        }

        aps::Toolkit::bin2hex(szBuf, RSA_KEY_LENGTH, (unsigned char*)szHexBuf, RSA_KEY_LENGTH*2);
        strEnced += szHexBuf;
    }

    releaseRSA(rsa);
    EVP_PKEY_free(evpPKey);
    X509_free(x509);   

    return strEnced;
}

int main(int argc, char *argv[])
{
    //LogManager::init(Z_DEFAULT_LOGDRIVER_NAME, "./test.xml");
    MemBuffer mem;

    if (argc < 4)
    {
        printf("usage: en 要加密加签的报文文件 金科公钥文件 商户私钥文件\n");
        return 0;
    }

    mem.loadFromFile(argv[1]);
    string strMsg((char *)mem.getRawBuffer());
    size_t iPosTmp = strMsg.rfind('\r');
    if (iPosTmp != string::npos )
    {
        strMsg.erase(iPosTmp);
    }

    iPosTmp = strMsg.rfind('\n');
    if (iPosTmp != string::npos )
    {
        strMsg.erase(iPosTmp);
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

    string strEnced = rsaEncrypt(argv[2], strMsgBody.c_str(), strMsgBody.length());
    cout << strEnced << endl;
    //cout << rsaDecrypt("/home/spring/project/qhjk/product/Linux64/var/certs/qhjk20160309.key", strEnced.c_str(), strEnced.length()) << endl;

    //将加密后的报文放入待签名串
    iTagBegin = strForChkSig.find("&msgbody=") + strlen("&msgbody=");
    string strTmpA(strForChkSig.substr(0, iTagBegin));
    strTmpA += strEnced;
    string strTmpB(strForChkSig.substr(iTagBegin));
    strTmpA += strTmpB;

    //cout << strTmpA << endl;

    string strSignHex = rsaSign(argv[3], strTmpA.c_str(), strTmpA.length());
    cout << strSignHex << endl;

    //新报文体写入原文件中
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

    //if (rsaVerify("/home/spring/project/qhjk/product/Linux64/var/certs/qhjk20160309.crt",
    //            strTmpA.c_str(), strTmpA.length(), strSignHex))
    //    cout << "失败" << endl;
    //else
    //    cout << "成功" << endl;

    return 0;
}

