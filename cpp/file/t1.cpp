/**
 * @file        
 * @brief       最高性能的读写文件，使用./a.out 源文件 目标文件
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
*/

#include <iostream>
#include <fstream>
#include <string>

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

void qWrite(const string &sFilePath, const string &sBuf)
{
    std::ofstream fOut(sFilePath.c_str());
    fOut.write(sBuf.data(), sBuf.size());
    fOut.close();
}

int main(int argc, char* argv[])
{
    qWrite(argv[2], qRead(argv[1]));

    return 0;
}

