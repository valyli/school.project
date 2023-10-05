#include "stdafx.h"
#include <memory>
#include <malloc.h>

#include "BEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef HASFLAG
#define HASFLAG(VAR,FLAG)       (((VAR)&(FLAG))==(FLAG))
#endif

// *************************************************************************
// class CSW_EditSelection
// *************************************************************************

CSW_EditSelection::CSW_EditSelection()
{
    Empty();
}

// *************************************************************************

void CSW_EditSelection::Empty()
{
    m_StartLine = -1;
    m_StartCol  = -1;

    m_aLine     = -1;
    m_aCol      = -1;
    m_zLine     = -1;
    m_zCol      = -1;
}

// *************************************************************************

BOOL CSW_EditSelection::IsEmpty()
{
    return m_aLine == m_zLine && m_aCol == m_zCol;
}

// *************************************************************************
//
//  This function returns FALSE if no characters are selected in the line 'iLine'.
//
BOOL CSW_EditSelection::GetSelectedChars (int iLine, int &First, int &Last)
{
    First = 1000000;
    Last  = -1;
    if (IsEmpty() || (iLine < m_aLine) || (iLine > m_zLine)) return FALSE;

    First = -1;
    Last  = 1000000;
    if (iLine == m_aLine) First = m_aCol;
    if (iLine == m_zLine) Last  = m_zCol - 1;
    return TRUE;
}

// *************************************************************************

void CSW_EditSelection::SetStartSelection (int StartLine, int StartCol)
{
    m_StartLine = m_aLine = m_zLine = StartLine;
    m_StartCol  = m_aCol  = m_zCol  = StartCol;
}

// *************************************************************************

void CSW_EditSelection::SetEndSelection (int EndLine, int EndCol)
{
    if (EndLine > m_StartLine) {
        m_aLine = m_StartLine;
        m_aCol  = m_StartCol;
        m_zLine = EndLine;
        m_zCol  = EndCol;
        return;
    }
    if (EndLine < m_StartLine) {
        m_aLine = EndLine;
        m_aCol  = EndCol;
        m_zLine = m_StartLine;
        m_zCol  = m_StartCol;
        return;
    }
    m_aLine = m_zLine = m_StartLine;

    if (EndCol > m_StartCol) {
        m_aCol  = m_StartCol;
        m_zCol  = EndCol;
        return;
    }
    if (EndCol < m_StartCol) {
        m_aCol  = EndCol;
        m_zCol  = m_StartCol;
        return;
    }
    m_aCol  = m_zCol  = m_StartCol;
}

// *************************************************************************
//
// A abstract class for all kind text editor
//
// Any text editors just need to override some methods from it
//
// *************************************************************************

IMPLEMENT_DYNAMIC( CSW_EditorBase, CWnd)
BEGIN_MESSAGE_MAP( CSW_EditorBase, CWnd)
    ON_WM_ERASEBKGND    ()
    ON_WM_PAINT         ()
    ON_WM_SIZE          ()
    ON_WM_HSCROLL       ()
    ON_WM_VSCROLL       ()
    ON_WM_MOUSEWHEEL    ()

    ON_WM_LBUTTONDOWN   ()
    ON_WM_MOUSEMOVE     ()
    ON_WM_LBUTTONUP     ()

    //ON_WM_KEYDOWN       ()

END_MESSAGE_MAP()

// *************************************************************************

CSW_EditorBase::CSW_EditorBase()
{
    m_FixedFont.CreateStockObject( ANSI_FIXED_FONT);
    m_FixedFontWidth    = 0;
    m_FixedFontHeight   = 0;

    m_nTmpVertScrollPos = 0;
    m_MouseMoveLine     = 0;
    m_MouseMoveCol      = 0;
    m_MouseMoveTopY     = 0;
    m_MouseMoveBotY     = 0;
}

// *************************************************************************

