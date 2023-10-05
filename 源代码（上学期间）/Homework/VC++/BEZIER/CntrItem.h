// CntrItem.h : interface of the CBezierCntrItem class
//

#if !defined(AFX_CNTRITEM_H__633DED01_5C1B_45A5_A2B7_24632E8F5E2D__INCLUDED_)
#define AFX_CNTRITEM_H__633DED01_5C1B_45A5_A2B7_24632E8F5E2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBezierDoc;
class CBezierView;

class CBezierCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CBezierCntrItem)

// Constructors
public:
	CBezierCntrItem(CBezierDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CBezierDoc* GetDocument()
		{ return (CBezierDoc*)COleClientItem::GetDocument(); }
	CBezierView* GetActiveView()
		{ return (CBezierView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBezierCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CBezierCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__633DED01_5C1B_45A5_A2B7_24632E8F5E2D__INCLUDED_)
