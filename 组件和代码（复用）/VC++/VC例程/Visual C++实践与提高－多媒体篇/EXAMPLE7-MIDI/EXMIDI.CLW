; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CExmidiDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "exmidi.h"

ClassCount=3
Class1=CExmidiApp
Class2=CExmidiDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_EXMIDI_DIALOG

[CLS:CExmidiApp]
Type=0
HeaderFile=exmidi.h
ImplementationFile=exmidi.cpp
Filter=N

[CLS:CExmidiDlg]
Type=0
HeaderFile=exmidiDlg.h
ImplementationFile=exmidiDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CExmidiDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=exmidiDlg.h
ImplementationFile=exmidiDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_EXMIDI_DIALOG]
Type=1
Class=CExmidiDlg
ControlCount=9
Control1=IDC_SLIDER,msctls_trackbar32,1342242840
Control2=IDC_OPEN,button,1342242816
Control3=IDC_PLAY,button,1342242816
Control4=IDC_PAUSE,button,1342242816
Control5=IDC_CLOSE,button,1342242816
Control6=IDC_BACK,button,1342242816
Control7=IDC_AHEAD,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_WTIME,static,1342308352

