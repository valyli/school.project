#define WM_HOOK_CREATEWINDOW WM_USER + 100

class AFX_EXT_CLASS CMouseHook:public CObject  
{  
public:  
	CMouseHook();//������Ĺ��캯��
	~CMouseHook();//���������������
	BOOL StartHook(HWND hWnd1, HWND hWnd2); //��װ���Ӻ���
	BOOL StopHook(); //ж�ع��Ӻ���
};  
