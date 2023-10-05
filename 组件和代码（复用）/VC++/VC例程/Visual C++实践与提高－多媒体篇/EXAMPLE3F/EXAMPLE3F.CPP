/***************************************************/
/*				编程实例：光栅模式文本的输出		*/
/***************************************************/
#include "afxwin.h"
#include "afxext.h"
#include "math.h"

//派生应用程序类
class CMyApp : public CWinApp
{
public:
	//初始化应用程序实例
	virtual BOOL InitInstance();
};

//派生窗口类
class CMyWnd : public CFrameWnd
{
public:

protected:
	//消息处理函数
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP();
};

//初始化应用程序实例
BOOL CMyApp::InitInstance()
{
	//创建应用程序的主窗口，显示标题名称
	CMyWnd *pWnd=new CMyWnd;
	pWnd->Create(NULL, "Example3F");

	//显示应用程序主窗口并更新其客户区
	pWnd->ShowWindow(SW_SHOW);
	pWnd->UpdateWindow();

	//在主窗口关闭时终止应用程序的执行线程
	m_pMainWnd=pWnd;
	return TRUE;
}

//声明唯一的应用程序对象MyApp
CMyApp MyApp;

//应用程序主窗口的消息映射
BEGIN_MESSAGE_MAP(CMyWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

//应用程序主窗口的绘图输出函数
void CMyWnd::OnPaint()
{
	//获得客户区窗口设备的上下文句柄
	CPaintDC dc(this);

	//获得窗口用户区的大小
	CRect rc;
	GetClientRect(rc);
	
	LOGFONT lf;
	dc.GetCurrentFont()->GetLogFont(&lf);
	CFont font1, font2, *pOldFont;
	
	//创建字体font2
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfWidth=0;
	lf.lfHeight=-16;
	strcpy(lf.lfFaceName, "宋体");
	font2.CreateFontIndirect(&lf);
	
	//创建字体font1
	lf.lfHeight=-55;
	lf.lfWeight=700;
	strcpy(lf.lfFaceName, "隶书");
	font1.CreateFontIndirect(&lf);
	
	pOldFont=dc.SelectObject(&font1);
	dc.SetBkMode(TRANSPARENT);
	
	//更改当前画笔
	CPen pen1(PS_NULL, 1, RGB(0, 0, 0)), pen2(PS_SOLID, 1, RGB(0, 0, 0)), *pOldPen;
	pOldPen=dc.SelectObject(&pen1);
	
	
	//更改当前刷子
	CBrush br(RGB(0, 255, 0)), *pOldBrush;
	pOldBrush=dc.SelectObject(&br);
	
	//绘制背景
	for (int i=0; i<rc.right; i+=100)
	{
		for (int j=-10; j<rc.bottom; j+=100)
		{
			dc.Rectangle(i, j, i+50, j+50);
			dc.Rectangle(i+50, j+50, i+100, j+100);
		}
	}
	
	dc.SelectObject(&pen2);
	int iDrawModes[16]={R2_BLACK, R2_WHITE, R2_NOP,
				R2_NOT, R2_COPYPEN, R2_NOTCOPYPEN,
				R2_MERGEPENNOT, R2_MASKPENNOT, R2_MERGENOTPEN,
				R2_MASKNOTPEN, R2_MERGEPEN, R2_NOTMERGEPEN, 
				R2_MASKPEN, R2_NOTMASKPEN, R2_XORPEN,
				R2_NOTXORPEN
			};
	char *strDrawModes[16]={"R2_BLACK", "R2_WHITE", "R2_NOP",
				"R2_NOT", "R2_COPYPEN", "R2_NOTCOPYPEN",
				"R2_MERGEPENNOT", "R2_MASKPENNOT", "R2_MERGENOTPEN",
				"R2_MASKNOTPEN", "R2_MERGEPEN", "R2_NOTMERGEPEN", 
				"R2_MASKPEN", "R2_NOTMASKPEN", "R2_XORPEN",
				"R2_NOTXORPEN"
			};

	for (i=0; i<16; i++)
	{
		//更改当前绘图模式，绘制字体的前景
		dc.SetBkMode(TRANSPARENT);
		dc.SetROP2(iDrawModes[i]);
		dc.BeginPath();
		dc.SelectObject(&font1);
		dc.TextOut((i%4)*150+10, (i/4)*80+10, "人生");
		dc.EndPath();
		dc.FillPath();
		//以 R2_BLACK绘图模式绘制字体的轮廓
		dc.SetROP2(R2_BLACK);
		dc.BeginPath();
		dc.TextOut((i%4)*150+10, (i/4)*80+10, "人生");
		dc.EndPath();
		dc.StrokePath();
		//显示所使用的绘图模式
		dc.SelectObject(&font2);
		dc.SetBkMode(OPAQUE);
		dc.TextOut((i%4)*150+10, (i/4)*80+70, strDrawModes[i]);
	}

	// 恢复设备上下文的原有设置
	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}