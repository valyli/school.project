; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CButtonDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Button.h"

ClassCount=4
Class1=CButtonApp
Class2=CButtonDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_BUTTON_DIALOG

[CLS:CButtonApp]
Type=0
HeaderFile=Button.h
ImplementationFile=Button.cpp
Filter=N

[CLS:CButtonDlg]
Type=0
HeaderFile=ButtonDlg.h
ImplementationFile=ButtonDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ButtonDlg.h
ImplementationFile=ButtonDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BUTTON_DIALOG]
Type=1
Class=CButtonDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SHOW_HIDE,button,1342242816
Control4=IDC_ENABLE_DISABLE,button,1342242816
Control5=IDC_LEFT,button,1342242816
Control6=IDC_CENTER,button,1342242816
Control7=IDC_RIGHT,button,1342242816

