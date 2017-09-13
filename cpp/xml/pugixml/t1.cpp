/**
 * @file        
 * @brief       本代码用于实现XSD文件的解析，XML schema校验和XSD文件到XML文件的转换，不支持多个命名空间、import、include
 *
 * @author      Warren.Fu
 * @date        2017/09/05
 * @copyright   
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <map>
#include <queue>
#include "pugixml.hpp"

#define DEFAULT_SCHEMA_NAMESPACE "http://www.w3.org/2001/XMLSchema"

typedef bool (*TypeValiFunc)(const std::string&);
typedef bool (*RstValiFunc)(const std::string&, const std::string&);

class XsdNodeBase
{
public:
    XsdNodeBase(){}
    XsdNodeBase(pugi::xml_node node): m_node(node) {}
    virtual ~XsdNodeBase() {}

    pugi::xml_node m_node;
};

//simpleType TODO 属性只支持name，子标签只支持restriction
class XsdSmpTypeNode: public XsdNodeBase
{
public:
    XsdSmpTypeNode(TypeValiFunc func):
        m_pSmp(NULL),
        m_typeVali(func)
        {}
    XsdSmpTypeNode(pugi::xml_node node):
        XsdNodeBase(node),
        m_pSmp(NULL),
        m_typeVali(NULL)
        {}

    XsdSmpTypeNode *m_pSmp; //通过base属性关联到另一个simpleType
    TypeValiFunc m_typeVali;
    std::map<RstValiFunc, std::string> m_mRsts;
};

//attribute TODO 属性只支持name、type、ref，子标签只支持simpleType
class XsdAttrTypeNode: public XsdNodeBase
{
public:
    XsdAttrTypeNode(pugi::xml_node node):
        XsdNodeBase(node),
        m_pSmp(NULL),
        m_pRef(NULL)
        {}

    ~XsdAttrTypeNode()
    {
        if (m_pSmp && m_pSmp->m_node.empty()) //不是xsd文件中单独的结点由自己析构
            delete m_pSmp;
    }

    XsdSmpTypeNode  *m_pSmp; //通过type属性关联到另一个simpleType
    XsdAttrTypeNode *m_pRef; //通过ref属性关联到另一个attribute
};

//complexType TODO 属性只支持name，子标签只支持all、choice、sequence、attribute、element
class XsdCmxTypeNode: public XsdNodeBase
{
public:
    XsdCmxTypeNode(pugi::xml_node node):
        XsdNodeBase(node)
        {}

    std::queue<XsdAttrTypeNode*> m_qAttrs;
    std::queue<XsdNodeBase*> m_qElts;
};

//element TODO 属性只支持name、ref、type，子标签只支持simpleType、complexType
class XsdElementNode: public XsdNodeBase
{
public:
    XsdElementNode(pugi::xml_node node):
        XsdNodeBase(node),
        m_isSmp(true),
        m_pRef(NULL),
        m_pType(NULL),
        m_iLevel(0),
        m_pFirstChild(NULL),
        m_pNextSibling(NULL)
        {}

    ~XsdElementNode()
    {
        if (m_pType && m_pType->m_node.empty())
        {
            delete m_pType;
        }
    }

    bool m_isSmp;         //简单复杂类型标志
    XsdElementNode* m_pRef;
    XsdNodeBase* m_pType;
    int m_iLevel;

    XsdElementNode *m_pFirstChild;
    XsdElementNode *m_pNextSibling;
};

//TODO group
//TODO attributeGroup

class XmlBinTree
{
public:
    XmlBinTree(pugi::xml_node node):
        m_iMaxLevel(0),
        m_iXSLen(0),
        m_rootNode(node),
        m_pRoot(NULL)
        {}

    std::string m_sNsPrefix;
    std::string m_sTargetNs;
    int m_iMaxLevel;

    int m_iXSLen;
    pugi::xml_node m_rootNode;
    XsdElementNode *m_pRoot;
    std::map<size_t, XsdNodeBase*> m_handledNode;
};

using namespace std;

//校验规则基于XML规则，类型校验
bool stringVali(const std::string& val) 
{
    return true;
}

bool intVali(const std::string& val) 
{
    return val == "0" || atoi(val.c_str());
}

bool dateVali(const std::string& val) 
{
    bool bIsValid = false;

    if (val.length() == 10)
    {
        int iYear = atoi(val.substr(0, 4).c_str());
        int iMonth = atoi(val.substr(5, 2).c_str());
        int iDay = atoi(val.substr(8, 2).c_str());
        if (val[4] == '-' && val[7] == '-' && iYear && iMonth && iDay)
        {
            if (iMonth == 1 || iMonth == 3 || iMonth == 5 || iMonth == 7 ||
                    iMonth == 8 || iMonth == 10 || iMonth == 12)
            {
                if (iDay > 0 && iDay < 32)
                    bIsValid = true;
            }
            else if (iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11)
            {
                if (iDay > 0 && iDay < 31)
                    bIsValid = true;
            }
            else if (iMonth == 2)
            {
                if ((iYear % 4 == 0 && iYear % 100 != 0) || iYear % 400 == 0)
                {
                    if (iDay > 0 && iDay < 30)
                        bIsValid = true;
                }
                else
                {
                    if (iDay > 0 && iDay < 29)
                        bIsValid = true;
                }
            }
        }
    }

    return bIsValid;
}

//TODO 待实现
bool timeVali(const std::string& val) 
{
    return true;
}
bool datetimeVali(const std::string& val) 
{
    return true;
}

bool decimalVali(const std::string& val) 
{
    return true;
}
bool byteVali(const std::string& val) 
{
    return true;
}
bool unsignedByteVali(const std::string& val) 
{
    return true;
}
bool shortVali(const std::string& val) 
{
    return true;
}
bool unsignedShortVali(const std::string& val) 
{
    return true;
}
bool integerVali(const std::string& val) 
{
    return true;
}
bool longVali(const std::string& val) 
{
    return true;
}
bool floatVali(const std::string& val) 
{
    return true;
}
bool positiveIntegerVali(const std::string& val) 
{
    return true;
}
bool nonPositiveIntegerVali(const std::string& val) 
{
    return true;
}
bool negativeIntegerVali(const std::string& val) 
{
    return true;
}
bool nonNegativeIntegerVali(const std::string& val) 
{
    return true;
}
bool unsignedLongVali(const std::string& val) 
{
    return true;
}
bool doubleVali(const std::string& val) 
{
    return true;
}
bool booleanVali(const std::string& val) 
{
    return true;
}
bool hexBinaryVali(const std::string& val) 
{
    return true;
}
bool base64BinaryVali(const std::string& val) 
{
    return true;
}
bool anyURIVali(const std::string& val) 
{
    return true;
}

//约束校验
bool enumerationVali(const std::string& val, const std::string& rst)
{
    if (0 == rst.length() || 0 == val.length())
        return false;

    size_t i = 0, j = 0;
    while(true)
    {
        j = rst.find('&', i);
        if (j != string::npos)
        {
            if (0 == memcmp(argv[1], rst.c_str()+i, j-i))
                return true;
        }
        else
        {
            if (0 == memcmp(argv[1], rst.c_str()+i, rst.length()-i))
                return true;
            else
                return false;
        }

        i = j + 1;
    }
}
bool maxLengthVali(const std::string& val, const std::string& rst)
{
    return val.length() <= atoi(rst.c_str());
}
bool minLengthVali(const std::string& val, const std::string& rst)
{
    return val.length() >= atoi(rst.c_str());
}
//TODO 待实现
bool patternVali(const std::string& val, const std::string& rst)
{
    return true;
}
bool fractionDigitsVali(const std::string& val, const std::string& rst)
{
    return true;
}
bool lengthVali(const std::string& val, const std::string& rst)
{
    return true;
}
bool maxExclusiveVali(const std::string& val, const std::string& rst)
{
    return true;
}
bool maxInclusiveVali(const std::string& val, const std::string& rst)
{
    return true;
}
bool minExclusiveVali(const std::string& val, const std::string& rst)
{
    return true;
}
bool minInclusiveVali(const std::string& val, const std::string& rst)
{
    return true;
}
bool totalDigitsVali(const std::string& val, const std::string& rst)
{
    return true;
}
bool whiteSpaceVali(const std::string& val, const std::string& rst)
{
    return true;
}

std::map<std::string, TypeValiFunc> g_typeValis;
std::map<std::string, RstValiFunc> g_rstValis;

void initValidatorMap() 
{
    g_typeValis["string"]             =  stringVali;
    g_typeValis["int"]                =  intVali;
    g_typeValis["date"]               =  dateVali;
    g_typeValis["time"]               =  timeVali;
    g_typeValis["datetime"]           =  datetimeVali;
    g_typeValis["decimal"]            =  decimalVali;
    g_typeValis["byte"]               =  byteVali;
    g_typeValis["unsignedByte"]       =  unsignedByteVali;
    g_typeValis["short"]              =  shortVali;
    g_typeValis["unsignedShort"]      =  unsignedShortVali;
    g_typeValis["integer"]            =  integerVali;
    g_typeValis["long"]               =  longVali;
    g_typeValis["float"]              =  floatVali;
    g_typeValis["positiveInteger"]    =  positiveIntegerVali;
    g_typeValis["nonPositiveInteger"] =  nonPositiveIntegerVali;
    g_typeValis["negativeInteger"]    =  negativeIntegerVali;
    g_typeValis["nonNegativeInteger"] =  nonNegativeIntegerVali;
    g_typeValis["unsignedLong"]       =  unsignedLongVali;
    g_typeValis["double"]             =  doubleVali;
    g_typeValis["boolean"]            =  booleanVali;
    g_typeValis["hexBinary"]          =  hexBinaryVali;
    g_typeValis["base64Binary"]       =  base64BinaryVali;
    g_typeValis["anyURI"]             =  anyURIVali;

    g_rstValis["enumeration"]         =  enumerationVali;
    g_rstValis["maxLength"]           =  maxLengthVali;
    g_rstValis["minLength"]           =  minLengthVali;
    g_rstValis["pattern"]             =  patternVali;
    g_rstValis["fractionDigits"]      =  fractionDigitsVali;
    g_rstValis["length"]           	  =  lengthVali;
    g_rstValis["maxExclusive"]        =  maxExclusiveVali;
    g_rstValis["maxInclusive"]        =  maxInclusiveVali;
    g_rstValis["minExclusive"]        =  minExclusiveVali;
    g_rstValis["minInclusive"]        =  minInclusiveVali;
    g_rstValis["totalDigits"]         =  totalDigitsVali;
    g_rstValis["whiteSpace"]          =  whiteSpaceVali;
}

bool validateNS(const char* src, const char* des, int iLen)
{
    if (strlen(src) < strlen(des)+1)
        return false;

    return 0 == memcmp(src, des, iLen) && *(src+iLen) == ':';
}

bool smpTypeParse(XmlBinTree& xbt, XsdSmpTypeNode& node)
{
    //TODO 添加list和union
    pugi::xml_node pugiNode = node.m_node.child("restriction");
    if (!pugiNode.empty())
    {
        pugi::xml_attribute pugiAttr = pugiNode.attribute("base");
        if (pugiAttr.empty())
        {
            cout << "restriction元素没有base属性" << endl;
            return false;
        }

        if (validateNS(pugiAttr.value(), xbt.m_sNsPrefix.c_str(), 
                    xbt.m_iXSLen)) //内部数据类型
        {
            //查找类型校验
            if(g_typeValis.count(pugiAttr.value()+xbt.m_iXSLen+1))
                node.m_typeVali = g_typeValis[pugiAttr.value()+xbt.m_iXSLen+1];
            else
            {
                cout << "错误的base属性值" << endl;
                return false;
            }

            //查找约束校验
            pugi::xml_object_range<pugi::xml_node_iterator> range = pugiNode.children();
            for (pugi::xml_node_iterator itor = range.begin();
                    itor != range.end(); itor ++)
            {
                if (validateNS(itor->name(), xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen) && 
                        g_rstValis.count(itor->name()+xbt.m_iXSLen+1))
                {
                    if (0 == strcmp(itor->name()+xbt.m_iXSLen+1, "enumeration"))
                    {
                        string sTmp(node.m_mRsts[
                                g_rstValis[itor->name()+xbt.m_iXSLen+1]]);
                        sTmp.append(itor->value());
                        sTmp.append(1, '&');

                        node.m_mRsts[g_rstValis[itor->name()+xbt.m_iXSLen+1]] = sTmp;
                    }
                    else
                        node.m_mRsts[g_rstValis[itor->name()]] = itor->value();
                }
                else
                {
                    cout << "错误的约束元素" << endl;
                    return false;
                }
            }
        }
        else //引用了另外的simpleType
        {
            string sTmp(xbt.m_sNsPrefix);
            sTmp += ":simpleType";
            pugi::xml_node pugiNodeTmp = xbt.m_rootNode.find_child_by_attribute(
                    sTmp.c_str(), "name", pugiAttr.value());
            if (!pugiNodeTmp.empty() && validateNS(pugiNodeTmp.name(), 
                        xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen))
            {
                //防止自身引用
                if (0 == strcmp(node.m_node.attribute("name").value(), 
                            pugiNodeTmp.attribute("name").value()))
                {
                    cout << "base属性值引用了自己！" << endl;
                    return false;
                }

                //可能已经解析
                if (xbt.m_handledNode.count(pugiNodeTmp.hash_value()))
                    node.m_pSmp = (XsdSmpTypeNode *)xbt.m_handledNode[
                        pugiNodeTmp.hash_value()];
                else
                {
                    XsdSmpTypeNode* pNodeTmp = new XsdSmpTypeNode(pugiNodeTmp);
                    xbt.m_handledNode[pugiNodeTmp.hash_value()] = pNodeTmp;
                    node.m_pSmp = pNodeTmp;
                    //递归调用
                    return smpTypeParse(xbt, *pNodeTmp);
                }
            }
            else
            {
                cout << "未找到base属性值指定的simpleType" << endl;
                return false;
            }
        }
    }
    else
    {
        cout << "simpleType中错误的子元素" << endl;
        return false;
    }

    return true;
}

bool attrTypeParse(XmlBinTree& xbt, XsdAttrTypeNode& node)
{
    pugi::xml_object_range<pugi::xml_attribute_iterator> range = 
        node.m_node.attributes();

    for (pugi::xml_attribute_iterator itor = range.begin(); itor != range.end();
            itor ++)
    {
        if (0 == strcmp(itor->name(), "type"))
        {   
            //内部数据类型
            if (validateNS(itor->value(), xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen))
            {
                //查找类型校验
                if(g_typeValis.count(itor->value()+xbt.m_iXSLen+1))
                    node.m_pSmp = new XsdSmpTypeNode(
                            g_typeValis[itor->value()+xbt.m_iXSLen+1]);
                else
                {
                    cout << "错误的type属性值" << endl;
                    return false;
                }
            }
            else //引用其他的simpleType
            {
                string sTmp(xbt.m_sNsPrefix);
                sTmp += ":simpleType";
                pugi::xml_node pugiNodeTmp = xbt.m_rootNode.find_child_by_attribute(
                        sTmp.c_str(), "name", itor->value());
                if (!pugiNodeTmp.empty() && validateNS(pugiNodeTmp.name(), 
                            xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen))
                {
                    //可能已经解析
                    if (xbt.m_handledNode.count(pugiNodeTmp.hash_value()))
                        node.m_pSmp = (XsdSmpTypeNode *)xbt.m_handledNode[
                            pugiNodeTmp.hash_value()];
                    else
                    {
                        XsdSmpTypeNode* pNodeTmp = new XsdSmpTypeNode(pugiNodeTmp);
                        xbt.m_handledNode[pugiNodeTmp.hash_value()] = pNodeTmp;
                        node.m_pSmp = pNodeTmp;
                        //递归调用
                        return smpTypeParse(xbt, *pNodeTmp);
                    }
                }
                else
                {
                    cout << "未找到type属性值指定的simpleType" << endl;
                    return false;
                }
            }
        }
        else if (0 == strcmp(itor->name(), "ref")) //引用其他的attribute
        {
            string sTmp(xbt.m_sNsPrefix);
            sTmp += ":attribute";
            pugi::xml_node pugiNodeTmp = xbt.m_rootNode.find_child_by_attribute(
                    sTmp.c_str(), "name", itor->value());
            if (!pugiNodeTmp.empty() && validateNS(pugiNodeTmp.name(), 
                        xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen))
            {
                //可能已经解析
                if (xbt.m_handledNode.count(pugiNodeTmp.hash_value()))
                    node.m_pRef = (XsdAttrTypeNode*)xbt.m_handledNode[
                        pugiNodeTmp.hash_value()];
                else
                {
                    XsdAttrTypeNode* pNodeTmp = new XsdAttrTypeNode(pugiNodeTmp);
                    xbt.m_handledNode[pugiNodeTmp.hash_value()] = pNodeTmp;
                    node.m_pRef = pNodeTmp;
                    //递归调用
                    return attrTypeParse(xbt, *pNodeTmp);
                }
            }
            else
            {
                cout << "未找到ref属性值指定的attribute" << endl;
                return false;
            }
        }
        else //其他标签不处理
            continue;
    }

    pugi::xml_node pugiNodeTmp = node.m_node.child("simpleType");
    if (!pugiNodeTmp.empty())
    {
        if (node.m_pSmp || node.m_pRef)
        {
            cout << "attribute的属性值ref或type不能与子元素simpleType并存" << endl;
            return false;
        }
        else
        {
            XsdSmpTypeNode* pNodeTmp = new XsdSmpTypeNode(pugiNodeTmp);
            //attribute的simpleType子元素同样由m_handledNode管理
            xbt.m_handledNode[pugiNodeTmp.hash_value()] = pNodeTmp;
            node.m_pSmp = pNodeTmp;

            return smpTypeParse(xbt, *pNodeTmp);
        }
    }
    else
    {
        if (!(node.m_pSmp || node.m_pRef))
        {
            cout << "attribute的属性值ref、type与子元素simpleType至少要有一个" << endl;
            return false;
        }
    }

    return true;
}

bool eltTypeParse(XmlBinTree& xbt, XsdElementNode& node);

bool cmxTypeParse(XmlBinTree& xbt, XsdCmxTypeNode& node)
{
    pugi::xml_object_range<pugi::xml_node_iterator> range = node.m_node.children();

    for (pugi::xml_node_iterator itor = range.begin(); itor != range.end(); itor ++)
    {
        if (validateNS(itor->value(), xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen))
        {
            const char *pSz = itor->value()+xbt.m_iXSLen+1;

            if (0==strcmp(pSz, "sequence") || 0==strcmp(pSz, "all") ||
                    0==strcmp(pSz, "option")) //三个可以相同对待
            {
                pugi::xml_object_range<pugi::xml_node_iterator> range2 = itor->children();
                for (pugi::xml_node_iterator itor2 = range2.begin(); itor2 != range2.end();
                        itor2 ++)
                {
                    if (validateNS(itor2->value(), xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen) 
                            && 0==strcmp(itor2->name()+xbt.m_iXSLen+1, "element"))
                    {
                        XsdElementNode *pNodeTmp = new XsdElementNode(*itor2);
                        xbt.m_handledNode[itor2->hash_value()] = pNodeTmp;
                        //层级下降
                        pNodeTmp->m_iLevel++;
                        if (!eltTypeParse(xbt, *pNodeTmp))
                        {
                            cout << "element解析失败" << endl;
                            return false;
                        }
                        node.m_qElts.push(pNodeTmp);
                    }
                    else
                    {
                        cout << "complexType的此类型子元素不支持" << endl;
                        continue;
                    }
                }
            }
            else if (0==strcmp(pSz, "attribute"))
            {
                XsdAttrTypeNode *pNodeTmp = new XsdAttrTypeNode(*itor);
                xbt.m_handledNode[itor->hash_value()] = pNodeTmp;
                if (!attrTypeParse(xbt, *pNodeTmp))
                {
                    cout << "attribute解析失败" << endl;
                    return false;
                }
                node.m_qAttrs.push(pNodeTmp);
            }
            else
            {
                cout << "complexType的此类型子元素不支持" << endl;
                continue;
            }
        }
        else
        {
            cout << "complexType的子元素标签错误" << endl;
            return false;
        }
    }

    return true;
}

bool eltTypeParse(XmlBinTree& xbt, XsdElementNode& node)
{
    pugi::xml_object_range<pugi::xml_attribute_iterator> range = 
        node.m_node.attributes();

    for (pugi::xml_attribute_iterator itor = range.begin(); itor != range.end();
            itor ++)
    {
        if (0 == strcmp(itor->name(), "type"))
        {   
            //内部数据类型
            if (validateNS(itor->value(), xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen))
            {
                //查找类型校验
                if(g_typeValis.count(itor->value()+xbt.m_iXSLen+1))
                    node.m_pType = new XsdSmpTypeNode(
                            g_typeValis[itor->value()+xbt.m_iXSLen+1]);
                else
                {
                    cout << "错误的type属性值" << endl;
                    return false;
                }
            }
            else //引用其他的simpleType或complexType
            {
                string sTmp(xbt.m_sNsPrefix);
                sTmp += ":simpleType";
                pugi::xml_node pugiNodeTmp = xbt.m_rootNode.find_child_by_attribute(
                        sTmp.c_str(), "name", itor->value());

                if (pugiNodeTmp.empty())
                {
                    sTmp = xbt.m_sNsPrefix;
                    sTmp += "complexType";
                    pugiNodeTmp = xbt.m_rootNode.find_child_by_attribute(
                            sTmp.c_str(), "name", itor->value());

                    if (pugiNodeTmp.empty())
                    {
                        cout << "未找到type属性值指定的simpleType或complexType" << endl;
                        return false;
                    }
                    node.m_isSmp = false;
                }

                if (validateNS(pugiNodeTmp.name(), xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen))
                {
                    //可能已经解析
                    if (xbt.m_handledNode.count(pugiNodeTmp.hash_value()))
                        node.m_pType = xbt.m_handledNode[pugiNodeTmp.hash_value()];
                    else
                    {
                        if (node.m_isSmp)
                        {
                            XsdSmpTypeNode* pNodeTmp = new XsdSmpTypeNode(pugiNodeTmp);
                            xbt.m_handledNode[pugiNodeTmp.hash_value()] = pNodeTmp;
                            node.m_pType = pNodeTmp;

                            if(!smpTypeParse(xbt, *pNodeTmp))
                            {
                                cout << "type属性值指定的simpleType解析失败" << endl;
                                return false;
                            }
                        }
                        else
                        {
                            XsdCmxTypeNode * pNodeTmp = new XsdCmxTypeNode(pugiNodeTmp);
                            xbt.m_handledNode[pugiNodeTmp.hash_value()] = pNodeTmp;
                            node.m_pType = pNodeTmp;

                            if(!cmxTypeParse(xbt, *pNodeTmp))
                            {
                                cout << "type属性值指定的complexType解析失败" << endl;
                                return false;
                            }
                        }
                    }
                }
                else
                {
                    cout << "未找到type属性值指定的simpleType" << endl;
                    return false;
                }
            }
        }
        else if (0 == strcmp(itor->name(), "ref")) //引用其他的element
        {
            string sTmp(xbt.m_sNsPrefix);
            sTmp += ":element";
            pugi::xml_node pugiNodeTmp = xbt.m_rootNode.find_child_by_attribute(
                    sTmp.c_str(), "name", itor->value());
            if (!pugiNodeTmp.empty() && validateNS(pugiNodeTmp.name(), 
                        xbt.m_sNsPrefix.c_str(), xbt.m_iXSLen))
            {
                //可能已经解析
                if (xbt.m_handledNode.count(pugiNodeTmp.hash_value()))
                {
                    node.m_pRef = (XsdElementNode *)xbt.m_handledNode[
                        pugiNodeTmp.hash_value()];
                    //被引用的层级下降，不被引用的只能是根element
                    node.m_pRef->m_iLevel++;
                    node.m_isSmp = node.m_pRef->m_isSmp;
                }
                else
                {
                    XsdElementNode* pNodeTmp = new XsdElementNode(pugiNodeTmp);
                    xbt.m_handledNode[pugiNodeTmp.hash_value()] = pNodeTmp;
                    node.m_pRef = pNodeTmp;
                    //被引用的层级下降
                    node.m_pRef->m_iLevel++;
                    //递归调用
                    return eltTypeParse(xbt, *pNodeTmp);
                }
            }
            else
            {
                cout << "未找到ref属性值指定的element" << endl;
                return false;
            }
        }
        else //其他标签不处理
            continue;
    }

    //查看子元素
    if (node.m_pType && node.m_pRef)
    {
        cout << "element的属性type和ref不能同时存在" << endl;
        return false;
    }
    else if (node.m_pType || node.m_pRef)
    {
        if (!node.m_node.child("simpleType").empty() || 
                !node.m_node.child("complexType").empty())
        {
            cout << "element的属性值ref或type与子元素simpleType或complexType不能同时存在" << endl;
            return false;
        }
    }

    pugi::xml_node pugiNodeTmp = node.m_node.child("simpleType");
    if (!pugiNodeTmp.empty()) //自定义的简单类型
    {
        XsdSmpTypeNode* pNodeTmp = new XsdSmpTypeNode(pugiNodeTmp);
        xbt.m_handledNode[pugiNodeTmp.hash_value()] = pNodeTmp;
        node.m_pType = pNodeTmp;
        //递归调用
        return smpTypeParse(xbt, *pNodeTmp);
    }
    else
    {
        pugiNodeTmp = node.m_node.child("complexType");
        if (!pugiNodeTmp.empty()) //自定义的复杂类型
        {
            XsdCmxTypeNode* pNodeTmp = new XsdCmxTypeNode(pugiNodeTmp);
            xbt.m_handledNode[pugiNodeTmp.hash_value()] = pNodeTmp;
            node.m_pType = pNodeTmp;
            //递归调用
            return cmxTypeParse(xbt, *pNodeTmp);
        }
        else
        {
            cout << "element的属性值ref、type与子元素simpleType或complexType至少要有一个" << endl;
            return false;
        }
    }

    return true;
}

XsdElementNode* delEltRef(XsdElementNode* pNode)
{
    if (pNode->m_pRef)
        return delEltRef(pNode->m_pRef);
    else
        return pNode;
}

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
    initValidatorMap();
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

    bool isValid = true;
    XmlBinTree xbt = XmlBinTree(doc.first_child());
    string sSN(xbt.m_rootNode.name());

    //获取schema标签ns
    if (strstr(sSN.c_str(), "schema"))
    {
        if (0 != strcmp(sSN.c_str(), "schema"))
        {
            size_t iPos = sSN.find(":");
            if (iPos == string::npos || 0 != strcmp(sSN.c_str()+iPos+1, "schema"))
            {
                cout << "错误的XML格式" << endl;
                return -1;
            }
            xbt.m_sNsPrefix = string(sSN.c_str(), iPos);
        }

        string sTmp = "xmlns:" + xbt.m_sNsPrefix;
        if (0 != strcmp(xbt.m_rootNode.attribute(sTmp.c_str()).value(), 
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
    pugi::xml_attribute attrTmp =  xbt.m_rootNode.attribute("targetNamespace");
    if (attrTmp.empty())
        cout << "未定义targetNamespace" << endl;
    else
        xbt.m_sTargetNs = attrTmp.value();

    xbt.m_iXSLen = xbt.m_sNsPrefix.length();
    pugi::xml_node nodeTmp;
    pugi::xml_node loopNode = xbt.m_rootNode.first_child();


    while(!loopNode.empty())
    {
        //防止重复处理
        if(xbt.m_handledNode.count(loopNode.hash_value()))
        {
            loopNode = loopNode.next_sibling();
            continue;
        }

        if (!strcmp(loopNode.name()+xbt.m_iXSLen, ":element")) //元素
        {
            XsdElementNode *pNodeTmp = new XsdElementNode(loopNode);
            xbt.m_handledNode[loopNode.hash_value()] = pNodeTmp;

            if (eltTypeParse(xbt, *pNodeTmp))
                return -1;
        }
        else if (!strcmp(loopNode.name()+xbt.m_iXSLen, ":simpleType")) //简单类型
        {
            XsdSmpTypeNode* pNodeTmp = new XsdSmpTypeNode(loopNode);
            xbt.m_handledNode[loopNode.hash_value()] = pNodeTmp;

            if (smpTypeParse(xbt, *pNodeTmp))
                return -1;
        }
        else if (!strcmp(loopNode.name()+xbt.m_iXSLen, ":attribute")) //属性
        {
            XsdAttrTypeNode* pNodeTmp = new XsdAttrTypeNode(loopNode);
            xbt.m_handledNode[loopNode.hash_value()] = pNodeTmp;

            if (attrTypeParse(xbt, *pNodeTmp))
                return -1;
        }
        else if (!strcmp(loopNode.name()+xbt.m_iXSLen, ":complexType")) //复杂类型
        {
            XsdCmxTypeNode* pNodeTmp = new XsdCmxTypeNode(loopNode);
            xbt.m_handledNode[loopNode.hash_value()] = pNodeTmp;

            if (cmxTypeParse(xbt, *pNodeTmp))
                return -1;
        }
        else if (!strcmp(loopNode.name()+xbt.m_iXSLen, ":group")) //元素数组
        {
            //TODO
        }
        else if (!strcmp(loopNode.name()+xbt.m_iXSLen, ":attributeGroup")) //属性组
        {
            //TODO
        }
        else if (!strcmp(loopNode.name()+xbt.m_iXSLen, ":annotation")) //注释
        {
            //TODO
        }
        else if (!strcmp(loopNode.name()+xbt.m_iXSLen, ":notation")) //非XML数据
        {
            //TODO
        }
        else
        {
            cout << "错误的XML格式" << endl;
            return -1;
        }

        loopNode = loopNode.next_sibling();
    }

    //根据处理结果构造XML文件，先找到根结点
    for (std::map<size_t, XsdNodeBase*>::iterator itor = xbt.m_handledNode.begin();
            itor != xbt.m_handledNode.end(); itor ++)
    {
        XsdElementNode* nodeTmp = dynamic_cast<XsdElementNode*>(itor->second);
        if (nodeTmp && !nodeTmp->m_isSmp && nodeTmp->m_iLevel == 0)
        {
            if (xbt.m_pRoot)
            {
                cout << "错误的XML格式" << endl;
                return -1;
            }
            else
                xbt.m_pRoot = nodeTmp;

            break;
        }
    }

    //创建关联
    XsdElementNode* pEltNodeTmp = delEltRef(xbt.m_pRoot);
    XsdCmxTypeNode* pCmxNodeTmp = (XsdCmxTypeNode *)(xbt.m_pRoot->m_pType);

    //转化为XML文件
    pugi::xml_document docOut;
    docOut.append_child();

    doc.print(std::cout);

    if (!isValid) 
    {
        cout << "xml文件格式错误" << endl;
        return -1;
    }


    return 0;
}

