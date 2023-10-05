; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMouseMsgDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MouseMsg.h"

ClassCount=4
Class1=CMouseMsgApp
Class2=CMouseMsgDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_MOUSEMSG_DIALOG

[CLS:CMouseMsgApp]
Type=0
HeaderFile=MouseMsg.h
ImplementationFile=MouseMsg.cpp
Filter=N

[CLS:CMouseMsgDlg]
Type=0
HeaderFile=MouseMsgDlg.h
ImplementationFile=MouseMsgDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MouseMsgDlg.h
ImplementationFile=MouseMsgDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MOUSEMSG_DIALOG]
Type=1
Class=CMouseMsgDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

