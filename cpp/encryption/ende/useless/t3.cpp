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
#include <openssl/pkcs12.h>
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

//载入私钥
EVP_PKEY *getPrivateKey(const string &strPath, const string &strPWD)
{
    FILE *fp;
    //TODO 这个key是否可以在获取RSA后free
    EVP_PKEY *evpPKey;
    //X509 *cert;
    //STACK_OF(X509) *ca = NULL;
    PKCS12 *p12;

    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    if ((fp = fopen(strPath.c_str(), "rb")) == NULL)
    {
        return NULL;
    }
    p12 = d2i_PKCS12_fp(fp, NULL);
    fclose(fp);

    if (!p12) {
        fprintf(stderr, "Error reading PKCS#12 file\n");
        ERR_print_errors_fp(stderr);
        //exit(1);
        return NULL;
    }
    //if (!PKCS12_parse(p12, strPWD.c_str(), &evpPKey, &cert, &ca))
    if (!PKCS12_parse(p12, strPWD.c_str(), &evpPKey, NULL, NULL))
    {
        fprintf(stderr, "Error parsing PKCS#12 file\n");
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    PKCS12_free(p12);

    return evpPKey;
}

EVP_PKEY *getPublicKey(const string &strPath)
{
    FILE *fp = fopen(strPath.c_str(), "rb") ;  
    if(!fp) 
    {
        ULog(eERROR, "打开证书文件失败，请检查证书[%s]是否存在", strPath.c_str());
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    size_t ifileSize = ftell(fp);
    rewind(fp);
    
    unsigned char *szFileBuf = new unsigned char[ifileSize + 1];
    memset(szFileBuf, 0x00, ifileSize + 1);
    unsigned int iLen = fread(szFileBuf, 1, ifileSize, fp);  
    fclose(fp);  

    X509 *x509 = X509_new();
    unsigned char* pBuf = szFileBuf;

    if (!d2i_X509(&x509, (const unsigned char **)&pBuf, iLen))
    {
        ULog(eERROR, "解析公钥文件失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        X509_free(x509);   
        delete [] szFileBuf;
        return NULL;
    }

    EVP_PKEY *evpPKey = X509_get_pubkey(x509);
    if (!evpPKey)
    {
        ULog(eERROR, "获取公钥失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        X509_free(x509);   
        delete [] szFileBuf;
        return NULL;
    }
    delete [] szFileBuf;
    X509_free(x509);   

    return evpPKey;
}

void releaseRSA(RSA *rsa)
{
    RSA_free(rsa);
}

void releaseKey(EVP_PKEY *evpPKey)
{
    EVP_PKEY_free(evpPKey);
}

string rsaSign(const char* szToSign, int iToSignLen, EVP_PKEY *evpPKey)
{
    if (!evpPKey || szToSign == NULL)
    {
        ULog(eERROR, "秘钥或待签名字符串为空");
        return "";
    }

    RSA *rsa = EVP_PKEY_get1_RSA(evpPKey);
    if (!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        return NULL;
    }
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
        releaseRSA(rsa);
        free(szSign);
        return "";
    }
    releaseRSA(rsa);

    char *szHexBuf = (char *)malloc(iSignLen*2 + 1);
    memset(szHexBuf, 0x00, iSignLen*2 + 1);
    aps::Toolkit::bin2hex(szSign, iSignLen, (unsigned char*)szHexBuf, iSignLen*2);

    string strSignHex(szHexBuf);

    free(szSign);
    free(szHexBuf);

    return strSignHex;
}

int rsaVerify(const char* szToVerify, int iLen, const std::string &strSignHex, EVP_PKEY *evpPKey)
{
    if (!evpPKey || szToVerify == NULL)
    {
        ULog(eERROR, "秘钥或待验签字符串为空");
        return -1;
    }

    RSA *rsa = EVP_PKEY_get1_RSA(evpPKey);
    if (!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

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

    //验签
    char *szSign = (char *)malloc(RSA_size(rsa) + 1);
    memset(szSign, 0x00, RSA_size(rsa) + 1);
    //if(!RSA_verify(NID_sha1, szSHA1, SHA_DIGEST_LENGTH, 
    if(!RSA_verify(NID_sha1, szSHA1, SHA_DIGEST_LENGTH, 
                (const unsigned char*)szSignBin, strSignHex.length()/2, rsa))
    {
        ULog(eERROR, "SHA1withRSA验签失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));
        releaseRSA(rsa);
        free(szSign);
        return -1;
    }

    releaseRSA(rsa);
    free(szSign);

    return 0;
}

//验密
string rsaDecrypt(const char* szToDecry, int iLen, EVP_PKEY *evpPKey)
{
    if (!evpPKey || szToDecry  == NULL)
    {
        ULog(eERROR, "秘钥或待加密字符串为空");
        return "";
    }

    if (iLen % RSA_KEY_LENGTH*2 != 0)
    {
        ULog(eERROR, "加密报文长度错误，验密失败");
        return "";
    }

    RSA *rsa = EVP_PKEY_get1_RSA(evpPKey);
    if (!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

        return NULL;
    }

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
string rsaEncrypt(const char* szToEnc, int iLen, EVP_PKEY *evpPKey)
{
    if (!evpPKey || szToEnc == NULL)
    {
        ULog(eERROR, "秘钥或待加密字符串为空");
        return "";
    }

    RSA *rsa = EVP_PKEY_get1_RSA(evpPKey);
    if (!rsa)
    {
        ULog(eERROR, "获取RSA失败, 原因[%s]", 
                ERR_reason_error_string(ERR_get_error()));

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

            releaseRSA(rsa);
            return "";
        }

        aps::Toolkit::bin2hex(szBuf, RSA_KEY_LENGTH, (unsigned char*)szHexBuf, RSA_KEY_LENGTH*2);
        strEnced += szHexBuf;
    }

    releaseRSA(rsa);

    return strEnced;
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

    EVP_PKEY *evpPKeyPub;
    if (!(evpPKeyPub = getPublicKey(argv[2])))
        cout << "获取公钥失败" << endl;

    EVP_PKEY *evpPKeyPri;
    if (!(evpPKeyPri = getPrivateKey(argv[3], "123456")))
        cout << "获取私钥失败" << endl;

    string strEnced = rsaEncrypt(strMsgBody.c_str(), strMsgBody.length(), evpPKeyPub);
    //cout << ((strMsgBody == rsaDecrypt(strEnced.c_str(), strEnced.length(), evpPKeyPri))? "相等": "不等") << endl;

    //将加密后的报文放入待签名串
    iTagBegin = strForChkSig.find("&msgbody=") + strlen("&msgbody=");
    string strTmpA(strForChkSig.substr(0, iTagBegin));
    strTmpA += strEnced;
    string strTmpB(strForChkSig.substr(iTagBegin));
    strTmpA += strTmpB;

    //cout << strTmpA << endl;

    string strSignHex = rsaSign( strTmpA.c_str(), strTmpA.length(), evpPKeyPri);
    //cout << strSignHex << endl;

    //if (rsaVerify(strTmpA.c_str(), strTmpA.length(), strSignHex, evpPKeyPub))
    //    cout << "失败" << endl;
    //else
    //    cout << "成功" << endl;

    releaseKey(evpPKeyPub);
    releaseKey(evpPKeyPri);

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

    return 0;
}

