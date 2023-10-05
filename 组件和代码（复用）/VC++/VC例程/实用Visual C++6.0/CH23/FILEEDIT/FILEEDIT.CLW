; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFileEditDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FileEdit.h"

ClassCount=3
Class1=CFileEditApp
Class2=CFileEditDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_FILEEDIT_DIALOG

[CLS:CFileEditApp]
Type=0
HeaderFile=FileEdit.h
ImplementationFile=FileEdit.cpp
Filter=N

[CLS:CFileEditDlg]
Type=0
HeaderFile=FileEditDlg.h
ImplementationFile=FileEditDlg.cpp
Filter=D
LastObject=IDOK
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=FileEditDlg.h
ImplementationFile=FileEditDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_FILEEDIT_DIALOG]
Type=1
Class=CFileEditDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FILEEDIT,edit,1350631556

