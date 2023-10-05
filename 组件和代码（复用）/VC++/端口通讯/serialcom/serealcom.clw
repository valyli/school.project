; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CComDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "serealcom.h"

ClassCount=4
Class1=CSerealcomApp
Class2=CSerealcomDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SEREALCOM_DIALOG
Class4=CComDlg
Resource4=IDD_DIALOG1

[CLS:CSerealcomApp]
Type=0
HeaderFile=serealcom.h
ImplementationFile=serealcom.cpp
Filter=N
LastObject=CSerealcomApp

[CLS:CSerealcomDlg]
Type=0
HeaderFile=serealcomDlg.h
ImplementationFile=serealcomDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSerealcomDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=serealcomDlg.h
ImplementationFile=serealcomDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SEREALCOM_DIALOG]
Type=1
Class=CSerealcomDlg
ControlCount=5
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG1]
Type=1
Class=CComDlg
ControlCount=2
Control1=IDC_COMBO1,combobox,1344340226
Control2=IDC_BUTTON1,button,1342242816

[CLS:CComDlg]
Type=0
HeaderFile=ComDlg.h
ImplementationFile=ComDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMBO1
VirtualFilter=dWC

