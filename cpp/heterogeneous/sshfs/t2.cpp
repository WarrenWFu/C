/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用sshfs挂载远程文件到本地，之后进行操作
 *
*******************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    system("sshfs -o uid=503 -o gid=502 -o allow_other -o follow_symlinks \
            -o umask=011 \
            strt@172.168.65.158:/disk/upp/strt/strt_server/product/Linux64/var/ \
            /mnt/strtdev/");

	FILE *fp = NULL;

	fp = NULL;
	//以读方式创建文件
	fp = fopen("/mnt/strtdev/current.pid", "r");
	if(!fp)
	{
        cout << "打开失败" << endl;
		return -1;
	}

    char cStr[100] = {0};

    fgets(cStr, 100, fp);

    cout << string(cStr) << endl;

	fclose(fp);

	return 0;

}
