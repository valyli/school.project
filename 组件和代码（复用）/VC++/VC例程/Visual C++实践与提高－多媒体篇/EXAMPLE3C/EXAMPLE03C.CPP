/***************************************************/
/*				编程实例：空心字的输出				*/
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
	pWnd->Create(NULL, "Example3C");

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
	//获得窗口的客户区设备上下文句柄
	CPaintDC dc(this);

	//设置背景
	dc.SetBkMode(TRANSPARENT);

	//获得窗口用户区的大小
	CRect rc;
	GetClientRect(rc);

	//更改当前字体,创建字体对象
	LOGFONT lf;
	dc.GetCurrentFont()->GetLogFont(&lf);
	CFont font, *pOldFont;
	
	lf.lfCharSet=134;
	lf.lfHeight=-100;
	lf.lfWidth=0;
	strcpy(lf.lfFaceName, "隶书");
	font.CreateFontIndirect(&lf);
	pOldFont=dc.SelectObject(&font);
	
	//获得字符串 "多媒体文本"输出时的宽度和高度
	CSize sz=dc.GetOutputTextExtent("多媒体文本");
	
	//更改当前画笔
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0)), *pOldPen;
	pOldPen=dc.SelectObject(&pen);
	
	//更改当前刷子
	CBrush br(HS_DIAGCROSS, RGB(0, 255, 255)), *pOldBrush;
	pOldBrush=dc.SelectObject(&br);
	
	//开始一个路径
	dc.BeginPath();
	dc.TextOut( rc.right/2-sz.cx/2,rc.bottom/2-sz.cy/2, "多媒体文本");
	dc.EndPath();
	
	//绘制路径
	dc.StrokeAndFillPath();

	//恢复设备上下文的原有设置
	dc.SelectObject(pOldFont);
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}