CSW_EditorBase::~CSW_EditorBase()
{
    if ( ::IsWindow( m_hWnd)) {
        ::DestroyWindow( m_hWnd);
    }
}

// *************************************************************************

CSize _GetTextExtent(CFont& Font)
{
    CDC IC;
    IC.CreateIC( "DISPLAY", NULL, NULL, NULL);
    CFont* pFont = (CFont*)IC.SelectObject( Font);

    CSize sz = IC.GetTextExtent( "W", 1);
    
    if ( pFont) ::SelectObject( IC.GetSafeHdc(), pFont);

    IC.DeleteDC();

    return sz;
}

// *************************************************************************

inline UINT CSW_EditorBase::GetLineH(int nLine)
{
    if ( m_FixedFontHeight > 0) return m_FixedFontHeight;
    m_FixedFontHeight = _GetTextExtent( m_FixedFont).cy;
    return m_FixedFontHeight;
}

// *************************************************************************

inline UINT CSW_EditorBase::GetColW(int nCol)
{
    if ( m_FixedFontWidth > 0) return m_FixedFontWidth;   
    m_FixedFontWidth = _GetTextExtent( m_FixedFont).cx;
    return m_FixedFontWidth;
}

// *************************************************************************

int CSW_EditorBase::GetLineFromY(int &Y)
{
    int iLine = 0;
    int curY = 0;

    // Loop in the list
    for ( int i = 0; i < GetTotalLines(); i++) {
        int H = GetLineH( i);
        if (curY + H > Y) {
            Y = curY;
            return i;
        }
        curY += H;
        iLine++;
    }

    // Not found
    return -1;
}

// *************************************************************************

int CSW_EditorBase::GetColFromX(int &X)
{
    int iCol = 0;
    int curX = 0;
    int nTotalCols = GetTotalCols();
    for ( int i = 0; i < nTotalCols; i++) {
        int W = GetColW( i);
        if ( curX + W > X) break;
        curX += W;
        iCol++;
    }
    // Not found
    X = curX;
    return i;
}

// *************************************************************************
//
//  The coordinates 'Pt' are relative to the Client Window.
//  After the function, 'Pt' is updated to point to the exact position of the character [iLine,iCol].
//  This function returns TRUE if get a correct cell, otherwise FALSE.
//
BOOL CSW_EditorBase::GetLineColFromPt (CPoint &Pt, int &iLine, int &iCol)
{
    iLine = 0;
    iCol  = 0;

    // Get the indice of the line
    int ScrollV = GetScrollPos( SB_VERT);
    int Y = Pt.y + ScrollV; // Make Y relative to the String List
    iLine = GetLineFromY( Y);
    if ( iLine < 0) return FALSE;

    // Get the indice of the column
    int ScrollH = GetScrollPos( SB_HORZ);
    int X = Pt.x + ScrollH; // Make X relative to the String List
    iCol = GetColFromX( X);
    if ( iCol < 0) return FALSE;

    // Update 'Pt'.
    Pt.x = X - ScrollH;
    Pt.y = Y - ScrollV;

    return TRUE;
}

// *************************************************************************

BOOL CSW_EditorBase::Create (DWORD dwStyle, CRect Rect, CWnd* pParentWnd, UINT nID/* = 1000*/)
{
    BOOL bRet = CWnd::Create( NULL, "SW_EditorBase", dwStyle, Rect, pParentWnd, nID);
    return bRet;
}

// *************************************************************************

