// EnumIconsDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "EnumIcons.h"
#include "EnumIconsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnumIconsDlg Dialogfeld

CEnumIconsDlg::CEnumIconsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEnumIconsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnumIconsDlg)
		// HINWEIS: Der Klassenassistent fügt hier Member-Initialisierung ein
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnumIconsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnumIconsDlg)
		// HINWEIS: Der Klassenassistent fügt an dieser Stelle DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEnumIconsDlg, CDialog)
	//{{AFX_MSG_MAP(CEnumIconsDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_ENUM_ICONS, OnBtnEnumIcons)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnumIconsDlg Nachrichten-Handler

BOOL CEnumIconsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CEnumIconsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CEnumIconsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEnumIconsDlg::OnBtnEnumIcons() 
{
// bytes to allocate for icon text and LVITEM struct
#define ALLOC_SIZE 200

HWND		hWnd;				// handle to desktop window
DWORD		dwPID;				// explorer process ID (associated with desktop)
HANDLE		hProcess;			// handle to explorer process (associated with desktop)
LPVOID		pData;				// pointer to LVITEM struct in explorer address space
LPVOID		pString;			// pointer to icon text in explorer address space
char		szText[ALLOC_SIZE];	// char array of icon text in application address space
char*		pszMessageBox;		// string to display
SIZE_T		BytesRead;			// for ReadProcessMemory
SIZE_T		BytesWritten;		// for WriteProcessMemory
BOOL		fResult;			// for ReadProcessMemory/WriteProcessMemory
LVITEM		lvi;				// LVITEM struct
int			i;					// counter for enumeration
int			nItemCount;			// icon item count

	// get desktop window handle
	if(((hWnd = FindWindowEx(NULL, NULL, "Progman", NULL)) == NULL) ||
	   ((hWnd = FindWindowEx(hWnd, NULL, "SHELLDLL_DefView", NULL)) == NULL) ||
	   ((hWnd = FindWindowEx(hWnd, NULL, "SysListView32", NULL)) == NULL))
	{
		MessageBox("Could not get desktop window.");
		goto Exit;
	}

	// get item count on desktop
	nItemCount = ::SendMessage(hWnd, LVM_GETITEMCOUNT, (WPARAM)0, (LPARAM)0);

	// allocate memory for output string
	pszMessageBox = (char*) malloc(ALLOC_SIZE * nItemCount);
	sprintf(pszMessageBox, "%d items:\n\n", nItemCount);

	// get desktop window process ID (explorer.exe)
	GetWindowThreadProcessId(hWnd, &dwPID);

	// open process to get explorer process handle
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);

	// allocate memory in explorer's address space
	// allocate space for LVITEM struct
	pData = VirtualAllocEx(hProcess, NULL, ALLOC_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	// allocate space for string (i.e. "Network Neighborhood")
	pString = VirtualAllocEx(hProcess, NULL, ALLOC_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// init LV_ITEM struct
	ZeroMemory(&lvi, sizeof(LVITEM));
	lvi.iItem = 0;
	lvi.iSubItem = 0;
	lvi.cchTextMax = 500;
	lvi.pszText = (char*)pString;	// use alloc'd string space

	// write the contents of lvi into explorer's address space
	fResult = WriteProcessMemory(hProcess, pData, &lvi, sizeof(LVITEM), &BytesWritten);

	// enum all icons
	for(i = 0; i < nItemCount; i++)
	{
		// get item's name
		::SendMessage(hWnd, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)pData);

  		// read back lvi struct (for debugging purposes only)
		fResult = ReadProcessMemory(hProcess, pData, szText, ALLOC_SIZE, &BytesRead);
		// read text of queried item
		fResult = ReadProcessMemory(hProcess, pString, szText, ALLOC_SIZE, &BytesRead);

		// append string to output string
		strcat(pszMessageBox, szText);
		strcat(pszMessageBox, "\n");
	}	

	// output message box with all icon texts
	MessageBox(pszMessageBox);

	// free alloc'd memory for message box
	free(pszMessageBox);

	// free alloc'd memory for string and LVITEM structs
	if(!VirtualFreeEx(hProcess, pString, ALLOC_SIZE, MEM_DECOMMIT))
	{
		MessageBox("VirtualFreeEx failed.");
		goto Exit;
	}
	if(!VirtualFreeEx(hProcess, pData, ALLOC_SIZE, MEM_DECOMMIT))
	{
		MessageBox("VirtualFreeEx failed.");
		goto Exit;
	}

	// close process handle
	CloseHandle(hProcess);

Exit:
	return;
}
