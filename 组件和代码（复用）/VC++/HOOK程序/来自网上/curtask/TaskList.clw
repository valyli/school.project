; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTaskListDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TaskList.h"

ClassCount=3
Class1=CTaskListApp
Class2=CTaskListDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TASKLIST_DIALOG
Resource4=IDD_TASKLIST_DIALOG (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))

[CLS:CTaskListApp]
Type=0
HeaderFile=TaskList.h
ImplementationFile=TaskList.cpp
Filter=N

[CLS:CTaskListDlg]
Type=0
HeaderFile=TaskListDlg.h
ImplementationFile=TaskListDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST1

[CLS:CAboutDlg]
Type=0
HeaderFile=TaskListDlg.h
ImplementationFile=TaskListDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_TASKLIST_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CTaskListDlg

[DLG:IDD_TASKLIST_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_LIST1,listbox,1352728835

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

