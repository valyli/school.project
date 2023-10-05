// EnumIconsDlg.h : Header-Datei
//

#if !defined(AFX_ENUMICONSDLG_H__CBDE8F01_518C_4F93_9067_71A161996008__INCLUDED_)
#define AFX_ENUMICONSDLG_H__CBDE8F01_518C_4F93_9067_71A161996008__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEnumIconsDlg Dialogfeld

class CEnumIconsDlg : public CDialog
{
// Konstruktion
public:
	CEnumIconsDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CEnumIconsDlg)
	enum { IDD = IDD_ENUMICONS_DIALOG };
		// HINWEIS: der Klassenassistent fügt an dieser Stelle Datenelemente (Members) ein
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CEnumIconsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CEnumIconsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnEnumIcons();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ENUMICONSDLG_H__CBDE8F01_518C_4F93_9067_71A161996008__INCLUDED_)
