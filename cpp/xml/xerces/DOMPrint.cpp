/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * $Id: DOMPrint.cpp 1801549 2017-07-11 00:18:21Z scantor $
 */

// ---------------------------------------------------------------------------
//  This sample program invokes the XercesDOMParser to build a DOM tree for
//  the specified input file. It then invokes DOMLSSerializer::write() to
//  serialize the resultant DOM tree back to XML stream.
//
//  Note:
//  Application needs to provide its own implementation of
//		   DOMErrorHandler (in this sample, the DOMPrintErrorHandler),
//		   if it would like to receive notification from the serializer
//		   in the case any error occurs during the serialization.
//
//  Application needs to provide its own implementation of
//		   DOMLSSerializerFilter (in this sample, the DOMPrintFilter),
//		   if it would like to filter out certain part of the DOM
//		   representation, but must be aware that thus may render the
//		   resultant XML stream invalid.
//
//  Application may choose any combination of characters as the
//		   end of line sequence to be used in the resultant XML stream,
//		   but must be aware that thus may render the resultant XML
//		   stream ill formed.
//
//  Application may choose a particular encoding name in which
//		   the output XML stream would be, but must be aware that if
//		   characters, unrepresentable in the encoding specified, appearing
//		   in markups, may force the serializer to terminate serialization
//		   prematurely, and thus no complete serialization would be done.
//
//  Application shall query the serializer first, before set any
//           feature/mode(true, false), or be ready to catch exception if this
//           feature/mode is not supported by the serializer.
//
//  Application needs to clean up the filter, error handler and
//		   format target objects created for the serialization.
//
//   Limitations:
//      1.  The encoding="xxx" clause in the XML header should reflect
//          the system local code page, but does not.
//      2.  Cases where the XML data contains characters that can not
//          be represented in the system local code page are not handled.
//
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <cstdio>
#include <cstring>

#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/XMLSchemaDescription.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "DOMTreeErrorReporter.hpp"
#include "DOMPrintFilter.hpp"
#include "DOMPrintErrorHandler.hpp"
#include <xercesc/util/OutOfMemoryException.hpp>

#include <string.h>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::cerr;
using std::string;

// ---------------------------------------------------------------------------
//  Local data
//
//  gXmlFile
//      The path to the file to parser. Set via command line.
//
//  gDoNamespaces
//      Indicates whether namespace processing should be done.
//
//  gDoSchema
//      Indicates whether schema processing should be done.
//
//  gSchemaFullChecking
//      Indicates whether full schema constraint checking should be done.
//
//  gDoCreate
//      Indicates whether entity reference nodes needs to be created or not
//      Defaults to false
//
//  gOutputEncoding
//      The encoding we are to output in. If not set on the command line,
//      then it is defaults to the encoding of the input XML file.
//
//  gSplitCdataSections
//      Indicates whether split-cdata-sections is to be enabled or not.
//
//  gDiscardDefaultContent
//      Indicates whether default content is discarded or not.
//
//  gUseFilter
//      Indicates if user wants to plug in the DOMPrintFilter.
//
//  gValScheme
//      Indicates what validation scheme to use. It defaults to 'auto', but
//      can be set via the -v= command.
//
// ---------------------------------------------------------------------------
static char*                    gXmlFile               = 0;
static bool                     gDoNamespaces          = false;
static bool                     gDoSchema              = false;
static bool                     gSchemaFullChecking    = false;
static bool                     gDoCreate              = false;

static char*                    goutputfile            = 0;
static char*                    gXPathExpression       = 0;

// options for DOMLSSerializer's features

static bool                     gSplitCdataSections    = true;
static bool                     gDiscardDefaultContent = true;
static bool                     gUseFilter             = false;
static bool                     gFormatPrettyPrint     = false;
static bool                     gXMLDeclaration        = true;
static bool                     gWriteBOM              = false;

static XercesDOMParser::ValSchemes    gValScheme       = XercesDOMParser::Val_Auto;

