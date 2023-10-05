; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShapesDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Shapes.h"

ClassCount=3
Class1=CShapesApp
Class2=CShapesDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SHAPES_DIALOG

[CLS:CShapesApp]
Type=0
HeaderFile=Shapes.h
ImplementationFile=Shapes.cpp
Filter=N

[CLS:CShapesDlg]
Type=0
HeaderFile=ShapesDlg.h
ImplementationFile=ShapesDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ShapesDlg.h
ImplementationFile=ShapesDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SHAPES_DIALOG]
Type=1
Class=CShapesDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,SysListView32,1350631427
Control4=IDC_TREE1,SysTreeView32,1350631431
Control5=IDC_COMBOBOXEX1,ComboBoxEx32,1344340227

