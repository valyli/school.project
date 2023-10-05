// HzGL.cpp: implementation of the CHzGL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HzGL.h"
#include <gl\gl.h>
#include <gl\glu.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHzGL::CHzGL()
{
	m_iDisplayListStart1=1000;
	m_iDisplayListStart2=2000;
	m_angle.cx = 0 ;//向下旋转角度初值
	m_angle.cy = 0 ;//左右旋转角度初值 
	m_theString =  " 东风第二动力厂电气主系统运行日志(一)";
	m_String="";
}

bool CHzGL::Create(CWnd* pWnd)
{
		int iPixelType=	PFD_TYPE_RGBA;
		DWORD dwFlags=	PFD_DOUBLEBUFFER   | // 使用双缓冲区
						PFD_SUPPORT_OPENGL | // 使用 OpenGL
						PFD_DRAW_TO_WINDOW;  // 窗口象数格式
	
	//描述图形表面象数格式结构
	PIXELFORMATDESCRIPTOR pfd ;
	memset(&pfd,0, sizeof(PIXELFORMATDESCRIPTOR)) ;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);  
	pfd.nVersion = 1 ;                           // 版本号
	pfd.dwFlags =  dwFlags ;					//象数缓冲区属性
	pfd.iPixelType = iPixelType ;
	pfd.cColorBits = 24 ;						// 24 位颜色
	pfd.cDepthBits = 32 ;						// 32-bit 颜色浓度缓冲区
	pfd.iLayerType = PFD_MAIN_PLANE ;           // Layer type
	
	m_pdc = new CClientDC(pWnd);
	//创建TrueType字体，根据实现需要，可用楷体、琥珀等字体
	LOGFONT lf;
	m_pdc->GetCurrentFont()->GetLogFont(&lf);
	lf.lfCharSet=134;
	strcpy(lf.lfFaceName, "黑体") ;  
	fontOpenGL1.CreateFontIndirect(&lf);
	strcpy(lf.lfFaceName, "宋体") ;  
	fontOpenGL2.CreateFontIndirect(&lf);
	
	//选择与设备描述符（DC）接近的像素格式
	int nPixelFormat = ChoosePixelFormat(m_pdc->m_hDC, &pfd);
	if (nPixelFormat == 0)
	{
		AfxMessageBox("ChoosePixelFormat Failed %d\r\n",GetLastError()) ;
		return false;
	}
	
	// 设置与设备描述符（DC）接近的像素格式
	BOOL bResult = SetPixelFormat(m_pdc->m_hDC, nPixelFormat, &pfd);
	if (!bResult)
	{
		AfxMessageBox("SetPixelFormat Failed %d\r\n",GetLastError()) ;
		return false;
	}
	
	
	//
	// 创建OpenGL绘图上下文-图形操作描述符(rendering context)
	//
	m_hrc = wglCreateContext(m_pdc->m_hDC);
	if (!m_hrc)
	{
		AfxMessageBox("wglCreateContext Failed %x\r\n", GetLastError()) ;
		return false;
	}
	
	//指定rendering context
   	if(!wglMakeCurrent(m_pdc->m_hDC, m_hrc))
	{
		AfxMessageBox("wglMakeCurrent Failed %x\r\n", GetLastError()) ;
		return false;
	}
	//调用成员私有函数-OpenGL初始化
	if(OnInit()) return true;
	else return false;
}

bool CHzGL::OnInit()
{
	// 允许颜色浓度
	glEnable(GL_DEPTH_TEST);  	
	
	// 设置前颜色为材料颜色
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE) ;
	glEnable(GL_COLOR_MATERIAL) ;
	
	// 设置光线位置
	float fLightPosition[3] = {-1.0f, -1.0f, 1.0f} ;
	glLightfv(GL_LIGHT0, GL_POSITION, fLightPosition) ;
	
	// 允许计算光源
	glEnable(GL_LIGHTING) ; 		
	glEnable(GL_LIGHT0) ;			
	
	// 设置屏幕底色
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;//设置底色为黑色
	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f) ;//设置底色为白色
	//float customColor=127/255;
	glClearColor(0.0f,0.5f,0.5f,0.0f);
	Create3DFont(); 
	return true ;
}