//	Prototypes for internally used functions
void usage();


// ---------------------------------------------------------------------------
//
//  Usage()
//
// ---------------------------------------------------------------------------
void usage()
{
    XERCES_STD_QUALIFIER cout << "\nUsage:\n"
            "    DOMPrint [options] <XML file>\n\n"
            "This program invokes the DOM parser, and builds the DOM tree.\n"
            "It then asks the DOMLSSerializer to serialize the DOM tree.\n"
            "Options:\n"
            "    -e          create entity reference nodes. Default is no expansion.\n"
            "    -v=xxx      Validation scheme [always | never | auto*].\n"
            "    -n          Enable namespace processing. Default is off.\n"
            "    -s          Enable schema processing. Default is off.\n"
            "    -f          Enable full schema constraint checking. Defaults is off.\n"
            "    -wenc=XXX   Use a particular encoding for output. Default is\n"
            "                the same encoding as the input XML file. UTF-8 if\n"
            "                input XML file has not XML declaration.\n"
            "    -wfile=xxx  Write to a file instead of stdout.\n"
            "    -wscs=xxx   Enable/Disable split-cdata-sections.      Default on\n"
            "    -wddc=xxx   Enable/Disable discard-default-content.   Default on\n"
            "    -wflt=xxx   Enable/Disable filtering.                 Default off\n"
            "    -wfpp=xxx   Enable/Disable format-pretty-print.       Default off\n"
            "    -wfdecl=xxx Enable/Disable xml-declaration.           Default on\n"
            "    -wbom=xxx   Enable/Disable write Byte-Order-Mark      Default off\n"
            "    -xpath=xxx  Prints only the nodes matching the given XPath.\n"
            "    -?          Show this help.\n\n"
            "  * = Default if not provided explicitly.\n\n"
            "The parser has intrinsic support for the following encodings:\n"
            "    UTF-8, US-ASCII, ISO8859-1, UTF-16[BL]E, UCS-4[BL]E,\n"
            "    WINDOWS-1252, IBM1140, IBM037, IBM1047.\n"
          <<  XERCES_STD_QUALIFIER endl;
}

int readFile(const string &sPath, string &sRes) 
{
    FILE *fptr = fopen(sPath.c_str(), "r");
    if (fptr == NULL)
    {
        cout << ("Cannot open file \n") << endl;
        return -1;
    }

#define GRANULAR 1024

    int iCnt = 1;
    char *pContent = (char *)calloc(GRANULAR * iCnt, sizeof(char));
    unsigned int iCounter = 0;
    char ch = fgetc(fptr);
    while (ch != EOF)
    {
        pContent[iCounter++] = ch;
        if (iCounter == GRANULAR * iCnt)
        {
            ++iCnt;
            char *pTemp = (char *)realloc(pContent, GRANULAR * iCnt * sizeof(char));
            pContent = pTemp;
            memset(&pContent[GRANULAR * (iCnt-1)], 0x00, sizeof(GRANULAR));
        }
        ch = fgetc(fptr);
    }
    fclose(fptr);

    sRes = pContent;
    free(pContent);

    return 0;
}

