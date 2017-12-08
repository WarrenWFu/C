#include "pugixml.hpp"

#include <string.h>
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

int readFile(const std::string &sPath, std::string &sBuf) 
{
    sBuf.clear();

    std::ifstream f(sPath.c_str());
    if (!f.good())
    {
        return -1;
    }
    f.seekg(0, std::ios::end);
    sBuf.resize(f.tellg());
    f.seekg(0);
    f.read((char *)sBuf.data(), sBuf.size());

    f.close();

    return 0;
}

int main(int argc, char **argv)
{
    string sFile;

    if (argc < 2)
    {
        cout << "usage:xsdtoxml xmlfile" << endl;
        return -1;
    }

    if (readFile(argv[1], sFile))
    {
        cout << "读取 " << argv[1] << "文件失败" << endl;
        return -1;
    }

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(sFile.c_str(), sFile.size());
    if (result.status != pugi::status_ok)
    {
        cout << "解析失败，原因" << result.description() << endl;
        return -1;
    }

    cout << strlen(doc.root().first_child().first_child().first_child().first_child().name()) << endl;


    pugi::xml_node loopNode = doc.root().first_child();
    for (; loopNode; loopNode = loopNode.next_sibling())
    {
        std::cout << loopNode.name() << std::endl;
    }

    return 0;
}