void CHzGL::Create3DFont()
{
	int i=0; 
	CFont* pOldFont=(CFont*)m_pdc->SelectObject(&fontOpenGL1);
	
	// 产生显示列表.
	unsigned int j=0; 
	i=0; 
	j=0; 
	while(i< m_theString.GetLength())
	{
		if (IsDBCSLeadByte(m_theString[i])){ //判 断 是 否 为 双 字 节 
			wglUseFontOutlines(m_pdc->m_hDC, // 所选字体的设备描述符
				(256+m_theString[i])*256+(256+m_theString[i+1]),// 要转换为显示列表的第一个字符 
				1, //  转换为显示列表的字符个数
				m_iDisplayListStart1+j, // 指定的显示列表基数 
				0.0,// 指定的最大偏离值，一般为0 
				0.15f, // 它是立体字体具体表现，Z轴（纵深方向）方向的值
				WGL_FONT_POLYGONS,// 显示的字体轮廓线格式，多边形-实心 
				&m_agmf1[j]); // 接受字符特性
			FTextList[j]=j; 
			j++; 
			i++;i++; 
		} 
		else{ 
			wglUseFontOutlines(m_pdc->m_hDC, // 所选字体的设备描述符
				m_theString[i], // 要转换为显示列表的第一个字符 
				1, //  转换为显示列表的字符个数
				m_iDisplayListStart1+j, // 指定的显示列表基数 
				0.0,// 指定的最大偏离值，一般为0 
				0.15f, // 它是立体字体具体表现，Z轴（纵深方向）方向的值
				WGL_FONT_POLYGONS,// 显示的字体轮廓线格式，多边形-实心 
				&m_agmf1[j]); // 接受字符特性
			FTextList[j]=j; 
			i++; 
			j++; 
		} 
	} 
	
	m_pdc->SelectObject(&fontOpenGL2);	
	i=0; 
	j=0; 
    while(i<m_String.GetLength())
	{
		if (IsDBCSLeadByte(m_String[i])){ ///判 断 是 否 为 双 字 节 
			wglUseFontOutlines(m_pdc->m_hDC,// 所选字体的设备描述符 
				(256+m_theString[i])*256+(256+m_theString[i+1]),// 要转换为显示列表的第一个字符 
				1, //  转换为显示列表的字符个数
				m_iDisplayListStart2+j, // 指定的显示列表基数 
				0.0,// 指定的最大偏离值，一般为0 
				0.15f, // 它是立体字体具体表现，Z轴（纵深方向）方向的值
				WGL_FONT_POLYGONS,// 显示的字体轮廓线格式，多边形-实心 
				&m_agmf2[j]); // 接受字符特性
			FTextList[j]=j; 
			j++; 
			i++;i++; 
		} 
		else{ 
			wglUseFontOutlines(m_pdc->m_hDC, // 所选字体的设备描述符
				m_theString[i], // 要转换为显示列表的第一个字符 
				1, //  转换为显示列表的字符个数
				m_iDisplayListStart2+j, // 指定的显示列表基数 
				0.0,// 指定的最大偏离值，一般为0 
				0.15f, // 它是立体字体具体表现，Z轴（纵深方向）方向的值
				WGL_FONT_POLYGONS,// 显示的字体轮廓线格式，多边形-实心 
				&m_agmf2[j]); // 接受字符特性
			FTextList[j]=j; 
			i++; 
			j++; 
		} 
	} 
	
	
	
	if (pOldFont) m_pdc->SelectObject(pOldFont) ;
	
}

CHzGL::~CHzGL()
{
	if (m_hrc) 
	{
		// 删除图形操作描述符
		if (m_hrc == wglGetCurrentContext())
			wglMakeCurrent(NULL,NULL) ; 
		wglDeleteContext(m_hrc) ;
		m_hrc = NULL ;
	}
	
	delete m_pdc;
	
}

bool CHzGL::Render()
{
	// Make the HGLRC current
	wglMakeCurrent(m_pdc->m_hDC, m_hrc);
	//第一个字符串颜色
	static GLdouble purple[3] = {3, 3, 3} ; 
	
	//第二个字符串四个字体不同颜色
	static GLubyte byPink[3] = {196, 0, 196} ;
	static GLubyte byTeal[3] = {0, 153, 168} ;
	static GLubyte byBlue[3] = {42, 38, 215} ;
	static GLubyte byGreen[3] = {0, 171, 82} ;
	
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//显示第一行汉字
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	glTranslated(-9.10,-0.1,-7.0 );//字体位置X,Y,字体大小
	//glRotated(m_angle.cy, 0.0, 1.0, 0.0);
	glRotated(m_angle.cx, 1, 0, 0);//  旋转角度X，Y，Z
	
	glColor3dv(purple) ;
	glListBase(m_iDisplayListStart1); 
	glCallLists(m_theString.GetLength(),GL_UNSIGNED_BYTE,&FTextList); 
	
	//显示第二行汉字
	double widthMN = (m_agmf2[0].gmfCellIncX + m_agmf2[3].gmfCellIncX) * 0.5 ;
	
	glLoadIdentity();
	glTranslated(0.0, -0.65, -3.0 );
	glRotated(m_angle.cy, 0.0, 1.0, 0.0);
	glTranslated(-widthMN, 0.0, 0.0) ;
	
	glScaled(0.5, 0.5, 0.5) ;
	glColor3ubv(byPink) ;
	glCallList(m_iDisplayListStart2) ;
	glColor3ubv(byTeal) ;
	glCallList(m_iDisplayListStart2+1) ;
	glColor3ubv(byBlue) ;			   
	glCallList(m_iDisplayListStart2+2) ;
	glColor3ubv(byGreen) ;
	glCallList(m_iDisplayListStart2+3) ;
	glFlush() ;
	GdiFlush() ;
	SwapBuffers(m_pdc->m_hDC) ;
	GdiFlush() ;
	spin();//调用成员私有函数—旋转增量
	return true;
}
BOOL CHzGL::OnResize(int cx, int cy)
{
	GLdouble gldAspect = (GLdouble) cx/ (GLdouble) cy;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//设置透视发射矩阵
	gluPerspective(30.0, gldAspect, 1.0, 10.0);
	glViewport(0, 0, cx, cy);
	
	return TRUE ;
}

BOOL CHzGL::spin()//旋转函数
{
	m_angle.cx += 10 ;
	m_angle.cy += 10 ;
	if (m_angle.cx >= 360) m_angle.cx = 0 ;
	if (m_angle.cy >= 360) m_angle.cy = 0 ;
}