void CSW_EditorBase::OnUpdateBars()
{
    if ( !::IsWindow( m_hWnd)) return;

    CRect ClientR;

    SCROLLINFO ScrollInfo;

    // === Horizontal ===
    GetClientRect( ClientR);
    int CliW = ClientR.Width();
    UINT nTotalW = 0;
    for ( int i = GetTotalCols() - 1; i >= 0; i--) {
        nTotalW += GetColW( i);
    }
    if ( nTotalW > CliW) {
	    SetScrollRange( SB_HORZ, 0, nTotalW);
        GetScrollInfo( SB_HORZ, &ScrollInfo, SIF_PAGE);
        ScrollInfo.nPage = CliW;
        SetScrollInfo( SB_HORZ, &ScrollInfo, SIF_PAGE);
    } else {
	    SetScrollRange( SB_HORZ, 0, 0);
    }

    // Get the Client Rect again because it can be changed by the setting of the HORZ scrollbar.
    GetClientRect( ClientR);

    // === Vertical ===
    int CliH = ClientR.Height();
    UINT nTotalH = 0;
    for ( i = GetTotalLines() - 1; i >= 0; i--) {
        nTotalH += GetLineH( i);
    }
    if ( nTotalH > CliH) {
        SetScrollRange( SB_VERT, 0, nTotalH);
        GetScrollInfo( SB_VERT, &ScrollInfo, SIF_PAGE);
        ScrollInfo.nPage = CliH;
        SetScrollInfo( SB_VERT, &ScrollInfo, SIF_PAGE);
    } else {
	    SetScrollRange( SB_VERT, 0, 0);
    }
}

// *************************************************************************

void CSW_EditorBase::OnPaint (void)
{    
    CPaintDC dc( this);

    CFont* pOldFont = dc.SelectObject( &m_FixedFont);
    
    // The PaintRect is a sub-rect of the ClientRect (coord. relative to the window!)
    CRect PaintRect( dc.m_ps.rcPaint);

    // Get the first visile line to update(paint)
    int Y = PaintRect.top + GetScrollPos( SB_VERT);
    int iLine = GetLineFromY( Y);

    CPoint Pt( -GetScrollPos( SB_HORZ), Y-GetScrollPos( SB_VERT));

    int NbrRefreshed = 0;

    int nTotalLines = GetTotalLines();
    while ( iLine >= 0 && iLine < nTotalLines) {

        int FirstSelectedChar = -1;
        int LastSelectedChar  = -1;
        m_Selection.GetSelectedChars( iLine, FirstSelectedChar, LastSelectedChar);

        // Draw text starting from the current point
        dc.MoveTo( Pt);

        int H = GetLineH( iLine); // This can make a first parsing.
        int X = 0;
        CRect R( /*l*/Pt.x, /*t*/Pt.y, /*r*/Pt.x + PaintRect.right, /*b*/Pt.y + H);
        if ( R.right < 0) {
            R.left = PaintRect.left; 
            R.right = PaintRect.right;
        }
        dc.FillSolidRect( R, dc.GetBkColor());

        // Get string in this line
        CString s;
        GetLineStr( iLine, s); 

        // Draw line
        OnDrawItem( &dc, iLine, s, FirstSelectedChar, LastSelectedChar);

        // Next ...
        NbrRefreshed++;

        Pt.y += H;
        if ( Pt.y >= PaintRect.bottom) break;

        iLine++;
    }

    // The rest of the client area should be covered by the background color as 'empty'
    int RestY = PaintRect.bottom - Pt.y;
    if (RestY > 0) {
        dc.FillSolidRect( PaintRect.left, Pt.y, PaintRect.Width(), RestY, dc.GetBkColor());
    }

    dc.SelectObject(pOldFont);
}

// *************************************************************************

