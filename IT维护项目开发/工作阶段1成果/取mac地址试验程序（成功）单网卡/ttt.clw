; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTttDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ttt.h"

ClassCount=4
Class1=CTttApp
Class2=CTttDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TTT_DIALOG

[CLS:CTttApp]
Type=0
HeaderFile=ttt.h
ImplementationFile=ttt.cpp
Filter=N

[CLS:CTttDlg]
Type=0
HeaderFile=tttDlg.h
ImplementationFile=tttDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=tttDlg.h
ImplementationFile=tttDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TTT_DIALOG]
Type=1
Class=CTttDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816

