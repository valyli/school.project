#ifndef __BEDIT_h
#define __BEDIT_h

// *************************************************************************
// CSW_EditSelection
// *************************************************************************

class CSW_EditSelection
{
public:
    int                 m_StartLine;
    int                 m_StartCol;

    int                 m_aLine;
    int                 m_aCol;
    int                 m_zLine;
    int                 m_zCol;

                        CSW_EditSelection   (void);

    void                Empty               (void);                
    BOOL                IsEmpty             (void);                

    BOOL                GetSelectedChars    (int iLine, int &First, int &Last);

    void                SetStartSelection   (int StartLine, int StartCol);
    void                SetEndSelection     (int EndLine,   int EndCol);
};

// *************************************************************************
//
// CSW_EditorBase
//
// A base calss for any kind of editor.
// The class has all the necessiary frame members for an editor.
// Any editors can be build by deriving just few members, and 
// they don't have to take care of selections, scrollbars, drawing work, and 
// other boring work has to be done on each kind of editors job.
//
// Examples : CSW_TextInfo and CSW_BDisplay
//
// *************************************************************************

class CSW_EditorBase : public CWnd
{    
    DECLARE_DYNAMIC( CSW_EditorBase)

private:

    // Fonts
            CFont   m_FixedFont;
            UINT    m_FixedFontHeight;
            UINT    m_FixedFontWidth;

    // Scrool bars
            int     m_nTmpVertScrollPos;// A temporary vertical scrollbar position
            int     m_MouseMoveLine;
            int     m_MouseMoveCol;
            int     m_MouseMoveTopY;
            int     m_MouseMoveBotY;

    // Selections
CSW_EditSelection   m_Selection;


public:
                    CSW_EditorBase  ();
                   ~CSW_EditorBase  ();

    // Create it
    virtual BOOL    Create          (DWORD dwStyle, CRect Rect, CWnd* pParentWnd, UINT nID = 1000);

protected:

    // Line functions
    virtual UINT    GetTotalLines   (void) = 0;
    virtual UINT    GetLineH        (int nLine);
    virtual int     GetLineFromY    (int &Y);

    // Column functions
    virtual UINT    GetTotalCols    (void) = 0;
    virtual UINT    GetColW         (int nCol);
    virtual int     GetColFromX     (int &X);

    // Cell functions
    virtual BOOL    GetLineColFromPt(CPoint &Pt, int &iLine, int &iCol);

    // String functions
    virtual void    GetLineStr      (int nLine, CString& str) = 0;
    
    // Paint
    virtual BOOL    OnDrawItem      (CDC *pDC, UINT nLine, LPCTSTR lpStr, int FirstSelectedChar = -1, int LastSelectedChar = -1);

    // Scroll bars, update scrollbars range
            void    OnUpdateBars    (void);

    // Don't derive again in subclass, normally.

    afx_msg BOOL    OnEraseBkgnd    (CDC *pDC);
    afx_msg void    OnPaint         (void);
    afx_msg void    OnSize          (UINT nType, int cx, int cy);

            int    _Scroll          (UINT nBar, UINT nSBCode, UINT nPos);
    afx_msg void    OnHScroll       (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void    OnVScroll       (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    afx_msg void    OnLButtonDown   (UINT nFlags, CPoint point);
    afx_msg void    OnLButtonDblClk (UINT nFlags, CPoint point);
    afx_msg void    OnMouseMove     (UINT nFlags, CPoint point);
    afx_msg void    OnLButtonUp     (UINT nFlags, CPoint point);
    afx_msg BOOL    OnMouseWheel    (UINT nFlags, short zDelta, CPoint pt);

    //afx_msg void    OnKeyDown       (UINT nChar, UINT nRepCnt, UINT nFlags);

    DECLARE_MESSAGE_MAP()
};

// *************************************************************************
//
// Class to display lines of text, like an information window
//
// All text saves inside a CStringArray.
//
// *************************************************************************

class CSW_TextInfo : public CSW_EditorBase
{
private:

    CStringArray    m_StrData;
    int             m_MaxColNBR;
public:

                    CSW_TextInfo    ();

            void    AddLine         (LPCTSTR lpStr);
            void    Clean           (void);

protected:

    // Derives from its parent class
    virtual UINT    GetTotalLines   (void);
    virtual UINT    GetTotalCols    (void);
    virtual void    GetLineStr      (int nLine, CString& str);
};


// *************************************************************************
//
// Class to show binary text
//
// Call 'SetDataPtr' to set the memory address to show, the address even can be zero.
// The length is ingored if the editor is endless.
//
// *************************************************************************

class CSW_BDisplay : public CSW_EditorBase
{
private:
            LPBYTE  m_pData;
            UINT    m_Length;
            
            UINT    m_nBytesPerRow;

            UINT    m_TotalLines;
            UINT    m_TotalCols;

            BOOL    m_Endless;
public:

                    CSW_BDisplay    (void);

            // Use the buffer directlly
            BOOL    SetDataPtr      (DWORD pData, UINT nLen) { return SetDataPtr((LPBYTE)pData, nLen);};
            BOOL    SetDataPtr      (LPBYTE pData, UINT nLen);

            // The showing memory address is endless
            void    SetEndless      (BOOL bEndless) { m_Endless = bEndless;};
            // Increase lines
            void    IncreaseLines   (int nLines);

protected:

    virtual UINT    GetTotalLines   (void);
    virtual UINT    GetTotalCols    (void);

    virtual void    GetLineStr      (int nLine, CString& str);

    afx_msg void    OnVScroll       (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

    afx_msg void    OnKeyDown       (UINT nChar, UINT nRepCnt, UINT nFlags);

    DECLARE_MESSAGE_MAP()
};

#endif
