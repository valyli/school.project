// HzGL.h: interface for the CHzGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HZGL_H__FC9C6828_CEB8_11D4_9034_F00952C10000__INCLUDED_)
#define AFX_HZGL_H__FC9C6828_CEB8_11D4_9034_F00952C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHzGL  
{
public:
	CHzGL();
	~CHzGL();
	bool Render() ;
	bool Create(CWnd* pWnd); 
	OnResize(int cx, int cy);//窗口大小发生变化时调用

private:
	
	spin();//旋转函数
	bool OnInit() ;
	CString m_theString ;
	CString m_String;
	BYTE FTextList[128]; 
	void Create3DFont() ;
	CDC* m_pdc;
	// 包含字形特性的位置和方向...
	GLYPHMETRICSFLOAT m_agmf1[128]; 
	GLYPHMETRICSFLOAT m_agmf2[40] ;
	//用于OPenGL显示的字体
	CFont fontOpenGL1,fontOpenGL2;
	CSize m_angle;//旋转角度0-360
	HGLRC m_hrc ; //OpenGL Rendering Context
	int m_iDisplayListStart1;
	int m_iDisplayListStart2;
};

#endif // !defined(AFX_HZGL_H__FC9C6828_CEB8_11D4_9034_F00952C10000__INCLUDED_)
