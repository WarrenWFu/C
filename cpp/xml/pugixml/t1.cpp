/**
 * @file        
 * @brief       本代码用于实现schema到xml的转换，不支持远程xsd文件获取，import命令，要求qualified
 *
 * @author      Warren.Fu
 * @date        
 * @copyright   
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include "pugixml.hpp"

#define DEFAULT_SCHEMA_NAMESPACE "http://www.w3.org/2001/XMLSchema"

using namespace std;

class Schema;

class Schema {
public:
    string name;
    string nsPrefix;
    string targetNs;

    //string XSDNamespacePrefix;
    //Schema *XSDParentSchema;
    /*
       hasAttrAttributeFormDefault
       hasAttrBlockDefault
       hasAttrElementFormDefault
       hasAttrFinalDefault
       hasAttrLang
       hasAttrId
       hasAttrSchemaLocation
       hasAttrTargetNamespace
       hasAttrVersion
       hasElemAnnotation
       hasElemsAttribute
       hasElemsAttributeGroup
       hasElemsComplexType
       hasElemsElement
       hasElemsGroup
       hasElemsInclude
       hasElemsImport
       hasElemsNotation
       hasElemsRedefine
       hasElemsSimpleType
       */

    string loadLocalPath;
    string loadUri;
};


int readFile(const string &sPath, string &sBuf) 
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
    //读取文件
    string sFile;

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

    Schema s;
    bool isXml = true;
    pugi::xml_node fstNode = doc.first_child();
    string sSN(fstNode.name());

    //获取schema标签ns
    if (strstr(sSN.c_str(), "schema"))
    {
        if (0 != strcmp(sSN.c_str(), "schema"))
        {
            int iPos = sSN.find(":");
            if (iPos == string::npos || 0 != strcmp(sSN.c_str()+iPos+1, "schema"))
            {
                cout << "错误的XML格式" << endl;
                return -1;
            }
            s.nsPrefix = string(sSN.c_str(), iPos);
        }

        string sTmp = "xmlns:" + s.nsPrefix;
        if (0 != strcmp(fstNode.attribute(sTmp.c_str()).value(), 
                    DEFAULT_SCHEMA_NAMESPACE))
        {
                cout << "错误的XML格式" << endl;
                return -1;
        }
    }
    else
    {
        cout << "错误的XML格式" << endl;
        return -1;
    }

    //获取targetNamespace
    pugi::xml_attribute attrTmp =  doc.first_child().attribute("targetNamespace");
    if (attrTmp.empty())
        cout << "未定义targetNamespace" << endl;
    else
        s.targetNs = attrTmp.value();

    //获取报文的根结点
    string sTmp = s.nsPrefix+":element";
    pugi::xml_node xmlRootNode = doc.child(sTmp.c_str());
    if (xmlRootNode.empty())
    {
        cout << "错误的XML格式" << endl;
        return -1;
    }

    for (pugi::xml_node nodeTmp = xmlRootNode.child("");)


    //    for (pugi::xml_node_iterator it = doc.children().begin(); 
    //            it != doc.children().end(); it++)
    //    {
    //        //找到schema
    //        if (strstr(it->name(), "schema"))
    //        {
    //            if (0 != strcmp(it->name(), "schema"))
    //            {
    //                string sTmp = string(it->name());
    //                int iPos = sTmp.find(":");
    //                if (0 != strcmp(sTmp.c_str()+iPos, "schema"))
    //                    continue;
    //                if (iPos == string::npos)
    //                {
    //                    isXml = false;
    //                    break;
    //                }
    //                s.nsPrefix = string(it->name(), iPos);
    //                cout << s.nsPrefix << endl;
    //            }
    //            bool bXml = false;
    //            for (pugi::xml_attribute_iterator itB = it->attributes().begin();
    //                    itB != it->attributes().end(); itB ++)
    //            {
    //                if (0 == strcmp(itB->name(), "targetNamespace")) 
    //                {
    //                    cout << itB->value() << endl;
    //                }
    //                else if (0 == strcmp(itB->name(), "xmlns:xml")) 
    //                    bXml = true;
    //            }
    //            if (!bXml)
    //            {
    //
    //            }
    //        }
    //    }

    if (!isXml) 
    {
        cout << "xml文件格式错误" << endl;
        return -1;
    }

    //    pugi::xml_document docOut;
    //    docOut.append_child();


    return 0;
}

