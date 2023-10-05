; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "sameball.h"
LastPage=0

ClassCount=6
Class1=CChildView
Class2=CMainFrame
Class3=CNameInDlg
Class4=CSameBallApp
Class5=CAboutDlg
Class6=CScoreList

ResourceCount=4
Resource1=IDD_DIALOG1
Resource2=IDD_DIALOG2
Resource3=IDD_ABOUTBOX
Resource4=IDR_MAINFRAME

[CLS:CChildView]
Type=0
BaseClass=CWnd 
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=W
VirtualFilter=WC
LastObject=CChildView

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=IDM_REGENDER
Filter=T
VirtualFilter=fWC

[CLS:CNameInDlg]
Type=0
BaseClass=CDialog
HeaderFile=NameInDlg.h
ImplementationFile=NameInDlg.cpp
LastObject=CNameInDlg
Filter=D
VirtualFilter=dWC

[CLS:CSameBallApp]
Type=0
BaseClass=CWinApp
HeaderFile=SameBall.h
ImplementationFile=SameBall.cpp
Filter=N
VirtualFilter=AC
LastObject=CSameBallApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SameBall.cpp
ImplementationFile=SameBall.cpp

[CLS:CScoreList]
Type=0
BaseClass=CDialog
HeaderFile=ScoreList.h
ImplementationFile=ScoreList.cpp
LastObject=IDC_MESSAGE
Filter=D
VirtualFilter=dWC

[DLG:IDD_DIALOG1]
Type=1
Class=CNameInDlg
ControlCount=2
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG2]
Type=1
Class=CScoreList
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDC_NAME1,static,1342308864
Control3=IDC_NAME5,static,1342308864
Control4=IDC_NAME4,static,1342308864
Control5=IDC_NAME3,static,1342308864
Control6=IDC_NAME2,static,1342308864
Control7=IDC_MESSAGE,static,1342308864
Control8=IDC_SCORE1,static,1342308864
Control9=IDC_SCORE2,static,1342308864
Control10=IDC_SCORE3,static,1342308864
Control11=IDC_SCORE4,static,1342308864
Control12=IDC_SCORE5,static,1342308864

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_APP_EXIT
Command3=ID_EDIT_UNDO
Command4=IDM_REGENDER
Command5=ID_VIEW_SCORELIST
Command6=ID_VIEW_STATUS_BAR
Command7=ID_HELP
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_VIEW_SCORELIST
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_UNDO
CommandCount=4

