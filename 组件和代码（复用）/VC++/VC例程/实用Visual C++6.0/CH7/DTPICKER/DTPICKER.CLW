; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDtpickerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dtpicker.h"

ClassCount=3
Class1=CDtpickerApp
Class2=CDtpickerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DTPICKER_DIALOG

[CLS:CDtpickerApp]
Type=0
HeaderFile=dtpicker.h
ImplementationFile=dtpicker.cpp
Filter=N

[CLS:CDtpickerDlg]
Type=0
HeaderFile=dtpickerDlg.h
ImplementationFile=dtpickerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_MYTIME

[CLS:CAboutDlg]
Type=0
HeaderFile=dtpickerDlg.h
ImplementationFile=dtpickerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DTPICKER_DIALOG]
Type=1
Class=CDtpickerDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MYDATE,SysDateTimePick32,1342242848
Control4=IDC_MYTIME,SysDateTimePick32,1342242857

