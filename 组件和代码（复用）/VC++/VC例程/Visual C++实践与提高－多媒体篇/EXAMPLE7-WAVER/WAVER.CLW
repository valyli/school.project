; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWaverDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "waver.h"

ClassCount=4
Class1=CWaverApp
Class2=CWaverDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_WAVER_DIALOG
Class4=displaydlg
Resource4=IDD_DISPLAY

[CLS:CWaverApp]
Type=0
HeaderFile=waver.h
ImplementationFile=waver.cpp
Filter=N
LastObject=CWaverApp

[CLS:CWaverDlg]
Type=0
HeaderFile=waverDlg.h
ImplementationFile=waverDlg.cpp
Filter=D
LastObject=CWaverDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=waverDlg.h
ImplementationFile=waverDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_WAVER_DIALOG]
Type=1
Class=CWaverDlg
ControlCount=8
Control1=IDC_PLAY,button,1342242816
Control2=IDC_OPEN,button,1342242816
Control3=IDC_RECORD,button,1342242816
Control4=IDC_STOP,button,1342242816
Control5=IDC_SAVE,button,1342242816
Control6=IDC_INFO,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATUS,static,1342308352

[DLG:IDD_DISPLAY]
Type=1
Class=displaydlg
ControlCount=11
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ENAME,edit,1484849280
Control8=IDC_ECHANNEL,edit,1484849280
Control9=IDC_ESAM,edit,1484849280
Control10=IDC_ELONG,edit,1484849280
Control11=IDC_EBIT,edit,1484849280

[CLS:displaydlg]
Type=0
HeaderFile=displaydlg.h
ImplementationFile=displaydlg.cpp
BaseClass=CDialog
Filter=D
LastObject=displaydlg
VirtualFilter=dWC

