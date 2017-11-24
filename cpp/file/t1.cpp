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

int main(int argc, char* argv[])
{
    std::string sBuf;

    std::ifstream f(argv[1]);
    f.seekg(0, std::ios::end);
    sBuf.resize(f.tellg());
    f.seekg(0);
    f.read((char *)sBuf.data(), sBuf.size());
    f.close();


    std::ofstream fOut(argv[2]);
    fOut.write(sBuf.data(), sBuf.size());
    fOut.close();

    return 0;
}

