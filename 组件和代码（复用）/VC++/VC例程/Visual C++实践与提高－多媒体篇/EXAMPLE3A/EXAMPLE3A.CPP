/***************************************************/
/*		编程实例：LOGFONT结构和CFont对象的使用		*/
/***************************************************/
#include "afxwin.h"
#include "afxext.h"
#include "math.h"

//角度转换为弧度
double dTransAngleToRadian(double dAngle);

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
	pWnd->Create(NULL, "Example3A");

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

	//设置字体输出背景为透明
	dc.SetBkMode(TRANSPARENT);

	//获得设备上下文所使用的当前字体
	LOGFONT lf;
	dc.GetCurrentFont()->GetLogFont(&lf);
	
	//定义字体变量
	CFont font1, font2;
	
	//用于保存设备上下文最初使用的字体
	CFont *pOldFont;

	//创建font1为12象素宋体,用于输出说明文字
	lf.lfCharSet=134;
	lf.lfHeight=-14;
	lf.lfWidth=0;
	strcpy(lf.lfFaceName, "宋体");
	font1.CreateFontIndirect(&lf);
	
	//把当前字体更改为20象素的Times New Roman，并且向上倾斜30度
	lf.lfCharSet=0;
	strcpy(lf.lfFaceName, "Times New Roman");
	lf.lfEscapement=300;
	lf.lfHeight=-20;
	font2.CreateFontIndirect(&lf);
	pOldFont=dc.SelectObject(&font2);

	//获得字符串 "倾角为30度" 在输出时的宽度和高度
	CSize sz=dc.GetTextExtent("倾角向上30度");

	//计算字符串合适的输出位置
	dc.TextOut(10, 10+int(sz.cx*sin(dTransAngleToRadian(30))), "倾角向上30度");

	//将字体输出方向更改为向下倾斜 30 度
	lf.lfEscapement=-300;
	dc.SelectObject(pOldFont);
	font2.DeleteObject();
	font2.CreateFontIndirect(&lf);
	dc.SelectObject(&font2);

	// 计算字符串合适的输出位置
	dc.TextOut(300-int(sz.cx*cos(dTransAngleToRadian(30))), 10, "倾角向下30度");

	//对称于直线 x=155 输出字符串 "参数lfEscapement确定角度"
	dc.SelectObject(&font1);
	sz=dc.GetTextExtent("参数lfEscapement确定输出文字角度");
	dc.TextOut(155-sz.cx/2, 110, "参数lfEscapement确定输出文字角度");

	//更改当前字体为最细的 50 象素大小的宋体
	lf.lfCharSet=134;
	strcpy(lf.lfFaceName, "宋体");
	lf.lfEscapement=0;
	lf.lfWeight=0;
	lf.lfHeight=-50;
	dc.SelectObject(pOldFont);
	font2.DeleteObject();
	font2.CreateFontIndirect(&lf);
	dc.SelectObject(&font2);
	dc.TextOut(330, 10, "细");//输出一个"细"字

	//更改当前字体为最粗的 50 象素大小的字体
	lf.lfWeight=1000;
	dc.SelectObject(pOldFont);
	font2.DeleteObject();
	font2.CreateFontIndirect(&lf);
	dc.SelectObject(&font2);
	dc.TextOut(330, 80, "粗");//输出一个"粗"字

	//在旁边使用 12 象素大小的宋体字给出当前字体和重量
	dc.SelectObject(&font1);
	dc.TextOut(395, 110, "参数lfWeight确定输出文字的粗细");

	//恢复设备上下文原有的 GDI 绘图对象
	dc.SelectObject(pOldFont);
}

//定义角度向弧度的转换
double dTransAngleToRadian(double dAngle)
{

	double dRadian = dAngle/180.* 3.1415926;
	return dRadian;
}