BOOL CSW_EditorBase::OnDrawItem(CDC *pDC, UINT nLine, LPCTSTR lpStr, int FirstSelectedChar /* = -1 */, int LastSelectedChar /* = -1 */)
{
    //CPoint Pt = pDC->GetCurrentPosition();

    UINT OldTextAlign = pDC->SetTextAlign( TA_UPDATECP);

    BOOL     bInHighLight = FALSE;
    COLORREF OldBkColor   = 0;
    COLORREF OldTextColor = 0;

    int nTotalChars = lstrlen( lpStr);
    for ( int iChar = 0; iChar < nTotalChars; iChar++) {
        if ((iChar >= FirstSelectedChar) && (iChar <= LastSelectedChar)) {
            if ( !bInHighLight) {
                bInHighLight = TRUE;
                OldBkColor   = pDC->SetBkColor(   ::GetSysColor( COLOR_HIGHLIGHT));
                OldTextColor = pDC->SetTextColor( ::GetSysColor( COLOR_HIGHLIGHTTEXT));
            }
        } else {
            // Restore the colors
            if (bInHighLight) {
                bInHighLight = FALSE;
                pDC->SetBkColor(   OldBkColor);
                pDC->SetTextColor( OldTextColor);
            }            
        }
        pDC->TextOut( 0/*Ingore*/, 0/*Ingore*/, lpStr + iChar, 1);
    }

    pDC->SetTextAlign( OldTextAlign);

    if (bInHighLight) {
        pDC->SetBkColor(   OldBkColor);
        pDC->SetTextColor( OldTextColor);
    }

    return TRUE;
}

// *************************************************************************

BOOL CSW_EditorBase::OnEraseBkgnd (CDC *pDC)
{
    return TRUE;
}

// *************************************************************************

void CSW_EditorBase::OnSize(UINT nType, int cx, int cy) 
{
    CWnd ::OnSize(nType, cx, cy);
    
    if( !GetSafeHwnd()) return;

    OnUpdateBars();
}

// *************************************************************************

#define SB_WHEEL    SB_ENDSCROLL + 1

int CSW_EditorBase::_Scroll( UINT nBar, UINT nSBCode, UINT nPos)
{
    if ( (nSBCode < SB_LINEUP || nSBCode >= SB_ENDSCROLL) && nSBCode != SB_WHEEL) return 0;

    int MaxPos = GetScrollLimit( nBar);
    int CurPos = GetScrollPos( nBar);
	int NewPos = 0;

    switch( nSBCode) {
        case SB_LEFT:           NewPos = 0;             break;
        case SB_RIGHT:          NewPos = MaxPos;        break;
        case SB_LINELEFT:       // Scroll left.
            if ( CurPos > 0) NewPos = CurPos - GetLineH(0);    
            break;
        case SB_LINERIGHT:
            if ( CurPos < MaxPos) NewPos = CurPos + GetLineH(0);    
                            else  NewPos = MaxPos;
            break;
        case SB_PAGELEFT:       // Scroll one page left.
            if ( CurPos > 0) NewPos = CurPos - 500;    
            break;
        case SB_PAGERIGHT:      // Scroll one page right.
            if ( CurPos < MaxPos) NewPos = CurPos + 500;    
                            else  NewPos = MaxPos;
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:     
            {
                SCROLLINFO info;
                info.cbSize = sizeof(SCROLLINFO);
                info.fMask = SIF_TRACKPOS;
                GetScrollInfo( nBar, &info);
                NewPos = info.nTrackPos;      
                break;
            }
        case SB_WHEEL:
            {
                // Get the the mouse settings from the system
                UINT uWheelScrollLines = 1;
                ::SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &uWheelScrollLines, 0);

                short zDelta = nPos;
                int Offset = 0;
                // Get how many lines to scroll
                int nToScroll = ::MulDiv( -zDelta, uWheelScrollLines, WHEEL_DELTA);
                if ( nToScroll == -1 || uWheelScrollLines == WHEEL_PAGESCROLL) {
                    // Scroll a page
                    Offset = _Scroll( nBar, ( zDelta > 0)?SB_PAGELEFT:SB_PAGERIGHT, 0);
                } else {
                    // Scroll lines
                    for ( UINT i = 0; i < (UINT)abs(nToScroll); i++) 
                        Offset += _Scroll( nBar, ( zDelta > 0)?SB_LINELEFT:SB_LINERIGHT, 0);
		        }
                return Offset;
            }
        default:                break;
    };
    // Check the limits
    if (NewPos < 0) 
        NewPos = 0;
    if (NewPos > MaxPos) 
        NewPos = MaxPos;
    int Offset = NewPos - CurPos;
    if (!Offset) return Offset;

    // Update the Scroll Position and Scroll the Window
	SetScrollPos( nBar, NewPos);

    return Offset;
}

