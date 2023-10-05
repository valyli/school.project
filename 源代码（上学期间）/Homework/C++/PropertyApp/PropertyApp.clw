; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPageB
LastTemplate=CPropertySheet
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PropertyApp.h"
LastPage=0

ClassCount=8
Class1=CPropertyAppApp
Class2=CPropertyAppDoc
Class3=CPropertyAppView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_DIALOG1
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Resource3=IDR_MAINFRAME
Class6=CPageA
Class7=CPageB
Class8=PropSheet
Resource4=IDD_DIALOG2

[CLS:CPropertyAppApp]
Type=0
HeaderFile=PropertyApp.h
ImplementationFile=PropertyApp.cpp
Filter=N

[CLS:CPropertyAppDoc]
Type=0
HeaderFile=PropertyAppDoc.h
ImplementationFile=PropertyAppDoc.cpp
Filter=N

[CLS:CPropertyAppView]
Type=0
HeaderFile=PropertyAppView.h
ImplementationFile=PropertyAppView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CPropertyAppView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=PropertyApp.cpp
ImplementationFile=PropertyApp.cpp
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
Command1=ID_FUN_PROP
Command2=ID_APP_EXIT
Command3=ID_APP_ABOUT
CommandCount=3

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_DIALOG1]
Type=1
Class=CPageA
ControlCount=1
Control1=IDC_EDIT,edit,1350631552

[DLG:IDD_DIALOG2]
Type=1
Class=CPageB
ControlCount=1
Control1=IDC_CHECK,button,1342242819

[CLS:CPageA]
Type=0
HeaderFile=PageA.h
ImplementationFile=PageA.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPageA
VirtualFilter=idWC

[CLS:CPageB]
Type=0
HeaderFile=PageB.h
ImplementationFile=PageB.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CPageB
VirtualFilter=idWC

[CLS:PropSheet]
Type=0
HeaderFile=PropSheet.h
ImplementationFile=PropSheet.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=ID_APP_ABOUT

