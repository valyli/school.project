; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CExCDDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "exCD.h"

ClassCount=4
Class1=CExCDApp
Class2=CExCDDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_EXCD_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=exsetdlg
Resource4=IDD_SET

[CLS:CExCDApp]
Type=0
HeaderFile=exCD.h
ImplementationFile=exCD.cpp
Filter=N
LastObject=CExCDApp

[CLS:CExCDDlg]
Type=0
HeaderFile=exCDDlg.h
ImplementationFile=exCDDlg.cpp
Filter=D
LastObject=CExCDDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=exCDDlg.h
ImplementationFile=exCDDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EXCD_DIALOG]
Type=1
Class=CExCDDlg
ControlCount=9
Control1=IDC_TRACK,combobox,1344339970
Control2=IDC_STATIC,static,1342308352
Control3=IDC_PLAY,button,1342242816
Control4=IDC_PLAYMODE,button,1342242816
Control5=IDC_PAUSE,button,1342242816
Control6=IDC_LAST,button,1342242816
Control7=IDC_NEXT,button,1342242816
Control8=IDC_EJECT,button,1342242816
Control9=IDC_STOP,button,1342242816

[DLG:IDD_SET]
Type=1
Class=exsetdlg
ControlCount=10
Control1=IDC_FMINI,edit,1350631552
Control2=IDC_FSECOND,edit,1350631552
Control3=IDC_TMINI,edit,1350631552
Control4=IDC_TSECOND,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_BUTTON1,button,1342242816
Control10=IDC_BUTTON2,button,1342242816

[CLS:exsetdlg]
Type=0
HeaderFile=exsetdlg.h
ImplementationFile=exsetdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=exsetdlg
VirtualFilter=dWC

