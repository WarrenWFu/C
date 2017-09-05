/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
*******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    int sockfd = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in socketAddr_in;

    socketAddr_in.sin_family = AF_INET;
    socketAddr_in.sin_port = htons(atoi(argv[1]));
    socketAddr_in.sin_addr.s_addr = inet_addr("192.168.137.101");

    int res = ::connect(sockfd, (sockaddr*)&socketAddr_in, sizeof(sockaddr_in));
    if (res < 0)
    {
        cout << "连接失败" << endl;
    }
    else if (res == 0)
    {
        cout << "连接成功" << endl;
    }
    else
    {
        cout << "不可能到此" << endl;
    }

    sleep(2);

    close(sockfd);

    return 0;
}
