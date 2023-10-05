//导入用Xecro-c处理XML要用到的头文件
//以其开发包解压缩后的include目录为根

#if !defined(_ForXecro_H_LIJIA_2003_05_22_)
#define _ForXecro_H_LIJIA_2003_05_22_

//设定在WIN32平台下编译
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
//在WIN32平台下必须加入
#if defined(_WIN32_Platform_ForXecro_H_)

#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/util/Transcoders/Win32/Win32TransService.hpp>

XERCES_CPP_NAMESPACE_USE



#endif//_WIN32_Platform_ForXecro_H_
////////////////////////////////////////////////////////////////////////////


#endif//_ForXecro_H_LIJIA_2003_05_22_