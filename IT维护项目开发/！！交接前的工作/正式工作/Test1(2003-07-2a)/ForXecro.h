//������Xecro-c����XMLҪ�õ���ͷ�ļ�
//���俪������ѹ�����includeĿ¼Ϊ��

#if !defined(_ForXecro_H_LIJIA_2003_05_22_)
#define _ForXecro_H_LIJIA_2003_05_22_

//�趨��WIN32ƽ̨�±���
#define _WIN32_Platform_ForXecro_H_

#include <xercesc/dom/deprecated/DOMParser.hpp>
#include <xercesc/dom/deprecated/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>


#include <xercesc/util/XercesVersion.hpp>
#include <xercesc/util/AutoSense.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
  
#include <xercesc/framework/XMLFormatter.hpp>

#include <xercesc/dom/DOM.hpp>


////////////////////////////////////////////////////////////////////////////
//��WIN32ƽ̨�±������
#if defined(_WIN32_Platform_ForXecro_H_)

#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/util/Transcoders/Win32/Win32TransService.hpp>

XERCES_CPP_NAMESPACE_USE



#endif//_WIN32_Platform_ForXecro_H_
////////////////////////////////////////////////////////////////////////////


#endif//_ForXecro_H_LIJIA_2003_05_22_