; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CModeless
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MLaunch.h"

ClassCount=4
Class1=CMLaunchApp
Class2=CMLaunchDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_MLAUNCH_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CModeless
Resource4=IDD_MODELESS

[CLS:CMLaunchApp]
Type=0
HeaderFile=MLaunch.h
ImplementationFile=MLaunch.cpp
Filter=N

[CLS:CMLaunchDlg]
Type=0
HeaderFile=MLaunchDlg.h
ImplementationFile=MLaunchDlg.cpp
Filter=D
LastObject=CMLaunchDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MLaunchDlg.h
ImplementationFile=MLaunchDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MLAUNCH_DIALOG]
Type=1
Class=CMLaunchDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_START_MODELESS,button,1342242816
Control4=IDC_SOP_MODELESS,button,1342242816
Control5=IDC_LIST1,listbox,1352728835

[DLG:IDD_MODELESS]
Type=1
Class=CModeless
ControlCount=3
Control1=IDC_POP,button,1342242816
Control2=IDC_POW,button,1342242816
Control3=IDC_EDIT1,edit,1350631552

[CLS:CModeless]
Type=0
HeaderFile=Modeless.h
ImplementationFile=Modeless.cpp
BaseClass=CDialog
Filter=D
LastObject=CModeless
VirtualFilter=dWC