// ---------------------------------------------------------------------------
//
//  main
//
// ---------------------------------------------------------------------------
int main(int argC, char* argV[])
{
    // Initialize the XML4C2 system
    try
    {
        XMLPlatformUtils::Initialize();
    }

    catch(const XMLException &toCatch)
    {
        cerr << "Error during Xerces-c Initialization.\n"
             << "  Exception message:"
             << StrX(toCatch.getMessage()) << endl;
        return 1;
    }

    gXmlFile = argV[2];

    string sContentIn;
    if (readFile(gXmlFile, sContentIn))
    {
        cout << "打开文件错误" << endl;
        return -1;
    }

    //输入报文检查
    xercesc::MemBufInputSource *pMemBufIn = new xercesc::MemBufInputSource(
            (const XMLByte*)sContentIn.c_str(), sContentIn.length(), "memBufIn");

    XercesDOMParser *parserIn = new XercesDOMParser;

    parserIn->setValidationScheme(XercesDOMParser::Val_Always);       //一直使用schema
    parserIn->setDoNamespaces(true);                                  //需要使用名称空间
    parserIn->setDoSchema(true);                                      //设置是否使用schema
    //parserIn->setHandleMultipleImports (true);                        //设置import多个schema
    //parserIn->setValidationSchemaFullChecking(false);                 //TODO 先放false吧
    //parserIn->setCreateEntityReferenceNodes(false);                   //TODO 先放false吧
    parserIn->setValidationConstraintFatal(true);                     //遇到错误停止
    //parserIn->setExternalNoNamespaceSchemaLocation(argV[1]);      //如果xml不带ns则用这个

    Grammar *pGrammerIn = parserIn->loadGrammar(argV[1], Grammar::SchemaGrammarType, true);
    if (NULL == pGrammerIn) //载入xsd
    {
        std::cout << "导入" << argV[1] << "失败" << std::endl;
        return -1;
    }
    std::string sSchemaLocIn(StrX(pGrammerIn->getTargetNamespace()).localForm());
    sSchemaLocIn += " ";
    sSchemaLocIn += argV[1];
    parserIn->setExternalSchemaLocation(sSchemaLocIn.c_str());

    DOMTreeErrorReporter *errReporter = new DOMTreeErrorReporter();
    parserIn->setErrorHandler(errReporter);

    //输出报文检查
    string sContentOut;
    if (readFile("./11.xml", sContentOut))
    {
        cout << "打开文件错误" << endl;
        return -1;
    }
    xercesc::MemBufInputSource *pMemBufOut = new xercesc::MemBufInputSource(
            (const XMLByte*)sContentOut.c_str(), sContentOut.length(), "memBufOut");

    XercesDOMParser *parserOut = new XercesDOMParser;

    parserOut->setValidationScheme(XercesDOMParser::Val_Never);        //开始不使用
    parserOut->setDoNamespaces(true);                                  //需要使用名称空间
    parserOut->setDoSchema(true);                                      //设置是否使用schema
    parserOut->setValidationConstraintFatal(true);                     //遇到错误停止

    Grammar *pGrammerOut = parserOut->loadGrammar("./3.xsd", 
            Grammar::SchemaGrammarType, true);
    if (NULL == pGrammerOut)
    {
        std::cout << "导入" << "./3.xsd" << "失败" << std::endl;
        return -1;
    }
    std::string sSchemaLocOut(StrX(pGrammerOut->getTargetNamespace()).localForm());
    sSchemaLocOut += " ";
    sSchemaLocOut += "./3.xsd";
    parserOut->setExternalSchemaLocation(sSchemaLocOut.c_str());

    //TODO 先共用一个
    parserOut->setErrorHandler(errReporter);

    //创建序列化类
    XMLCh tempStr[3] = {chLatin_L, chLatin_S, chNull};
    DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
    DOMLSSerializer   *theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();

    DOMErrorHandler *myErrorHandler = new DOMPrintErrorHandler();
    DOMConfiguration* serializerConfig = theSerializer->getDomConfig();
    serializerConfig->setParameter(XMLUni::fgDOMErrorHandler, myErrorHandler);

    //删除默认值，要配合xsd使用不方便啊
//    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true))
//        serializerConfig->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true);

    //不需要优化文档结构
//    if (serializerConfig->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
//        serializerConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

    //添加过滤器
    DOMPrintFilter *pFilter = new DOMPrintFilter(DOMNodeFilter::SHOW_ELEMENT   |
            DOMNodeFilter::SHOW_ATTRIBUTE |
            DOMNodeFilter::SHOW_DOCUMENT_TYPE);
    theSerializer->setFilter(pFilter);

    for (int i = 0; i < 1; i++)
    {
        bool errorsOccured = false;
        try
        {
            parserIn->parse(*pMemBufIn);
        }
        catch (const OutOfMemoryException&)
        {
            cerr << "OutOfMemoryException" << endl;
            errorsOccured = true;
        }
        catch (const XMLException& e)
        {
            cerr << "An error occurred during parsing\n   Message: "
                << StrX(e.getMessage()) << endl;
            errorsOccured = true;
        }
        catch (const DOMException& e)
        {
            const unsigned int maxChars = 2047;
            XMLCh errText[maxChars + 1];

            cerr << "\nDOM Error during parsing: '" << gXmlFile << "'\n"
                << "DOMException code is:  " << e.code << endl;

            if (DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
                cerr << "Message is: " << StrX(errText) << endl;

            errorsOccured = true;
        }
        catch (...)
        {
            cerr << "An error occurred during parsing\n " << endl;
            errorsOccured = true;
        }

        DOMNodeList * pDNodeList = parserIn->getDocument()->
            getElementsByTagName(XMLString::transcode("Id"));

        for (int i=0; i < pDNodeList->getLength(); i++)
        {
            if (pDNodeList->item(i)->getChildNodes()->getLength() == 1 && 
                    strcmp(StrX(pDNodeList->item(i)->getFirstChild()->
                            getNodeName()).localForm(), "#text") == 0) 
            {
                cout << (pDNodeList->item(i)->getNodeType()) << endl;
                //cout << StrX(pDNodeList->item(i)->getTextContent()) << endl;
            }
        }

        try
        {
            parserOut->parse(*pMemBufOut);
        }
        catch (const OutOfMemoryException&)
        {
            cerr << "OutOfMemoryException" << endl;
            errorsOccured = true;
        }
        catch (const XMLException& e)
        {
            cerr << "An error occurred during parsing\n   Message: "
                << StrX(e.getMessage()) << endl;
            errorsOccured = true;
        }
        catch (const DOMException& e)
        {
            const unsigned int maxChars = 2047;
            XMLCh errText[maxChars + 1];

            cerr << "\nDOM Error during parsing: '" << gXmlFile << "'\n"
                << "DOMException code is:  " << e.code << endl;

            if (DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
                cerr << "Message is: " << StrX(errText) << endl;

            errorsOccured = true;
        }
        catch (...)
        {
            cerr << "An error occurred during parsing\n " << endl;
            errorsOccured = true;
        }

        parserOut->setValidationScheme(XercesDOMParser::Val_Always);

        cout << StrX(theSerializer->writeToString(parserOut->getDocument())) << endl;
    }


#if 0
    //根据xsd创建报文
	DOMImplementation* impl =  DOMImplementationRegistry::
        getDOMImplementation(XMLString::transcode("Core"));

	XMLGrammarDescription *pGraDes = pGrammer->getGrammarDescription();
    pGrammer->getElemDecl


	DOMDocument* doc = impl->createDocument(
			0,                    // root element namespace URI.
			X("company"),         // root element name
			0);                   // document type object (DTD).

	DOMElement* rootElem = doc->getDocumentElement();

	DOMElement*  prodElem = doc->createElement(X("product"));
	rootElem->appendChild(prodElem);

	DOMText*    prodDataVal = doc->createTextNode(X("Xerces-C"));
	prodElem->appendChild(prodDataVal);

	DOMElement*  catElem = doc->createElement(X("category"));
	rootElem->appendChild(catElem);

	catElem->setAttribute(X("idea"), X("great"));
#endif

    theSerializer->release();

    //
    //  Clean up the error handler. The parserIn does not adopt handlers
    //  since they could be many objects or one object installed for multiple
    //  handlers.
    //
    delete errReporter;

    //
    //  Delete the parserIn itself.  Must be done prior to calling Terminate, below.
    //
    delete parserIn;
    delete parserOut;

    delete pMemBufIn;
    delete pMemBufOut;

    // And call the termination method
    XMLPlatformUtils::Terminate();

    return 0;
}
