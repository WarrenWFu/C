#include <iostream>
#include <fstream>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

string qRead(const string &sFilePath)
{
    std::string sBuf;

    std::ifstream f(sFilePath.c_str());
    f.seekg(0, std::ios::end);
    sBuf.resize(f.tellg());
    f.seekg(0);
    f.read((char *)sBuf.data(), sBuf.size());
    f.close();

    return sBuf;
}

int main(int argc, char *argv[])
{
    sockaddr_in socketAddr_in;

    socketAddr_in.sin_family = AF_INET;
    socketAddr_in.sin_port = htons(atoi(argv[1]));
    socketAddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");

    string s = qRead(argv[2]);
    for (int i=0; i < atoi(argv[3]); i++)
    {
        int sockfd = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        int res = ::connect(sockfd, (sockaddr*)&socketAddr_in, sizeof(sockaddr_in));
        if (res < 0)
        {
            cout << i << " 连接失败" << endl;
        }
        else if (res == 0)
        {
            cout << i << endl;
            //::sleep(10);
            cout << write(sockfd, s.c_str(), s.length()) << endl;
        }
        else
        {
            cout << "不可能到此" << endl;
        }

        close(sockfd);
    }

    return 0;
}
