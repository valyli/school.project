// TestXmlRead.cpp : Defines the entry point for the console application.
//

#include <iostream.h>
#include <stdio.h>

#include "StrTransformer.h"






void GetChilds(DOMNode* node);


void GetChild(DOMNode* node)
{
	StrTransformer tran_str("gb2312");
	if(node->getNodeType() == DOMNode::TEXT_NODE)
	{
//		if(strcmp(tran_str.ChangeStr(node->getNodeValue()), "#text") != 0)
			printf("VALUE: %s\n", XMLString::transcode(node->getNodeValue()));
	}
	else
		printf("NODE: %s\n", tran_str.ChangeStr(node->getNodeName()));
	GetChilds(node);
	return;
}


void GetChilds(DOMNode* node)
{
	DOMNodeList* node_list = node->getChildNodes();
	for(XMLSize_t i = 0; i < node_list->getLength(); i++)
	{
		GetChild(node_list->item(i));
	}
	return;
}



//主要用于试验Xecro-c++中的一些处理上的问题
//1、都文件
//2、写文件
//3、编码的转换
int main(int argc, char* argv[])
{
	printf("Start Test Read XML!\n");

	//初始化，与平台相关，在WIN32下必须执行此步骤
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch)
	{
		char* message = XMLString::transcode(toCatch.getMessage());
		cout << "Error during initialization! :\n"
		<< message << "\n";
		XMLString::release(&message);
		return 1;
	}

	//初始化，与平台无关，创建接口对象
	DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("LS"));
	//获取解析器对象
	DOMBuilder* dbf = ((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	//读入一个文档
	DOMDocument* doc = dbf->parseURI(XMLString::transcode("Test.xml"));

	//获取文档的根结点
	//如果上一步读文件失败，就会在这步内存报错
	DOMElement* root = doc->getDocumentElement();

	//示例找结点
	DOMNode* node = root->getFirstChild();
	node = node->getNextSibling();


	//示例创建一棵结点树
    DOMElement*  prodElem = doc->createElement(XMLString::transcode("product"));
    root->appendChild(prodElem);

    DOMText*    prodDataVal = doc->createTextNode(XMLString::transcode("Xerces-C"));
    prodElem->appendChild(prodDataVal);

    DOMElement*  catElem = doc->createElement(XMLString::transcode("category"));
    root->appendChild(catElem);

    catElem->setAttribute(XMLString::transcode("idea"), XMLString::transcode("great"));
printf("Test Transcoder.......................\n");

	DOMText*    catDataVal = doc->createTextNode(
				XMLString::transcode("XML 中文Parsing Tools")
		);
    catElem->appendChild(catDataVal);




    DOMElement*  devByElem = doc->createElement(XMLString::transcode("developedBy"));
    root->appendChild(devByElem);

    DOMText*    devByDataVal = doc->createTextNode(XMLString::transcode("Apache Software Foundation"));
    devByElem->appendChild(devByDataVal);	

	//遍历XML树
	GetChilds(root);





	//写文件，且可写中文
	doc->setEncoding(XMLString::transcode("gb2312"));
	DOMWriter* theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

	theSerializer->setEncoding(XMLString::transcode("gb2312"));
	doc->setActualEncoding(XMLString::transcode("gb2312"));
	//建立输出到文件的流
	XMLFormatTarget *FormTarget = new LocalFileFormatTarget(XMLString::transcode("TT.xml"));

	//建立输出到屏幕的流
	//XMLFormatTarget *FormTarget = new StdOutFormatTarget();
	//建立输出到文件的流
	XMLFormatter *formatter = new XMLFormatter(XMLString::transcode("gb2312"), FormTarget);

	//将XML结点树写入流
	theSerializer->writeNode(FormTarget, *doc);		//此处可写doc、root、node

	theSerializer->release();
	delete FormTarget;
	delete formatter;
	printf("end");



	//终止，与平台相关，在WIN32下必须执行此步骤
	XMLPlatformUtils::Terminate();
	return 0;
}

