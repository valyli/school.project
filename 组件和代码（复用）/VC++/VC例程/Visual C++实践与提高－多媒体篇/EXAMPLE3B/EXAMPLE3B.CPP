/***************************************************/
/*				编程实例：旋转文本的输出			*/
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
	//获得客户区窗口的设备上下文句柄
	CPaintDC dc(this);
	
	//获得窗口用户区的大小
	CRect rc;
	GetClientRect(rc);
	
	//定义旋转文本
	CString str(_T("......旋转文本输出！"));
	
	//设置背景色和文本的颜色
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,255,50));
	
	//定义字体变量
	CFont font;
	LOGFONT lf;

	//dc.GetCurrentFont()返回指向当前设备上下文所使用的字体的指针
	//GetLogFont将当前字体的信息填入到lf中
	dc.GetCurrentFont()->GetLogFont(&lf);
	
	//设置lf中各个成员的值
	lf.lfHeight = -15;
	lf.lfWeight = FW_NORMAL;
	lf.lfClipPrecision = CLIP_LH_ANGLES;
	strcpy(lf.lfFaceName, "宋体");

	//绘制旋转文本
	for (int i=0;i<3600;i+=360)
	{
		lf.lfEscapement = i;
		//创建字体对象
		font.CreateFontIndirect(&lf);
		//用于保存设备上下文最初使用的字体
		CFont *pOldFont = dc.SelectObject(&font);
		//以用户区的中心为旋转中心
		dc.TextOut(rc.right/2, rc.bottom/2,str);
		dc.SelectObject(pOldFont);
		font.DeleteObject();
	}
}

