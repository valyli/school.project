; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShutDownDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ShutDown.h"

ClassCount=6
Class1=CShutDownApp
Class2=CShutDownDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_PWDDLG
Resource2=IDR_MAINFRAME
Resource3=IDD_SHUTDOWN_DIALOG
Resource4=IDD_DIALOG_INPUT
Class4=CPwdDlg
Resource5=IDD_KEYDLG
Class5=CKeyDlg
Resource6=IDD_ABOUTBOX
Class6=CInput
Resource7=IDR_MENU_MAIN

[CLS:CShutDownApp]
Type=0
HeaderFile=ShutDown.h
ImplementationFile=ShutDown.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CShutDownApp

[CLS:CShutDownDlg]
Type=0
HeaderFile=ShutDownDlg.h
ImplementationFile=ShutDownDlg.cpp
Filter=D
LastObject=CShutDownDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ShutDownDlg.h
ImplementationFile=ShutDownDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC_MAIL,static,1342308864

[DLG:IDD_SHUTDOWN_DIALOG]
Type=1
Class=CShutDownDlg
ControlCount=27
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342177283
Control3=IDC_STATIC_NOW,static,1342308865
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_BUTTON_HIDE,button,1342242816
Control7=IDC_BUTTON_SHUTDOWN,button,1342242816
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STATIC,static,1342312961
Control10=IDC_STATIC,static,1342312961
Control11=IDC_STATIC,static,1342312961
Control12=IDC_STATIC,static,1342312961
Control13=IDC_STATIC,static,1342312961
Control14=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242857
Control15=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242857
Control16=IDC_DATETIMEPICKER3,SysDateTimePick32,1342242857
Control17=IDC_DATETIMEPICKER4,SysDateTimePick32,1342242857
Control18=IDC_DATETIMEPICKER5,SysDateTimePick32,1342242857
Control19=IDC_STATIC,static,1342181384
Control20=IDC_STATIC,button,1342177287
Control21=IDC_CHECK1,button,1342242819
Control22=IDC_CHECK2,button,1342242819
Control23=IDC_CHECK3,button,1342242819
Control24=IDC_CHECK4,button,1342242819
Control25=IDC_CHECK5,button,1342242819
Control26=IDC_STATIC,static,1342181384
Control27=IDC_STATIC,static,1342181384

[MNU:IDR_MENU_MAIN]
Type=1
Class=CShutDownDlg
Command1=ID_MENU_MAIN
Command2=ID_MENU_NOWSHUT
Command3=ID_MENU_REBOOT
Command4=ID_MENU_OUT
Command5=ID_MENU_CLOSE
Command6=ID_MENU_SHORTCUT
Command7=ID_MENU_SYSTEM
Command8=ID_MENU_PASSWORD
Command9=ID_MENU_IDLEMIN
Command10=ID_MENU_ABORT
Command11=ID_MENU_EXIT
CommandCount=11

[CLS:CPwdDlg]
Type=0
HeaderFile=PwdDlg.h
ImplementationFile=PwdDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CPwdDlg

[DLG:IDD_PWDDLG]
Type=1
Class=CPwdDlg
ControlCount=9
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342177283
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_KEYDLG]
Type=1
Class=CKeyDlg
ControlCount=10
Control1=IDC_EDIT_OLDKEY,edit,1350631584
Control2=IDC_EDIT_NEWKEY,edit,1350631584
Control3=IDC_EDIT_NEWKEYOK,edit,1350631584
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308864
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342177283

[CLS:CKeyDlg]
Type=0
HeaderFile=KeyDlg.h
ImplementationFile=KeyDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_DIALOG_INPUT]
Type=1
Class=CInput
ControlCount=5
Control1=IDC_EDIT_STRING,edit,1350639744
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC_TITLE,static,1342308352
Control5=IDC_STATIC,static,1342177283

[CLS:CInput]
Type=0
HeaderFile=Input.h
ImplementationFile=Input.cpp
BaseClass=CDialog
Filter=D
LastObject=CInput

