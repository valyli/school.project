// InquireView.cpp : implementation of the CInquireView class
//

#include "stdafx.h"
#include "Inquire.h"

#include "InquireDoc.h"
#include "InquireView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInquireView

IMPLEMENT_DYNCREATE(CInquireView, CScrollView)

BEGIN_MESSAGE_MAP(CInquireView, CScrollView)
	//{{AFX_MSG_MAP(CInquireView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_REGISTRATION, OnRegistration)
	ON_MESSAGE(WM_SUBMIT, OnSubmit)
	ON_MESSAGE(WM_DELETE, OnDelete)
	ON_MESSAGE(WM_FIRST_REC, OnFirstRec)
	ON_MESSAGE(WM_LAST_REC, OnLastRec)
	ON_MESSAGE(WM_PREV_REC, OnPrevRec)
	ON_MESSAGE(WM_NEXT_REC, OnNextRec)
	ON_MESSAGE(WM_SORTING, OnSorting)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInquireView construction/destruction

CInquireView::CInquireView()
{
	// TODO: add construction code here
	m_Sort = none;
	m_Retrieve = none;
	m_RetrieveKey = "";

}

CInquireView::~CInquireView()
{
}

BOOL CInquireView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CInquireView drawing

void CInquireView::OnDraw(CDC* pDC)
{
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	// �ָ�ԭ�еļ�������ؼ��֡��������ͼ����ؼ���
	CStudent::m_Sort = m_Sort;//changed by me
	CStudent::m_Retrieve = m_Retrieve;//changed by me
	CStudent::m_RetrieveKey = m_RetrieveKey;//changed by me

	// ���ѧ����Ϣ����Ϊ�գ�����

	if(pDoc->m_StudentSet.Count() == 0)
		return;

	// �ݴ浱ǰ���ϼ�¼����ֵ���Ա�ָ���
	int index = pDoc->m_StudentSet.Index();

	// �����豸��ʾӳ�䷽ʽ
	pDC->SetMapMode(MM_LOENGLISH);

	// �ж��Ƿ�ѡ��ǰѡ������Ϊ�豸ʹ�õĶ���
	CFont font, *oldfont;
	COLORREF oldcolor;
	BOOL changeFont = font.CreateFontIndirect(&pDoc->m_logFont);
	if(changeFont)
	{
		oldfont = pDC->SelectObject(&font);
		oldcolor = pDC->SetTextColor(pDoc->m_crText);
	}
	
	// ��ʼ����ʾ��ʽ���ݣ��ַ��ߴ�textSize���и�lineHeight��������Ͻ�λ��tabPos��
	// �ĵ���ѧ����Ϣ���ϣ��ߴ�docSize���������Ӵ������ߴ硣
	int i, lineWidth = 0, lineHeight;
	CSize textSize = pDC->GetTextExtent("ѧ");
	for(i = 0; i < 11; i++)
		lineWidth += textSize.cx * CStudent::m_FieldWidth[i] / 2;
	lineHeight = textSize.cy + 8;
	CRect rect;
	GetClientRect(&rect);
	CSize clientSize(rect.right, rect.bottom);
	CPoint tabPos = CPoint(20, -lineHeight * 2);
	CSize docSize(lineWidth + 40, lineHeight * (pDoc->m_StudentSet.Count() + 4));
	CSize tabSize;
	SetScrollSizes(MM_LOENGLISH, docSize, clientSize, CSize(lineWidth, lineHeight));
	pDoc->m_StudentSet.Index(pDoc->m_StudentSet.FirstIndex());
	// �жϵ�ǰ���ػ������Ƿ��Ǵ�ӡ���ӡԤ����
	if(pDC->IsPrinting())
	{
		// ����ÿҳ�ı�����Ͻ�λ��tabPos��ҳ������linesInPage��ҳ����interval��
		int pageHeight = pDC->GetDeviceCaps(VERTSIZE);
		int pageWidth = pDC->GetDeviceCaps(HORZSIZE);
		tabPos = CPoint(max(0, (pageWidth * 1000 / 254 - lineWidth) / 2), -lineHeight * 2);
		int linesInPage = pageHeight * 1000 / 254 / lineHeight - 4;
		int interval = pageHeight * 1000 / 254 - linesInPage * lineHeight + 2;

		// ���ݼ���״̬����ҳ��ʾ�����еĿɷ�����Ϣ��¼��
		for(i = 0; i < (pDoc->m_StudentSet.Count()) / linesInPage ; i++)
		{
			tabSize = CSize(lineWidth, -lineHeight * (linesInPage + 1));
			pDoc->m_StudentSet.ShowTitle(pDC, CRect(tabPos, tabSize), font, lineHeight);
			pDoc->m_StudentSet.DrawFrame(pDC, CRect(tabPos, tabSize),textSize, 
													lineHeight, linesInPage + 1);
			pDoc->m_StudentSet.ShowItems(pDC, tabPos, textSize, lineHeight,
											i * linesInPage, ( i + 1) * linesInPage);
			tabPos.y -= linesInPage * lineHeight + interval;
		}
		// ���ݼ���״̬�������һҳ��ʾ������ʣ��Ŀɷ�����Ϣ��¼��
		tabSize = CSize(lineWidth, -lineHeight * (pDoc->m_StudentSet.Count() - i * linesInPage + 1));
		pDoc->m_StudentSet.ShowTitle(pDC, CRect(tabPos, tabSize), font, lineHeight);
		pDoc->m_StudentSet.DrawFrame(pDC, CRect(tabPos, tabSize), textSize,
										lineHeight, pDoc->m_StudentSet.Count() - i * linesInPage + 1);
		pDoc->m_StudentSet.ShowItems(pDC, tabPos, textSize, lineHeight,
										i * linesInPage, pDoc->m_StudentSet.Count());
	}
	else
	{
		// ���Ӵ��Ŀͻ����У����ݼ���״̬��ʾ�����еĿɷ�����Ϣ��¼��
		tabSize = CSize(lineWidth, -lineHeight * (pDoc->m_StudentSet.Count() + 1));
		pDoc->m_StudentSet.ShowTitle(pDC, CRect(tabPos, tabSize), font, lineHeight); 
		pDoc->m_StudentSet.DrawFrame(pDC, CRect(tabPos, tabSize), textSize, 
										lineHeight, pDoc->m_StudentSet.Count() + 1);
		pDoc->m_StudentSet.ShowItems(pDC, tabPos, textSize, lineHeight, 
											0, pDoc->m_StudentSet.Count());
		char a[10];
		sprintf(a,"%d",pDoc->m_StudentSet.Count());
	}

	// ����Ѿ�ѡ��ǰѡ������Ϊ�豸ʹ�õĶ�����ָ�ԭ�е����Ͷ���
	if(changeFont)
	{
		pDC->SelectObject(oldfont);
		pDC->SetTextColor(oldcolor);
	}

	// �ָ�����ԭ�еļ�¼����ֵ��
	pDoc->m_StudentSet.Index(index);
}

