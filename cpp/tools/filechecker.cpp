/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:用于查找文件中的非ASCII码字符
 *
*******************************************************************************/
#include <iostream>
#include <string>
#include <unistd.h>
#include <cctype>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 
using namespace std;

int main(int argc, char* argv[])
{
	int result = 0;
	int fd = 0;
    char cContainer;
    int iLineNum = 1;
    int iColumnNum = 1;
    
	if(argc < 2)
	{
        cout << "usage: myfilechecker filename" << endl;
	}

    string strFilePath(argv[1]);
    if (string::npos == strFilePath.find("/"))
    {
        strFilePath = "./" + strFilePath;
    }

	if(access(strFilePath.c_str(), F_OK | R_OK ) != 0)
	{
        cout << strFilePath + " doesn't exists." << endl;
        return 0;
	}
	//文件存在则以只读方式打开
	else
	{
        fd = open(strFilePath.c_str(),O_RDONLY);
	}

	if(fd < 0)
	{
        cout << strFilePath + " open failed." << endl;
        close(fd);
		return 0;
	}

	do
	{
		result = read(fd, &cContainer, 1);
		if(result == 0)
		{
            cout << "read " + strFilePath + " end." << endl;
            close(fd);
            return 0;
		}
        iColumnNum += 1;

        if (cContainer == '\n')
        {
            iLineNum += 1;
            iColumnNum = 1;
        }

        if (!isdigit(cContainer) && !isalpha(cContainer) && 
                ((int)cContainer >  127 || (int)cContainer <  0))
        {
            cout << "find a character is not ASCII " << "Line:" << iLineNum;
            cout << " Column:" << iColumnNum << endl;
        }

	}while(true);

	close(fd);

	return 0;

}
