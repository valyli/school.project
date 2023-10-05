; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CListDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "list.h"

ClassCount=3
Class1=CListApp
Class2=CListDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_LIST_DIALOG

[CLS:CListApp]
Type=0
HeaderFile=list.h
ImplementationFile=list.cpp
Filter=N

[CLS:CListDlg]
Type=0
HeaderFile=listDlg.h
ImplementationFile=listDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST2

[CLS:CAboutDlg]
Type=0
HeaderFile=listDlg.h
ImplementationFile=listDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_mem,static,1342308353

[DLG:IDD_LIST_DIALOG]
Type=1
Class=CListDlg
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_LIST2,SysListView32,1350631681
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1342242816
Control5=IDC_STATIC,static,1342177283