void CInquireView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CInquireView printing

BOOL CInquireView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CInquireView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add preparation before printing
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// �ж��Ƿ�ѡ��ǰѡ������Ϊ�豸ʹ�õĶ���
	CFont font, *oldfont;
	COLORREF oldcolor;
	BOOL changeFont = font.CreateFontIndirect(&pDoc->m_logFont);
	if(changeFont)
	{
		oldfont = pDC->SelectObject(&font);
		oldcolor = pDC->SetTextColor(pDoc->m_crText);
	}

	// �趨��ʾӳ�䷽ʽ�����ڴ˷�ʽ�¼��㵱ǰ�ĵ��Ĵ�ӡ�ʹ�ӡԤ����ҳ����
	pDC->SetMapMode(MM_LOENGLISH);
	CSize textSize = pDC->GetTextExtent("ѧ") + CSize(0, 8);
	int pageHeight = pDC->GetDeviceCaps(VERTSIZE);
	int linesInPage = pageHeight * 1000 / 254 / textSize.cy - 4;
	int numPages = pDoc->m_StudentSet.Count() / linesInPage + 
		((pDoc->m_StudentSet.Size() % linesInPage) ? 1 : 0);
	pInfo->SetMaxPage(numPages);

	// ����Ѿ�ѡ��ǰѡ������Ϊ�豸ʹ�õĶ�����ָ�ԭ�е����Ͷ���
	if(changeFont)
	{
		pDC->SelectObject(oldfont);
		pDC->SetTextColor(oldcolor);
	}
}

