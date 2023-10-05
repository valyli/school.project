//////////////////////////////////////////////////////////
//		Other Functions DialogBox Proc
//			Southern.Liang
//			  1996.7.7
//////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#include <windows.h>
#include "DOS.H"
#include "VCDAPI.H"
extern	int	CheckTime;
extern	int	ListAllFile;
extern	int	SupperVESAState;
extern	HANDLE 	hInst;
extern	HWND	AudioMainWindow;
extern	int	Chinese;
extern	int	BankingFlags;		//No 128K Buffer use banking.
extern	int	OtherDecoder;		//Use internal MPEG decoder.
extern	int	UseDCI;
extern	int	DCIType;	//If now be 640x480 and had DCI Primary 64K/32K
extern	char	OtherDecoderName[24];

#pragma	warn -par
DWORD	huge	PASCAL	AboutProc(HWND hwnd,WORD message,WORD wParam,LONG lParam)
{
	int		Ret;
	HDC		hdc;
	HBITMAP		hAbout;
	PAINTSTRUCT     ps;
	int		cx,cy;

	switch(message)
		{
		case 	WM_INITDIALOG:
			return	TRUE;
		case	WM_PAINT:
			hdc=BeginPaint(hwnd,&ps);
			cx=ps.rcPaint.right-ps.rcPaint.left;
			cx-=268;cx/=2;
			hAbout=LoadBitmap(hInst,"LOGO");
			DrawBitmap(hdc,hAbout,cx,0);
			DeleteObject(hAbout);
			EndPaint(hwnd,&ps);
			return	TRUE;
		case	WM_COMMAND:
			if(wParam==1)
				{
				EndDialog(hwnd,1);
				return TRUE;
				}
		case	WM_CLOSE:
			EndDialog(hwnd,0);
			return TRUE;
		}
	return	FALSE;
}
void	PASCAL	FAR	DisplaySystemMessage(HWND hwnd);
void	PASCAL	FAR	BuildCheckTimer(void);
void	PASCAL	FAR	GetBankingWay(void);
static	void	near	AddMCIDriverStringToListBox(HWND hwnd,int Item)
{
	int	Bytes;
	int	i;
	int	Count;
	char	*Ptr;
	char	Buffer[1024];

	SendDlgItemMessage(hwnd,Item,CB_ADDSTRING,0,(LPARAM)(LPCSTR)OtherDecoderName);
	SendDlgItemMessage(hwnd,Item,CB_SETCURSEL,0,0L);
	Bytes=GetPrivateProfileString("mci",NULL,NULL,Buffer,sizeof(Buffer),"system.ini");
	Ptr=Buffer;
	Count=0;
	while(Count<Bytes)
		{
		SendDlgItemMessage(hwnd,Item,CB_ADDSTRING,0,(LPARAM)(LPCSTR)Ptr);
		i=lstrlen(Ptr);
		i++;	//Next string
		Count+=i;
		Ptr+=i;
		}
}
DWORD	huge	PASCAL	OtherFunctionProc(HWND hwnd,WORD message,WORD wParam,LONG lParam)
{
	int	Ret;
	int	RetError;

	switch(message)
		{
		case 	WM_INITDIALOG:
			SetDlgItemInt(hwnd,200,CheckTime,TRUE);
			if(CheckTime==-1)//Can't edit it
				{
				SendDlgItemMessage(hwnd,200,EM_SETREADONLY,TRUE,0L);
				CheckDlgButton(hwnd,201,0);//Disable
				}
			else	{
				SendDlgItemMessage(hwnd,200,EM_SETREADONLY,FALSE,0L);
				CheckDlgButton(hwnd,201,1);//Enable
				}
			/////////////// Set Check state /////////
			CheckDlgButton(hwnd,202,ListAllFile);
			CheckDlgButton(hwnd,203,SupperVESAState);
			CheckDlgButton(hwnd,204,BankingFlags);
			if(OtherDecoder>1 || OtherDecoder<0) OtherDecoder=0;
			CheckRadioButton(hwnd,205,206,205+OtherDecoder);//Enable internal MPEG decoder
			if(OtherDecoder==0) EnableWindow(GetDlgItem(hwnd,207),FALSE);
			AddMCIDriverStringToListBox(hwnd,207);
			return TRUE;
		case	WM_COMMAND:
			switch(wParam)
				{
				case	1:	//OK
					Ret=GetDlgItemInt(hwnd,200,&RetError,TRUE);
					if(RetError)
						{//No Error
						if(Ret==-1)
							{//Off Check
							if(CheckTime!=-1)
								{
								KillTimer(hwnd,4545);
								CheckTime=Ret;
								BuildCheckTimer();
								}
							}
						else	{//Change Check Time
							if(Ret!=CheckTime)
								{
								KillTimer(hwnd,4545);
								CheckTime=Ret;
								BuildCheckTimer();
								}
							}
						}
					///////////
					ListAllFile=IsDlgButtonChecked(hwnd,202);
					SupperVESAState=IsDlgButtonChecked(hwnd,203);
					SupperVESAState<<=3;	// Bit 3
					if(BankingFlags==0)
						{//Be Force Banking
						BankingFlags=IsDlgButtonChecked(hwnd,204);
						if(BankingFlags) GetBankingWay();
						}
					else	BankingFlags=IsDlgButtonChecked(hwnd,204);
					Ret=IsDlgButtonChecked(hwnd,206);//Be Selected
					if(Ret==1 && OtherDecoder==0)
						{//Old use internal,now use other
						if(DCIType==2)
							{//Let other driver use DCI YUV
							DeleteDCISurface();
							ReleaseDCIProvider();
							}
						}
					if(Ret==0 && OtherDecoder==1)
						{//Old is other,now use internal
						UseDCI=SearchDCISupportFunction();
						}
					OtherDecoder=Ret;
					if(OtherDecoder)//Get The MCI driver type name
						GetWindowText(GetDlgItem(hwnd,207),OtherDecoderName,sizeof(OtherDecoderName));
					/////////// Save Them //////////
					EndDialog(hwnd,1);
					return TRUE;
				case	2:	//CANCAL
					goto	RETURN;
				case 	100:	//SYSINFO
					DisplaySystemMessage(hwnd);
					return	TRUE;
				case	101:	//ABOUT
					if(Chinese) DialogBox(hInst,"ABOUTC",hwnd,(DLGPROC)AboutProc);
					else	DialogBox(hInst,"ABOUT",hwnd,(DLGPROC)AboutProc);
					return	TRUE;
				case	102:	//Help
					WinHelp(hwnd,"README.HLP",HELP_KEY,(DWORD)(LPCSTR)"其他功能");
					return	TRUE;
				/////////////////////
				case 	200:	return	TRUE;//This MUST TURE it case the init fail.
				case	201:	//AutoCheck
					Ret=IsDlgButtonChecked(hwnd,201);
					if(Ret)	{//Enable
						SetDlgItemInt(hwnd,200,CheckTime,TRUE);
						SendDlgItemMessage(hwnd,200,EM_SETREADONLY,FALSE,0L);
						}
					else	{//Disable
						//CheckTime=-1;
						SetDlgItemInt(hwnd,200,-1,TRUE);
						SendDlgItemMessage(hwnd,200,EM_SETREADONLY,TRUE,0L);
						}
					return 	TRUE;
				case	202:	//FilesList
				case	203:	//VESAState
				case	204:	//BankingFlags
					return	TRUE;
				case 	205:	//Enable internal decoder
					EnableWindow(GetDlgItem(hwnd,207),FALSE);
					return	TRUE;
				case	206:	//Enable other MPEG decoder
					EnableWindow(GetDlgItem(hwnd,207),TRUE);
				case	207:	//Other MPEG Decoder list
					return	TRUE;
				}
		case	WM_CLOSE:
			RETURN:
			EndDialog(hwnd,0);
			return TRUE;
		}
	return FALSE;
}
#pragma	warn .par
