; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSdimenuView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "sdimenu.h"
LastPage=0

ClassCount=5
Class1=CSdimenuApp
Class2=CSdimenuDoc
Class3=CSdimenuView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDR_MYCONTEXT
Resource3=IDD_ABOUTBOX

[CLS:CSdimenuApp]
Type=0
HeaderFile=sdimenu.h
ImplementationFile=sdimenu.cpp
Filter=N

[CLS:CSdimenuDoc]
Type=0
HeaderFile=sdimenuDoc.h
ImplementationFile=sdimenuDoc.cpp
Filter=N

[CLS:CSdimenuView]
Type=0
HeaderFile=sdimenuView.h
ImplementationFile=sdimenuView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_CONTEXT_ITEM1
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=sdimenu.cpp
ImplementationFile=sdimenu.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_LIST1,listbox,1352728835

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_MYHEADER_SUBMENU
Command18=ID_MYHEADER_MYSBUONE
Command19=ID_MYHEADER_SUBTWO
Command20=ID_MYHEADER_SUBTHREE
CommandCount=20

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

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MYCONTEXT]
Type=1
Class=?
Command1=ID_CONTEXT_ITEM1
Command2=ID_CONTEXT_ITEM2
Command3=ID_CONTEXT_ITEM3
Command4=ID_CONTEXT_ITEM4
CommandCount=4

