; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDataIODlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Inquire.h"
LastPage=0

ClassCount=7
Class1=CInquireApp
Class2=CInquireDoc
Class3=CInquireView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_INQUIRTYPE
Resource2=IDR_MAINFRAME
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDD_ABOUTBOX
Class7=CDataIODlg
Resource4=IDD_DATA_IO_DLG

[CLS:CInquireApp]
Type=0
HeaderFile=Inquire.h
ImplementationFile=Inquire.cpp
Filter=N
LastObject=CInquireApp

[CLS:CInquireDoc]
Type=0
HeaderFile=InquireDoc.h
ImplementationFile=InquireDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CInquireDoc

[CLS:CInquireView]
Type=0
HeaderFile=InquireView.h
ImplementationFile=InquireView.cpp
Filter=C
LastObject=CInquireView
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=C
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=Inquire.cpp
ImplementationFile=Inquire.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_INQUIRTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_REGISTRATION
Command16=ID_OPTION_FONT
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_APP_ABOUT
CommandCount=23

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_DATA_IO_DLG]
Type=1
Class=CDataIODlg
ControlCount=48
Control1=IDC_SUBMIT,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STUDENT_ID,edit,1350631424
Control5=IDC_STATIC,static,1342308352
Control6=IDC_NAME,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SPECIALITY_COMBO,combobox,1344339970
Control11=IDC_STATIC,static,1342308352
Control12=IDC_TELEPHONE,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_BIRTHPLACE,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_SEX_COMBO,combobox,1344339970
Control17=IDC_YEAR_SPIN,msctls_updown32,1342177442
Control18=IDC_STATIC,static,1350696961
Control19=IDC_YEAR_VAL,edit,1350631552
Control20=IDC_MONTH_SPIN,msctls_updown32,1342177442
Control21=IDC_STATIC,static,1350696961
Control22=IDC_MONTH_VAL,edit,1350631552
Control23=IDC_DAY_SPIN,msctls_updown32,1342177442
Control24=IDC_STATIC,static,1350696961
Control25=IDC_DAY_VAL,edit,1350631552
Control26=IDC_AGE,edit,1350633600
Control27=IDC_STATIC,static,1342308352
Control28=IDC_REGISTER_DATE,edit,1350633600
Control29=IDC_STATIC,static,1342308352
Control30=IDC_UPDATE_DATE,edit,1350633600
Control31=IDC_STATIC,static,1342308352
Control32=IDC_MAJOR_COMBO,combobox,1344339970
Control33=IDC_STATIC,button,1342177287
Control34=IDC_STATIC,static,1342308352
Control35=IDC_REC_TOTAL,edit,1350633600
Control36=IDC_STATIC,static,1342308352
Control37=IDC_REC_INDEX,edit,1350633600
Control38=IDC_SORT_KEY_COMBO,combobox,1344339971
Control39=IDC_STATIC,static,1342308352
Control40=IDC_RETRIEVE_KEY_COMBO,combobox,1344339971
Control41=IDC_STATIC,static,1342308352
Control42=IDC_PREV_REC,button,1342242817
Control43=IDC_NEXT_REC,button,1342242816
Control44=IDC_FIRST_REC,button,1342242817
Control45=IDC_LAST_REC,button,1342242816
Control46=IDC_RETRIEVE_COMBO,combobox,1344339971
Control47=IDC_STATIC,static,1342308352
Control48=IDC_DELETE,button,1342242817

[CLS:CDataIODlg]
Type=0
HeaderFile=resclass.h
ImplementationFile=resclass.cpp
BaseClass=CDialog
LastObject=CDataIODlg
Filter=D
VirtualFilter=dWC

