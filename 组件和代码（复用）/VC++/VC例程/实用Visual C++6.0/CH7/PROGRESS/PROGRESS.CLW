; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CScroll
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Progress.h"

ClassCount=4
Class1=CProgressApp
Class2=CProgressDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PROGRESS_DIALOG
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDD_PROGRESS_DIALOG (English (U.S.))
Class4=CScroll
Resource6=IDD_DIALOG1

[CLS:CProgressApp]
Type=0
HeaderFile=Progress.h
ImplementationFile=Progress.cpp
Filter=N

[CLS:CProgressDlg]
Type=0
HeaderFile=ProgressDlg.h
ImplementationFile=ProgressDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CProgressDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ProgressDlg.h
ImplementationFile=ProgressDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg


[DLG:IDD_PROGRESS_DIALOG]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Class=CProgressDlg

[DLG:IDD_PROGRESS_DIALOG (English (U.S.))]
Type=1
Class=CProgressDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MY_PROGRESS,msctls_progress32,1350565888
Control4=IDC_STEPIT,button,1342242816

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG1]
Type=1
Class=CScroll
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SCROLLBAR1,scrollbar,1342177282
Control4=IDC_SCROLLBAR2,scrollbar,1342177285

[CLS:CScroll]
Type=0
HeaderFile=Scroll.h
ImplementationFile=Scroll.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SCROLLBAR1

