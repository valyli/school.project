#define WM_HOOK_CREATEWINDOW WM_USER + 100

class AFX_EXT_CLASS CMouseHook:public CObject  
{  
public:  
	CMouseHook();//钩子类的构造函数
	~CMouseHook();//钩子类的析构函数
	BOOL StartHook(HWND hReceiveWindow); //安装钩子函数
	BOOL StopHook(); //卸载钩子函数
};  
