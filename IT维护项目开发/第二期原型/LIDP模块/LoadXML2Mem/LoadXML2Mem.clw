; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CXmlTreeViewCtrl
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "LoadXML2Mem.h"

ClassCount=4
Class1=CLoadXML2MemApp
Class2=CLoadXML2MemDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CXmlTreeViewCtrl
Resource3=IDD_LOADXML2MEM_DIALOG

[CLS:CLoadXML2MemApp]
Type=0
HeaderFile=LoadXML2Mem.h
ImplementationFile=LoadXML2Mem.cpp
Filter=N

[CLS:CLoadXML2MemDlg]
Type=0
HeaderFile=LoadXML2MemDlg.h
ImplementationFile=LoadXML2MemDlg.cpp
Filter=D
LastObject=CLoadXML2MemDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=LoadXML2MemDlg.h
ImplementationFile=LoadXML2MemDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LOADXML2MEM_DIALOG]
Type=1
Class=CLoadXML2MemDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_TEST,button,1342242816
Control4=IDC_TREE_XML,SysTreeView32,1350631431

[CLS:CXmlTreeViewCtrl]
Type=0
HeaderFile=XmlTreeViewCtrl.h
ImplementationFile=XmlTreeViewCtrl.cpp
BaseClass=CTreeCtrl
Filter=W
LastObject=CXmlTreeViewCtrl

