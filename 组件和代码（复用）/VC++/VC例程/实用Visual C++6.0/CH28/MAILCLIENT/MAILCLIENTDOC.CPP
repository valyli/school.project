// MailClientDoc.cpp : implementation of the CMailClientDoc class
//

#include "stdafx.h"
#include "MailClient.h"

#include "MailClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailClientDoc

IMPLEMENT_DYNCREATE(CMailClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CMailClientDoc, CDocument)
	//{{AFX_MSG_MAP(CMailClientDoc)
	ON_COMMAND(ID_RECEIVE, OnFileReceive)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailClientDoc construction/destruction

#include "mapi.h"

HMODULE g_hMAPI;
LHANDLE g_hSession;

LPMAPILOGON g_lpfnLogon;
LPMAPILOGOFF g_lpfnLogoff;
LPMAPIFINDNEXT g_lpfnFindNext;
LPMAPIREADMAIL g_lpfnReadMail;
LPMAPIFREEBUFFER g_lpfnFreeBuffer;

CMailClientDoc::CMailClientDoc()
{
	//**Dynamically load the dll and functions
	g_hMAPI=LoadLibrary("MAPI28.DLL");
	g_lpfnLogon=(LPMAPILOGON)
		GetProcAddress(g_hMAPI,"MAPILogon");
	g_lpfnLogoff=(LPMAPILOGOFF)
		GetProcAddress(g_hMAPI,"MAPILogoff");
	g_lpfnFindNext=(LPMAPIFINDNEXT)
		GetProcAddress(g_hMAPI,"MAPIFindNext");
	g_lpfnReadMail=(LPMAPIREADMAIL)
		GetProcAddress(g_hMAPI,"MAPIReadMail");
	g_lpfnFreeBuffer=(LPMAPIFREEBUFFER)
		GetProcAddress(g_hMAPI,"MAPIFreeBuffer");

	(*g_lpfnLogon) (0,NULL,NULL,
		MAPI_NEW_SESSION | MAPI_LOGON_UI,0,&g_hSession);
}

CMailClientDoc::~CMailClientDoc()
{
	//**Log off and free the session
	(*g_lpfnLogoff) (g_hSession,0,0,0);
	FreeLibrary(g_hMAPI);
}

void CMailClientDoc::OnFileReceive() 
{
	//**Find the view
	POSITION pos=GetFirstViewPosition();
	CView *pView=GetNextView(pos);

	//Declare the message identifiers
	static char szSeedMessage[512];
	static char szMessage[512];

	static LPSTR pSeed=NULL;
	static LPSTR pMsg=NULL;
	lpMapiMessage lpMessage=NULL;

	//**Find the next mail
	ULONG ulResult=(*g_lpfnFindNext)(g_hSession,
					(ULONG)pView->m_hWnd,NULL,pSeed,
					MAPI_LONG_MSGID,0L,pMsg);

	//**Read the next email
	ulResult=(*g_lpfnReadMail)(g_hSession,
			(ULONG)pView->m_hWnd,pMsg,MAPI_PEEK,0L,&lpMessage);
	
	CString strMessage;
	CString strFmt;
	if (ulResult==0L)
	{
		//**Store the message parts
		strFmt.Format("From:%s\r\n",
			lpMessage->lpOriginator->lpszName);
		strMessage+=strFmt;
		strFmt.Format("To:%s\r\n",
			lpMessage->lpRecips[0].lpszName);
		strMessage+=strFmt;
		strFmt.Format("Subject:%s\r\n",
			lpMessage->lpszSubject);
		strMessage+=strFmt;
		strMessage+=lpMessage->lpszNoteText;
		pSeed=szSeedMessage;
		strcpy(pSeed,pMsg);

		//**Set the message to the edit view
		pView->SetWindowText(strMessage);

		//**Free the allocated buffer
		(*g_lpfnFreeBuffer)((LPVOID)lpMessage);
	}
}

BOOL CMailClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMailClientDoc serialization

void CMailClientDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CMailClientDoc diagnostics

#ifdef _DEBUG
void CMailClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMailClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMailClientDoc commands


