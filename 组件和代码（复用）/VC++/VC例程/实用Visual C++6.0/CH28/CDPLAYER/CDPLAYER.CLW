; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCDPlayerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CDPlayer.h"

ClassCount=4
Class1=CCDPlayerApp
Class2=CCDPlayerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CDPLAYER_DIALOG

[CLS:CCDPlayerApp]
Type=0
HeaderFile=CDPlayer.h
ImplementationFile=CDPlayer.cpp
Filter=N

[CLS:CCDPlayerDlg]
Type=0
HeaderFile=CDPlayerDlg.h
ImplementationFile=CDPlayerDlg.cpp
Filter=D

[CLS:CAboutDlg]
Type=0
HeaderFile=CDPlayerDlg.h
ImplementationFile=CDPlayerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CDPLAYER_DIALOG]
Type=1
Class=CCDPlayerDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

