; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CEditsDlg
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Edits.h"

ClassCount=4
Class1=CEditsApp
Class2=CEditsDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CInitials
Resource3=IDD_EDITS_DIALOG

[CLS:CEditsApp]
Type=0
HeaderFile=Edits.h
ImplementationFile=Edits.cpp
Filter=N

[CLS:CEditsDlg]
Type=0
HeaderFile=EditsDlg.h
ImplementationFile=EditsDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_SECOND

[CLS:CAboutDlg]
Type=0
HeaderFile=EditsDlg.h
ImplementationFile=EditsDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EDITS_DIALOG]
Type=1
Class=CEditsDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_FIRST,edit,1350631552
Control5=IDC_GET_TEXT,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_SECOND,edit,1350631552
Control8=IDC_EDIT_SHOW,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_INITIAL,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT2,edit,1350631552

[CLS:CInitials]
Type=0
HeaderFile=Initials.h
ImplementationFile=Initials.cpp
BaseClass=CEdit
Filter=W
LastObject=CInitials
VirtualFilter=WC

