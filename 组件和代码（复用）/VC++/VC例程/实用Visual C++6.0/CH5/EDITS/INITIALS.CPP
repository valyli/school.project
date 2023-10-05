// Initials.cpp : implementation file
//

#include "stdafx.h"
#include "Edits.h"
#include "Initials.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitials

CInitials::CInitials()
{
}

CInitials::~CInitials()
{
}


BEGIN_MESSAGE_MAP(CInitials, CEdit)
	//{{AFX_MSG_MAP(CInitials)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInitials message handlers

void CInitials::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	// ** Validat the entered character is alphabetic
	if (isalpha(nChar))
	{
		// ** Convert lower case to upper case
		if (islower(nChar))
			nChar-=32;

		// ** Call the default windows procedure as
		// ** the value of nChar may have been altered
		DefWindowProc(WM_CHAR,nChar,MAKELONG(nRepCnt,nFlags));

		// ** Call the default windows procedure
		// ** again to add the period
		nChar ='.';
		DefWindowProc(WM_CHAR,nChar,MAKELONG(nRepCnt,nFlags));
	}
	// ** if the backspace key is pressed call the
	// ** base class funtion twice to remove the period
	// ** and the letter
	if (nChar == VK_BACK)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}
