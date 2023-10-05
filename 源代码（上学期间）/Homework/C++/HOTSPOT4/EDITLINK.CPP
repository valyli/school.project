// editlink.cpp : implementation file
//

#include "stdafx.h"
#include "hotspot4.h"
#include "hotspdoc.h"
#include "editlink.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditLinkDlg dialog


CEditLinkDlg::CEditLinkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditLinkDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditLinkDlg)
	m_selectedLink = -1;
	//}}AFX_DATA_INIT
}


void CEditLinkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditLinkDlg)
	DDX_LBIndex(pDX, IDC_LINKLIST, m_selectedLink);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditLinkDlg, CDialog)
	//{{AFX_MSG_MAP(CEditLinkDlg)
	ON_BN_CLICKED(IDDELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEditLinkDlg message handlers


BOOL CEditLinkDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//Load hotspots for the current picture into
	//the dialog's list box.
	
	//Get the document.
	CHotspot4Doc* pDoc = (CHotspot4Doc*) GetParentFrame()->GetActiveDocument();

	//Get a pointer to the list box.
	CListBox* list = (CListBox*) GetDlgItem(IDC_LINKLIST);
	
	char buf[256];
	int index = 0, recnum = -1;
	unsigned long fileLength = pDoc->m_datafile.SeekToEnd();
	pDoc->m_datafile.SeekToBegin();
	HotSpotRecord record;
	int pos;

	do
	{
		pos = pDoc->m_datafile.GetPosition();
		pDoc->m_datafile.Read(&record, sizeof(HotSpotRecord));
		recnum++;
		if (pDoc->GetTitle().Compare(record.image))
			continue;	//Not equal, loop.
		else
			{
			strcpy(buf,record.image);
			strcat(buf, ": ");
			strcat(buf, record.target);
			list->InsertString(-1, buf);
			pDoc->m_recordNum[index++] = recnum;
			}
		
	} while (pDoc->m_datafile.GetPosition() < fileLength);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditLinkDlg::OnDelete() 
{
	//Delete the selected hotspot from the data file.
	//Start by seeing if a hot spot is selected in the list box.
	CListBox* list = (CListBox*) GetDlgItem(IDC_LINKLIST);
	int hotspot = list->GetCurSel();
	if (hotspot == LB_ERR)
		{
		MessageBox("No link selected");
		return;
		}

	//Get the document.
	CHotspot4Doc* pDoc = (CHotspot4Doc*) GetParentFrame()->GetActiveDocument();

	//Seek to the record's position in the file and write a blank
	//string in the image field to "delete" it.
	char buf[13] = "            ";
	long pos = sizeof(HotSpotRecord) * pDoc->m_recordNum[hotspot];
	pDoc->m_datafile.Seek(pos, CFile::begin);
	pDoc->m_datafile.Write(buf, 13);
	pDoc->m_datafile.Flush();
	EndDialog(IDCANCEL);
}
