; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRotaryPropPage
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Rotary.h"
CDK=Y

ClassCount=2
Class1=CRotaryCtrl
Class2=CRotaryPropPage

ResourceCount=2
LastPage=0
Resource1=IDD_ABOUTBOX_ROTARY
Resource2=IDD_PROPPAGE_ROTARY

[CLS:CRotaryCtrl]
Type=0
HeaderFile=RotaryCtl.h
ImplementationFile=RotaryCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=CRotaryCtrl

[CLS:CRotaryPropPage]
Type=0
HeaderFile=RotaryPpg.h
ImplementationFile=RotaryPpg.cpp
Filter=D
BaseClass=COlePropertyPage
VirtualFilter=idWC
LastObject=IDC_NUM_TICKS

[DLG:IDD_ABOUTBOX_ROTARY]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_ROTARY]
Type=1
Class=CRotaryPropPage
ControlCount=4
Control1=IDC_TICKS_ENABLED,button,1342242819
Control2=IDC_NUM_TICKS,edit,1350639744
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SPIN1,msctls_updown32,1342177330