void CInquireView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CInquireView diagnostics

#ifdef _DEBUG
void CInquireView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CInquireView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CInquireDoc* CInquireView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInquireDoc)));
	return (CInquireDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInquireView message handlers

void CInquireView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// �����ǰ������Ǵ�ӡ���ӡԤ����������ÿҳ���ӿںʹ��ڵĶ�Ӧλ�á�
	if(pDC->IsPrinting())
	{
		int pageHeight = pDC->GetDeviceCaps(VERTSIZE);
		int originY = (pageHeight * 1000 / 254 + 2) * (pInfo->m_nCurPage - 1);
		// ����ÿҳ��ʾ���ݵĴ�����ʼλ�á�
		pDC->SetWindowOrg(0, -originY);
	}
	else
		CScrollView::OnPrepareDC(pDC, pInfo);
}

// ��ʾ������������Ի���Լ��Ͻ��м����¼���޸ļ�¼��ɾ����¼�ͼ��ϵ����򼰼�����
void CInquireView::OnRegistration() 
{
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(!pDoc->m_pDataIODlg)
	{
		pDoc->m_pDataIODlg = new CDataIODlg(this);
		pDoc->m_pDataIODlg->Create(IDD_DATA_IO_DLG, this);
	}
	pDoc->m_pDataIODlg->ShowWindow(SW_SHOWNORMAL);
}

// �ύ�¼�¼��������Ӧ������
LONG CInquireView::OnSubmit(WPARAM wParam, LPARAM lParam)
{
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->AddStudent();
	::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_REPLY, 0, 0);
	::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_ENABLE_REC_BUTTONS, 0, 0);
	return 0L;
}

// ɾ����¼��������Ӧ������
LONG CInquireView::OnDelete(WPARAM wParam, LPARAM lParam)
{
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	pDoc->DeleteStudent();
	::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_REPLY, 0, 0);
	::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_ENABLE_REC_BUTTONS, 0, 0);
	return 0L;
}

// Ѱ�Ҳ���ʾ�����е�һ����¼��������Ӧ������
LONG CInquireView::OnFirstRec(WPARAM wParam, LPARAM lParam)
{
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->FirstRec())
	{
		::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_REPLY, 0, 0);
		::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_ENABLE_REC_BUTTONS, 0, 0);
	}
	return 0L;
}

// Ѱ�Ҳ���ʾ���������һ����¼��������Ӧ������
LONG CInquireView::OnLastRec(WPARAM wParam, LPARAM lParam)
{
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->LastRec())
	{
		::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_REPLY, 0, 0);
		::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_ENABLE_REC_BUTTONS, 0, 0);
	}
	return 0L;
}

// Ѱ�Ҳ���ʾ������ǰһ����¼��������Ӧ������
LONG CInquireView::OnPrevRec(WPARAM wParam, LPARAM lParam)
{
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->PrevRec())
	{
		::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_REPLY, 0, 0);
		::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_ENABLE_REC_BUTTONS, 0, 0);
	}
	return 0L;
}

// Ѱ�Ҳ���ʾ��������һ����¼��������Ӧ������
LONG CInquireView::OnNextRec(WPARAM wParam, LPARAM lParam)
{
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->NextRec())
	{
		::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_REPLY, 0, 0);
		::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_ENABLE_REC_BUTTONS, 0, 0);
	}
	return 0L;
}

// ��������ؼ��ֶԼ��Ͻ��������������Ӧ������
LONG CInquireView::OnSorting(WPARAM wParam, LPARAM lParam)
{
	CInquireDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Sorting();
	::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_REPLY, 0, 0);
	::PostMessage(pDoc->m_pDataIODlg->m_hWnd, WM_ENABLE_REC_BUTTONS, 0, 0);
	return 0L;
}
