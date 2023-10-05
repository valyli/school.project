; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCPUDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CPU.h"

ClassCount=4
Class1=CCPUApp
Class2=CCPUDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_CPU_DIALOG

[CLS:CCPUApp]
Type=0
HeaderFile=CPU.h
ImplementationFile=CPU.cpp
Filter=N

[CLS:CCPUDlg]
Type=0
HeaderFile=CPUDlg.h
ImplementationFile=CPUDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CPUDlg.h
ImplementationFile=CPUDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CPU_DIALOG]
Type=1
Class=CCPUDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816