// *************************************************************************

void CSW_EditorBase::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CWnd::OnHScroll( nSBCode, nPos, pScrollBar);
    int Offset = _Scroll( SB_HORZ, nSBCode, nPos);
    if ( !Offset) return;
    ScrollWindow( -Offset, 0);
}

// *************************************************************************

void CSW_EditorBase::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CWnd::OnVScroll( nSBCode, nPos, pScrollBar);
    int Offset = _Scroll( SB_VERT, nSBCode, nPos);
    if ( !Offset) return;
    ScrollWindow( 0, -Offset);
}

//*******************************************************************
//
// Response to the mouse wheel events
//
BOOL CSW_EditorBase::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    if ( nFlags & (MK_SHIFT | MK_CONTROL)) return FALSE;

    // Check if there is a scrollbar
    DWORD dwStyle = GetStyle();
    int Offset = 0;
    // The vertical scroll has a higher priority
    if ( HASFLAG( dwStyle, WS_VSCROLL)) {
        Offset = _Scroll( SB_VERT, SB_WHEEL, zDelta);
        ScrollWindow( 0, -Offset);
    }
    // If the vertical scroll didn't move, scroll the horizontal
    if ( !Offset && HASFLAG( dwStyle, WS_HSCROLL)) {
        Offset = _Scroll( SB_HORZ, SB_WHEEL, zDelta);
        ScrollWindow( -Offset, 0);
    }
    if ( Offset) UpdateWindow();

    return (BOOL)Offset;
}

// *************************************************************************

void CSW_EditorBase::OnLButtonDown (UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown( nFlags, point);

    BOOL bRefreshAll = TRUE;

    SetFocus();

    // Be able to track the cursor when the move pointer moves out of the window
    SetCapture();

    // Keep the current vertical scrollbar position when mouse is pushed down
    m_nTmpVertScrollPos = GetScrollPos( SB_VERT);

    // Get the clicked Line and Col
    int iLine = 0;
    int iCol  = 0;
    BOOL bFound = GetLineColFromPt( point, iLine, iCol); // Can return NULL !!!

    // Update the selection
    if (HASFLAG( nFlags, MK_SHIFT)) {
        m_Selection.SetEndSelection( iLine, iCol);
    }
    else {
        if (m_Selection.IsEmpty()) bRefreshAll = FALSE;
        m_Selection.SetStartSelection( iLine, iCol);
    }

    // Initialize the part of the ClientRect to to refresh - used in "OnMouseMove()"
    if ( bFound) {
        m_MouseMoveTopY = point.y;
        m_MouseMoveBotY = m_MouseMoveTopY + GetLineH( iLine);
    }

    // Redraw if necessary
    if (bRefreshAll) Invalidate();
}

// *************************************************************************

void CSW_EditorBase::OnMouseMove (UINT nFlags, CPoint point)
{
    // Get the current pointed line
    int iLine = 0;
    int iCol  = 0;
    BOOL bFound = GetLineColFromPt( point, iLine, iCol);
    if ( !bFound) {
        m_MouseMoveLine = 0;
        m_MouseMoveCol  = 0;
        End:
        CWnd::OnMouseMove( nFlags, point);
        return;
    }

    // Check if we really moved
    if ((m_MouseMoveLine == iLine) && (m_MouseMoveCol == iCol)) goto End;
    m_MouseMoveLine = iLine;
    m_MouseMoveCol  = iCol;

    // If the mouse button is down, we update the selection and invalidate the correct Rect
    if (HASFLAG( nFlags, MK_LBUTTON)) {
        // Update the selection
        m_Selection.SetEndSelection( iLine, iCol);
        // Build the Rect to Invalidate
        int _TopY = point.y;
        int _BotY = _TopY + GetLineH( iLine);
        CRect R;
        GetClientRect( &R);
        R.top    = min( m_MouseMoveTopY, _TopY);
        R.bottom = max( m_MouseMoveBotY, _BotY);
        m_MouseMoveTopY = _TopY;
        m_MouseMoveBotY = _BotY;
        // Redraw
        InvalidateRect( R, /*bErase*/FALSE);
    }
    goto End;
}

