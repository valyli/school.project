; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPsManagerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "psManager.h"

ClassCount=4
Class1=CPsManagerApp
Class2=CPsManagerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_PSMANAGER_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CConfirmTermination
Resource4=IDD_CONFIRM_TERMINATION

[CLS:CPsManagerApp]
Type=0
HeaderFile=psManager.h
ImplementationFile=psManager.cpp
Filter=N

[CLS:CPsManagerDlg]
Type=0
HeaderFile=psManagerDlg.h
ImplementationFile=psManagerDlg.cpp
Filter=D
LastObject=CPsManagerDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=psManagerDlg.h
ImplementationFile=psManagerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PSMANAGER_DIALOG]
Type=1
Class=CPsManagerDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_REFRESH,button,1342242816
Control3=IDC_STATIC,static,1342177294
Control4=IDC_PROCESS_LIST,SysListView32,1350631429
Control5=IDC_TERMINATE,button,1342242816
Control6=IDC_HAISAN,static,1342308620

[DLG:IDD_CONFIRM_TERMINATION]
Type=1
Class=CConfirmTermination
ControlCount=5
Control1=IDYES,button,1342242817
Control2=IDNO,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PROCESS_ID,edit,1342244992
Control5=IDC_PROCESS_PATH,edit,1342244992

[CLS:CConfirmTermination]
Type=0
HeaderFile=ConfirmTermination.h
ImplementationFile=ConfirmTermination.cpp
BaseClass=CDialog
Filter=D
LastObject=IDNO
VirtualFilter=dWC

