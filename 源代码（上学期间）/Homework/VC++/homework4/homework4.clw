; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=SelStyleDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "homework4.h"
LastPage=0

ClassCount=6
Class1=CHomework4App
Class2=CHomework4Doc
Class3=CHomework4View
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=SelStyleDlg
Resource3=IDD_DIALOG_SEL_STYLE

[CLS:CHomework4App]
Type=0
HeaderFile=homework4.h
ImplementationFile=homework4.cpp
Filter=N

[CLS:CHomework4Doc]
Type=0
HeaderFile=homework4Doc.h
ImplementationFile=homework4Doc.cpp
Filter=N

[CLS:CHomework4View]
Type=0
HeaderFile=homework4View.h
ImplementationFile=homework4View.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CHomework4View


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=homework4.cpp
ImplementationFile=homework4.cpp
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
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_APP_ABOUT
CommandCount=11

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

[DLG:IDD_DIALOG_SEL_STYLE]
Type=1
Class=SelStyleDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO_SEL_STYLE,combobox,1344340226
Control4=IDC_EDIT_X,edit,1350639746
Control5=IDC_EDIT_Y,edit,1350639746

[CLS:SelStyleDlg]
Type=0
HeaderFile=SelStyleDlg.h
ImplementationFile=SelStyleDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

