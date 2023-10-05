; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CListsDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Lists.h"

ClassCount=3
Class1=CListsApp
Class2=CListsDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_LISTS_DIALOG

[CLS:CListsApp]
Type=0
HeaderFile=Lists.h
ImplementationFile=Lists.cpp
Filter=N

[CLS:CListsDlg]
Type=0
HeaderFile=ListsDlg.h
ImplementationFile=ListsDlg.cpp
Filter=D
LastObject=IDC_SUB_DIRS
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ListsDlg.h
ImplementationFile=ListsDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LISTS_DIALOG]
Type=1
Class=CListsDlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_MAIN_DIR,combobox,1344340227
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FILES_TREE,SysTreeView32,1350631431
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SUB_DIRS,listbox,1352730627
Control8=IDC_STATIC,static,1342308352
Control9=IDC_SELECTED_DIRS,SysListView32,1350631425