// *************************************************************************

void CSW_EditorBase::OnLButtonUp( UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonUp( nFlags, point);
    
    // Release the mouse capture
    ::ReleaseCapture();
}


// *************************************************************************
// CSW_TextInfo
// *************************************************************************
CSW_TextInfo::CSW_TextInfo()
{
    m_StrData.RemoveAll();
    m_MaxColNBR = 0;
}

// *************************************************************************

void CSW_TextInfo::AddLine(LPCTSTR lpStr)
{
    int nLeng = lstrlen( lpStr);
    if ( nLeng > m_MaxColNBR) m_MaxColNBR = nLeng;
    m_StrData.Add( lpStr);
}

// *************************************************************************

void CSW_TextInfo::Clean(void)
{
    m_StrData.RemoveAll();
}

// *************************************************************************

inline UINT CSW_TextInfo::GetTotalLines(void)
{
    return m_StrData.GetSize();
}

// *************************************************************************

inline UINT CSW_TextInfo::GetTotalCols(void)
{
    return m_MaxColNBR;
}

// *************************************************************************

void CSW_TextInfo::GetLineStr(int nLine, CString& str)
{
    if ( nLine < 0 || nLine > GetTotalLines()) {
        str.Empty();
        return;
    }
    str = m_StrData.GetAt( nLine); 
}

// *************************************************************************
// CSW_BDisplay
// *************************************************************************

#define _ADDR_LEN   8
#define _HEX_LEN    3
#define _ANSI_LEN   1
#define _SEPE_LEN   3

// *************************************************************************

BEGIN_MESSAGE_MAP( CSW_BDisplay, CSW_EditorBase)
    ON_WM_VSCROLL       ()
    ON_WM_KEYDOWN       ()
END_MESSAGE_MAP()

// *************************************************************************

CSW_BDisplay::CSW_BDisplay()
{
    m_pData = NULL;
    m_Length = 0;

    m_nBytesPerRow = 0x10;
    m_TotalLines = 0;
    m_TotalCols  = 0;

    m_Endless = FALSE;
}

// *************************************************************************

BOOL CSW_BDisplay::SetDataPtr(LPBYTE pData, UINT nLen)
{
    m_pData = pData;
    m_Length = nLen;

    // 
    m_TotalLines = m_Length / m_nBytesPerRow;
    if ( m_nBytesPerRow * m_TotalLines < m_Length) m_TotalLines++;

    m_TotalCols  = _ADDR_LEN + _SEPE_LEN + _HEX_LEN * m_nBytesPerRow + _SEPE_LEN + _ANSI_LEN * m_nBytesPerRow;

    OnUpdateBars();

    return TRUE;
}

// *************************************************************************

inline UINT CSW_BDisplay::GetTotalLines(void)
{
    return m_TotalLines;
}

// *************************************************************************

inline UINT CSW_BDisplay::GetTotalCols(void)
{
    return m_TotalCols;
}

// *************************************************************************

