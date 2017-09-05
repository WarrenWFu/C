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

using namespace std;

bool hex2bin(const string& inHexStr, void*outBuffer, unsigned int bufferLen, bool bZeroTail)
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
int main(int argc, char *argv[])
{
	string str1(argv[1]);

    char szBuf[100] = {0};
    char szBuf1[] = "1";

    hex2bin(str1, szBuf, 100, true);

    cout << "[" << szBuf << "]" << endl;


    return 0;
}

