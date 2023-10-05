// hotspot4.h : main header file for the HOTSPOT4 application
//

//Maximum number of vertices per hotspot.
#define MAX_POINTS 100

//Constants for program mode.
#define TEST -1
#define DEFINE 1

//Name of hotlink data file.
#define LINKFILENAME "POLYHOTS.DAT"

//Structure to hold polygonal hotspots.
struct HotSpotRecord {
	char image[128];
	char target[128];
	int num_points;
	CPoint points[MAX_POINTS];
	};

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHotspot4App:
// See hotspot4.cpp for the implementation of this class
//

class CHotspot4App : public CWinApp
{
public:
	CHotspot4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotspot4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHotspot4App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