void Hex2Char(BYTE Hex, TCHAR lpBuf[3])
{
    const char gHexCharacters[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 
	lpBuf[0] = gHexCharacters[Hex>>4];
	lpBuf[1] = gHexCharacters[Hex&0xf];
	lpBuf[2] = ' ';
}

// *************************************************************************
//
// Get the first byte from a memory address.. If the memory address is not readable, return '?'
//
void ConvertByte(LPBYTE lpByte, TCHAR lpAnsi[1], TCHAR lpHexData[3])
{
try {
    // Check if the address is validate
    BOOL bValide = AfxIsValidAddress( lpByte, sizeof(TCHAR), FALSE);
    if ( bValide) {
	    lpAnsi[0] = isprint( *lpByte) ? *(TCHAR*)lpByte: '.';
	    Hex2Char( *lpByte, lpHexData);
        return;
    }
} catch ( ...) 
{
}
    // If the address is not readable, return unknown make
    lpAnsi[0] = '?';
    lpHexData[0] = '?';
    lpHexData[1] = '?';
    lpHexData[2] = ' ';
}

// *************************************************************************

void CSW_BDisplay::GetLineStr(int nLine, CString& str)
{
    try{
    LPBYTE dwPosBegin = m_pData + nLine*m_nBytesPerRow;
    LPBYTE _dwPosBegin = dwPosBegin;
	LPBYTE dwPosEnd = dwPosBegin + m_nBytesPerRow;

    // Seperated spaces
    TCHAR* pSepBuf = (TCHAR*)_alloca( _SEPE_LEN + 1);
	memset( pSepBuf, ' ', _SEPE_LEN);
	pSepBuf[_SEPE_LEN] = '\0';

    // Ansi
    #define ANSILen _ANSI_LEN * m_nBytesPerRow
    LPTSTR pAnsiBuf = (LPTSTR)_alloca( ANSILen + 1);
	memset(pAnsiBuf, ' ', ANSILen);

	// Formated hex-data
    #define HexSepLen   1
    #define HEXLen _HEX_LEN * m_nBytesPerRow + HexSepLen
	TCHAR* pHexBuf = (TCHAR*)_alloca(HEXLen + 1); 
    LPTSTR pHexPtr = pHexBuf;
    // Fill with spaces
	memset( pHexBuf, ' ', HEXLen);	

	for ( UINT i = 0; i < dwPosEnd - dwPosBegin; i++) {

        // Keep a space in the half of a line
        if ( i == m_nBytesPerRow/2) pHexPtr += HexSepLen;      
        ConvertByte( dwPosBegin+i, &(pAnsiBuf[i]), pHexPtr);
        pHexPtr += _HEX_LEN;
	}
	pAnsiBuf[ANSILen] = '\0';
	pHexBuf [HEXLen]  = '\0';

    // Draw Address and its contents
    str.Format( "%08X%s%s%s%s", _dwPosBegin/*nLine*m_TotalCols*/, pSepBuf, pHexBuf, pSepBuf, pAnsiBuf);
    } catch ( ...)
    {
    }
}

// *************************************************************************

void CSW_BDisplay::IncreaseLines(int nLines)
{
    if ( nLines > 0) {
        SetDataPtr( m_pData, m_Length + nLines * m_nBytesPerRow);
        return;
    }
    if ( SetDataPtr( (DWORD)m_pData + nLines*m_nBytesPerRow, m_Length)) Invalidate();
}

// *************************************************************************

void CSW_BDisplay::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if ( m_Endless && nSBCode < SB_ENDSCROLL) {
        if ( GetScrollLimit( SB_VERT) == GetScrollPos( SB_VERT)) IncreaseLines( 10);
        else 
            if ( GetScrollPos( SB_VERT) == 0) IncreaseLines( (nSBCode==SB_PAGEUP)?-10:-1);
    }
    CSW_EditorBase::OnVScroll( nSBCode, nPos, pScrollBar);
}

// *************************************************************************

void CSW_BDisplay::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar) {
        case VK_PRIOR:  SendMessage( WM_VSCROLL, SB_PAGEUP,   NULL); break;
        case VK_NEXT:   SendMessage( WM_VSCROLL, SB_PAGEDOWN, NULL); break;
        case VK_DOWN:   SendMessage( WM_VSCROLL, SB_LINEDOWN, NULL); break;
        case VK_UP:     SendMessage( WM_VSCROLL, SB_LINEUP,   NULL); break;
    }

    CSW_EditorBase::OnKeyDown( nChar, nRepCnt, nFlags);
}

// *************************************************************************
