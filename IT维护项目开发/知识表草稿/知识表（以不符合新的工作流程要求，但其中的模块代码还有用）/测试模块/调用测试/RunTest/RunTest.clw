; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRunTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RunTest.h"

ClassCount=4
Class1=CRunTestApp
Class2=CRunTestDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_RUNTEST_DIALOG

[CLS:CRunTestApp]
Type=0
HeaderFile=RunTest.h
ImplementationFile=RunTest.cpp
Filter=N

[CLS:CRunTestDlg]
Type=0
HeaderFile=RunTestDlg.h
ImplementationFile=RunTestDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=RunTestDlg.h
ImplementationFile=RunTestDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_RUNTEST_DIALOG]
Type=1
Class=CRunTestDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_CHECKSYSTEMVERSION,button,1342242816
Control4=IDC_BUTTON_CHECKDLLVERSION,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_BUTTON_CHECK_BIOS,button,1342242816
Control8=IDC_BUTTON_CHECK_HARDDISK,button,1342242816

