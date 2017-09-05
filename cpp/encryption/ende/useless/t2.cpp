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

    //string strSignHex = rsaEnc.rsaSign(strTmpA.c_str(), strTmpA.length());
    string strTest = "72E1DD133DDAB451463486A9B3B5E57259DB332D10CDCCCE506D1378F36EAB688D191E800ADC4E36750B655C6F8F701A8996870AB708D703E6579ECF4A2F216059917EDBFD15FE95BAEF4B2FD335D88E1E67EA0D700850931142DA2CF146D08F14C549C8E2C82878F8F1415F44FBD4743092278A9B1DAC2E63DE09DDEBF6600D10C4C076485244E6E8B30C356DC0C92E4EC25BFFAE881E6930FE371EF7FC0BE88E91FC3178904A24F4A5D11A3A00E03C62AEEF95CBB729994306A282F68662D576ECA36C2FADD8B22A31FC2F1C66FCC7A28D6CAA8A4CE882736AEA19B8E1BE75D189A31054B58736257BA7DEEC67FADD75A19C44BA871BFF8306B02CB7BDB2E10AB65BA5ED5A838BB02E17759D983F969C4FB8E51B68B92FC9C5A5A5D591FE1F5085B31236B9DAA995A2ADC78D6720052943A7F1456D9A0F85D13B0D2F64C44EE85E554A9BC31B0F4FDCACDAE3EEE7312A3C453DA9F962E8DDBB96B36867200EDADBAD5C16EA3A45F4E039AC2300C7F08655E245FB93BB64B3D236644ACFE6780EF50BBE31D0468EDE3343F252FF18D2CC5AFD4E81D7C9C11690B902848F9A012393AE4344A5A8F47174BF6920C71581651360B7C0F5B631C73E9791B810AF9928B154C5AFD82EB43504B7CFA0167F64FFD83D009CE28375B7D2DA8A9791D7874967BBEE4DC1A990E77076A5B69938A4B0124197F6397B99E8093777EA294DDA4FCA7F29C74F37C2851740A0CE38105D7AE8A2244740D7D4304A9D0A0A113BB33BEFC26ED104DE6A13EFB0BF90C0AD8CBADDD3D77DC3375AD78879517B443DD4C760BAEF971A63E7B857FC32F4BA1E11B7BF9641D6B114E9037BD212B113C01D7C7EB946C65447380E5E053F60A1EAD967B63570D3A5B5110EEAAC2057B7C9E95A49F59E0512A74D62F7B54E8C6A08BE36D1E687DEC1ECC2029D34F62542B007270E897BF0A21A07C3C99146719B5C8270E3AB176FFA73CF5C4B220FF89CB9DC840A26ED092CFABE45B01822FAD303E71279809D36AC9BF73BB4214AF5239672BA74CCE393433AABCC8BE73D0C2BC71C31950FB72C92D0E863D9323119C96A50";
    string strSignHex = rsaEnc.rsaSign(strTest.c_str(), strTest.length());
    cout << strSignHex << endl;

    string strTestB = "6B935E18F502B09979AD87ABA1602DACD17B4B1DED40009F315D1AAA176DE033469EE8609E057BF9245D302B7D39F04C8D266ECD99093EDC09DFA3F79941184ACE02CC42556A88EB7C58685204DE5C5FB216A04C6E157227D63F9E6926FEEC371A5934D0BE2779BB50C07C35301ECA77AC960AB311EABFF501CD200E2663117CEF6FEBD0679CCB51EB66542DFFF01B2F550292AF16C93CE1D4805BFEFD447F64D86B5F0338BB771EDC7812EDE3A8E4A9E1613B364B5FB36A16547D1E710E76F314DC8A83B3B50BE390ADC2F7419880AE733969AACBB5E9773B82CD5935BB659A048F1A430F3269BD66C70A8FFA15356D2996294228F3F48C54ED7CA3EB8F2C2F";
    string strTestC = "72E1DD133DDAB451463486A9B3B5E57259DB332D10CDCCCE506D1378F36EAB688D191E800ADC4E36750B655C6F8F701A8996870AB708D703E6579ECF4A2F216059917EDBFD15FE95BAEF4B2FD335D88E1E67EA0D700850931142DA2CF146D08F14C549C8E2C82878F8F1415F44FBD4743092278A9B1DAC2E63DE09DDEBF6600D10C4C076485244E6E8B30C356DC0C92E4EC25BFFAE881E6930FE371EF7FC0BE88E91FC3178904A24F4A5D11A3A00E03C62AEEF95CBB729994306A282F68662D576ECA36C2FADD8B22A31FC2F1C66FCC7A28D6CAA8A4CE882736AEA19B8E1BE75D189A31054B58736257BA7DEEC67FADD75A19C44BA871BFF8306B02CB7BDB2E10AB65BA5ED5A838BB02E17759D983F969C4FB8E51B68B92FC9C5A5A5D591FE1F5085B31236B9DAA995A2ADC78D6720052943A7F1456D9A0F85D13B0D2F64C44EE85E554A9BC31B0F4FDCACDAE3EEE7312A3C453DA9F962E8DDBB96B36867200EDADBAD5C16EA3A45F4E039AC2300C7F08655E245FB93BB64B3D236644ACFE6780EF50BBE31D0468EDE3343F252FF18D2CC5AFD4E81D7C9C11690B902848F9A012393AE4344A5A8F47174BF6920C71581651360B7C0F5B631C73E9791B810AF9928B154C5AFD82EB43504B7CFA0167F64FFD83D009CE28375B7D2DA8A9791D7874967BBEE4DC1A990E77076A5B69938A4B0124197F6397B99E8093777EA294DDA4FCA7F29C74F37C2851740A0CE38105D7AE8A2244740D7D4304A9D0A0A113BB33BEFC26ED104DE6A13EFB0BF90C0AD8CBADDD3D77DC3375AD78879517B443DD4C760BAEF971A63E7B857FC32F4BA1E11B7BF9641D6B114E9037BD212B113C01D7C7EB946C65447380E5E053F60A1EAD967B63570D3A5B5110EEAAC2057B7C9E95A49F59E0512A74D62F7B54E8C6A08BE36D1E687DEC1ECC2029D34F62542B007270E897BF0A21A07C3C99146719B5C8270E3AB176FFA73CF5C4B220FF89CB9DC840A26ED092CFABE45B01822FAD303E71279809D36AC9BF73BB4214AF5239672BA74CCE393433AABCC8BE73D0C2BC71C31950FB72C92D0E863D9323119C96A50";
    //if (rsaEnc.rsaVerify(strTestB.c_str(), strTestB.length(), strSignHex.c_str()))
    if (rsaEnc.rsaVerify(strTestC.c_str(), strTestC.length(), strTestB.c_str()))
        cout << "失败" << (ERR_get_error()) << endl;
    else
        cout << "成功" << endl;
#if 0
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
#endif

    return 0;
}

