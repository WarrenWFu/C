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
#include <log/logger.hpp>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

using namespace std;

void PrintHex(unsigned char *str, unsigned int len)  
{  
    int i = 0;  
    for(i =0;i< len; i++)  
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
#if 0
    string strDataOri = "123abc";
    //转16进制
    //string strDataHex = aps::Toolkit::bin2hex(strDataOri.c_str(), 
    //        strDataOri.length());


    unsigned char *p_en = NULL;
    RSA *p_rsa;
    FILE *file;
    int flen,rsa_len;
    //if((file = fopen("/home/spring/rsa_public_key.pem","r"))==NULL){
    if((file = fopen("/home/spring/cert.pem","r"))==NULL){
        perror("open key file error");
        exit(-1);
    }   

    if((p_rsa=PEM_read_RSA_PUBKEY(file,NULL,NULL,NULL))==NULL)
    //if((p_rsa=PEM_read_RSAPublicKey(file,NULL,NULL,NULL))==NULL)
    { 
        ERR_print_errors_fp(stdout);
        cout << "打开公钥文件失败" << endl;
    }   
    flen = strDataOri.length();
    rsa_len = RSA_size(p_rsa);
    p_en = (unsigned char *)malloc(rsa_len+1);
    memset(p_en, 0x00, rsa_len+1);
    if(RSA_public_encrypt(rsa_len, (unsigned char *)strDataOri.c_str(), 
                (unsigned char*)p_en, p_rsa, RSA_NO_PADDING)<0)
    {
        cout << "加密失败" << endl;
    }
    RSA_free(p_rsa);
    fclose(file);

    //char *pHex = (char *)malloc(rsa_len+1);
    //memset(pHex, 0x00, rsa_len+1);
    //if (aps::Toolkit::bin2hex((const char*)p_en, pHex, rsa_len, true))
    //    cout << pHex << endl;
    //else
    //    cout << "转换失败" << endl;
    
    cout << aps::Toolkit::bin2hex(p_en, rsa_len) << endl;

    free(p_en);
#endif
    X509 *x;  
    FILE *fp;  
    unsigned char   buf[5000],*p;  
    
    EVP_PKEY *k;  
    RSA *rsa;  
    unsigned char n[300] ={0x0};  
    unsigned char e[300] ={0x0};  
    unsigned int len;  
    /* www.google.com2为DER编码的数字证书 ，从firefox中导出 
    */  
    fp=fopen("/home/spring/tmp/qhjk20160309.crt","rb");  
    //fp=fopen("/home/spring/tmp/qhjk20160309.pfx","rb");  
    if(!fp) 
    {
        cout << "打开文件失败" << endl;
        return -1;
    }
    len=fread(buf,1,5000,fp);  
    fclose(fp);  
    p=buf;  
    x=X509_new();  
    d2i_X509(&x,(const unsigned char **)&p,len);  
    k=X509_get_pubkey(x);  
    rsa=EVP_PKEY_get1_RSA(k);  

    EVP_PKEY_free(k);
    X509_free(x);   

    //if(rsa->n != NULL)  
    //{  
    //    BN_bn2bin(rsa->n, n);  
    //    len= BN_num_bytes(rsa->n);  
    //printf("N:\n");  
    //PrintHex(n,len);  
    //}  
    //else  
    //{  
    //    printf("DER error \n");  
    //}  
    //if(rsa->e != NULL)  
    //{  
    //    BN_bn2bin(rsa->e, e);  
    //    len= BN_num_bytes(rsa->e);  
    //    printf("E:\n");  
    //    PrintHex(e,len);  
    //}  
    //else  
    //{  
    //    printf("DER error \n");  
    //}  

    //默认使用的是 RSA_PKCS1_PADDING，即这里最大加密块为64-11=53,大量数组需要分组处理
    const char *srcStr = "45E5E9A06F6BEA8561CE6E26EA3F8317591C8BFB49E5AA22F8B51A14DDDB1DEECE030F0F42D2C1B999B9E9B79B978165613A43CC67443B35CA04245E5E9A06F6BEA8561CE6E26EA3F8317591C8BFB49E5AA22F8B51A14DDDB1DEECE030F0F42D2C1B999B9E9B79B978165613A43CC67443B35CA042aaaaaaaaaa123456789";
    char encData[1235] = {0};
    int iOutLen = 0;
    char decData[1235] = {0};
    int declen = 0;
    printf("秘钥长度[%d]\n", RSA_size(rsa));
    printf("原文长度[%ld]\n", strlen(srcStr));
    
    //加密
    if(RSA_public_encrypt(atoi(argv[1]), (unsigned char *)srcStr, (unsigned char*)encData, rsa, RSA_PKCS1_PADDING) < 0)
    {
        printf("调用失败, 原因[%d/%s]\n", ERR_get_error(), ERR_reason_error_string(ERR_get_error()));
        return -1;
    }

    //EVP_PKEY_CTX *ectx;
    //ectx = EVP_PKEY_CTX_new(k, NULL);
    //EVP_PKEY_encrypt_init(ectx);
    //if (EVP_PKEY_encrypt(ectx, NULL, (size_t *)&iOutLen, (const unsigned char*)srcStr, strlen(srcStr)) <= 0)
    //{
    //    printf("调用失败");
    //    return -1;
    //}


    //int iRes = EVP_PKEY_encrypt(ectx, (unsigned char*)encData, 
    //        (size_t*)&iOutLen, (const unsigned char*)srcStr, strlen(srcStr));


    printf("密文长度[%ld]\n",strlen(encData));
    unsigned char szTmp[1000+1] = {0};
    aps::Toolkit::bin2hex(encData, 256, szTmp, sizeof(szTmp));
    printf("16进制密文长度[%d]\n", strlen((const char*)szTmp));
    printf("16进制密文[%s]\n", szTmp);
    //printf("iRes[%d]\n",iRes);

    //解密
    //EVP_PKEY_CTX *dctx;
    //dctx = EVP_PKEY_CTX_new(k, NULL);
    //EVP_PKEY_decrypt_init(dctx);
    //EVP_PKEY_decrypt(dctx, decData, &declen, encData, enclen);
    //printf("dec=%s\n",decData);

    //EVP_PKEY_CTX_free(dctx);
    //EVP_PKEY_CTX_free(ectx);

    
    fp = NULL; 
    if((fp = fopen("/home/spring/1.key", "r"))  == NULL) 
    { 
        printf("打开私钥证书失败");
        return 0; 
    }

    rsa = NULL;
    if((rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL)) == NULL )
    {
        printf("PEM_read_RSAPrivateKey 失败");
        return 0;
    }

    char szTmpB[300] = {0};
    aps::Toolkit::hex2bin((const char*)szTmp, szTmpB, sizeof(szTmpB));

    //encData
    int rsa_len = RSA_size(rsa);
    char* chptrOut = (char*)malloc(rsa_len+1);
    memset(chptrOut, 0x00, rsa_len+1);

    //if(RSA_private_decrypt(256, (unsigned char *)encData, (unsigned char*)chptrOut, rsa, RSA_PKCS1_PADDING) < 0 )
    if(RSA_private_decrypt(256, (unsigned char *)szTmpB, (unsigned char*)chptrOut, rsa, RSA_PKCS1_PADDING) < 0 )
    {
        printf("RSA_private_decrypt 核密失败");
        free(chptrOut);
        return 0;
    }
    else
        printf("核密成功, 明文结果[%s]\n", chptrOut);

    free(chptrOut);

    RSA_free(rsa);

#if 0
    //-----------------------------------------------解验签名-------------------------------------
    //MD5摘要
    unsigned char md_value[EVP_MAX_MD_SIZE];//保存输出的摘要值的数组  
    unsigned int md_len, i;  
    EVP_MD_CTX mdctx;           //EVP消息摘要结构体  

    EVP_MD_CTX_init(&mdctx);//初始化摘要结构体   
    EVP_DigestInit_ex(&mdctx, EVP_md5(), NULL);//设置摘要算法和密码算法引擎，这里密码算法使用MD5，算法引擎使用OpenSSL默认引擎即软算法  
    EVP_DigestUpdate(&mdctx, encData, 256);
    EVP_DigestFinal_ex(&mdctx, md_value, &md_len);//摘要结束，输出摘要值    
    EVP_MD_CTX_cleanup(&mdctx);//释放内存

    printf("md_value长度[%d]", strlen((char*)md_value));

    //
    int verifyResult = RSA_verify(NID_md5, chszMD5, SHA_DIGEST_LENGTH, (const unsigned char*)chptrSign, iSignLen, rsa);
#endif


    return 0;
}

