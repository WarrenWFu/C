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
#include <openssl/md5.h>
#include <openssl/sha.h>

using namespace std;

int main(int argc, char *argv[])
{
    unsigned char szMD5[MD5_DIGEST_LENGTH + 1] = {0}; 

    MD5((const unsigned char*)argv[1], strlen(argv[1]), szMD5);

    cout << strlen((const char*)szMD5) << endl;

    unsigned char szSHA1[SHA_DIGEST_LENGTH + 1] = {0};
    SHA1(szMD5, strlen((const char*)szMD5), szSHA1);

    cout << strlen((const char*)szSHA1) << endl;
    cout << szSHA1 << endl;

    return 0;
}

