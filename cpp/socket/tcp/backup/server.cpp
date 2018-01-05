/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:
 *
 *******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <base/tcpSocket.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    int sockfd = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in socketAddr_in;

    socketAddr_in.sin_family = AF_INET;
    socketAddr_in.sin_port = htons(atoi(argv[1]));
    socketAddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");

    int res = ::bind(sockfd, (struct sockaddr *)&socketAddr_in, sizeof socketAddr_in);
    if (0 != res) 
    {
        cout << "bind 失败" << endl;
        return -1;
    }

    if (::listen(sockfd, 512)==-1)
    {
        cout << "listen 失败" << endl;
        return false;
    }

    sockaddr_in clientAddr;
    int addrLen = sizeof( clientAddr );
    int iSize = 1024*5;
    char *pSz = (char *)malloc(iSize+1);
    int iCnt = 0;
    int iBytes = 0;
    sleep(1);
    for(;;)
    {
        memset(pSz, 0x00, iSize+1);
        memset(&clientAddr, 0x00, sizeof(clientAddr));
        int newSocket = ::accept(sockfd, (sockaddr *)&clientAddr, (socklen_t *) &addrLen );
        if( -1 == newSocket && EINTR == errno )
        {
            cout << "accept 失败" << endl;
            continue;
        }

        if (newSocket != -1)
        {
            //            cout << inet_ntoa(clientAddr.sin_addr) << endl;
            //            cout << ntohs(clientAddr.sin_port) << endl;
            int iRes = 0;
#if 0
            for (;iBytes < 2000;)
            {
                //iRes = read(newSocket, pSz, iSize);
                iRes = ::recv(newSocket, pSz, iSize, 0);
                if (iRes < 0)
                {
                    cout << "read 错误:" << iRes << endl;
                    break;
                }
                iBytes += iRes;
                cout << ++iCnt << " " << ntohs(clientAddr.sin_port) << endl;
            }
#else
            cout << ++iCnt << endl;
            pid_t pid = ::fork();
            if (pid == -1)
            {
                int er = errno;
                cout << "fork failed" << endl;
                exit(-1);
            }
            else if (pid == 0)
            {
                bool isConn = aps::TcpSocket::recv(newSocket, pSz, 2000, &iRes);
                cout << (isConn?"true ":"false ") << iRes << " " << ntohs(clientAddr.sin_port) << endl;
                close(newSocket);

            }
#endif

            close(newSocket);
        }
    }

    close(sockfd);

    return 0;

}
