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



//��Ҫ��������Xecro-c++�е�һЩ�����ϵ�����
//1�����ļ�
//2��д�ļ�
//3�������ת��
int main(int argc, char* argv[])
{
	printf("Start Test Read XML!\n");

	//��ʼ������ƽ̨��أ���WIN32�±���ִ�д˲���
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

	//��ʼ������ƽ̨�޹أ������ӿڶ���
	DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("LS"));
	//��ȡ����������
	DOMBuilder* dbf = ((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	//����һ���ĵ�
	DOMDocument* doc = dbf->parseURI(XMLString::transcode("Test.xml"));

	//��ȡ�ĵ��ĸ����
	//�����һ�����ļ�ʧ�ܣ��ͻ����ⲽ�ڴ汨��
	DOMElement* root = doc->getDocumentElement();

	//ʾ���ҽ��
	DOMNode* node = root->getFirstChild();
	node = node->getNextSibling();


	//ʾ������һ�ý����
    DOMElement*  prodElem = doc->createElement(XMLString::transcode("product"));
    root->appendChild(prodElem);

    DOMText*    prodDataVal = doc->createTextNode(XMLString::transcode("Xerces-C"));
    prodElem->appendChild(prodDataVal);

    DOMElement*  catElem = doc->createElement(XMLString::transcode("category"));
    root->appendChild(catElem);

    catElem->setAttribute(XMLString::transcode("idea"), XMLString::transcode("great"));
printf("Test Transcoder.......................\n");

	DOMText*    catDataVal = doc->createTextNode(
				XMLString::transcode("XML ����Parsing Tools")
		);
    catElem->appendChild(catDataVal);




    DOMElement*  devByElem = doc->createElement(XMLString::transcode("developedBy"));
    root->appendChild(devByElem);

    DOMText*    devByDataVal = doc->createTextNode(XMLString::transcode("Apache Software Foundation"));
    devByElem->appendChild(devByDataVal);	

	//����XML��
	GetChilds(root);





	//д�ļ����ҿ�д����
	doc->setEncoding(XMLString::transcode("gb2312"));
	DOMWriter* theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

	theSerializer->setEncoding(XMLString::transcode("gb2312"));
	doc->setActualEncoding(XMLString::transcode("gb2312"));
	//����������ļ�����
	XMLFormatTarget *FormTarget = new LocalFileFormatTarget(XMLString::transcode("TT.xml"));

	//�����������Ļ����
	//XMLFormatTarget *FormTarget = new StdOutFormatTarget();
	//����������ļ�����
	XMLFormatter *formatter = new XMLFormatter(XMLString::transcode("gb2312"), FormTarget);

	//��XML�����д����
	theSerializer->writeNode(FormTarget, *doc);		//�˴���дdoc��root��node

	theSerializer->release();
	delete FormTarget;
	delete formatter;
	printf("end");



	//��ֹ����ƽ̨��أ���WIN32�±���ִ�д˲���
	XMLPlatformUtils::Terminate();
	return 0;
}

