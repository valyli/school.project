; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDCDrawDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DCDraw.h"

ClassCount=3
Class1=CDCDrawApp
Class2=CDCDrawDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DCDRAW_DIALOG

[CLS:CDCDrawApp]
Type=0
HeaderFile=DCDraw.h
ImplementationFile=DCDraw.cpp
Filter=N

[CLS:CDCDrawDlg]
Type=0
HeaderFile=DCDrawDlg.h
ImplementationFile=DCDrawDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_DRAWIT

[CLS:CAboutDlg]
Type=0
HeaderFile=DCDrawDlg.h
ImplementationFile=DCDrawDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DCDRAW_DIALOG]
Type=1
Class=CDCDrawDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_DRAWIT,button,1342242816

