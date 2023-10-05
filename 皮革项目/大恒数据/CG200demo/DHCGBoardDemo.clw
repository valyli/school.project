; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDHCGBoardDemoView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DHCGBoardDemo.h"
LastPage=0

ClassCount=7
Class1=CDHCGBoardDemoApp
Class2=CDHCGBoardDemoDoc
Class3=CDHCGBoardDemoView
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_PROPPAGE1_IMAGESET
Class5=CAboutDlg
Resource2=IDD_AVERAGENUM_DLG
Class6=CAverageNumDlg
Resource3=IDD_ABOUTBOX
Resource4=IDD_PROPPAGE2_SOURCE
Resource5=IDD_PROPPAGE4_FIELD
Resource6=IDR_MAINFRAME
Resource7=IDD_PROPPAGE3_COLOR
Class7=CdlgMask
Resource8=IDD_PROPPAGE5_WINDOWS

[CLS:CDHCGBoardDemoApp]
Type=0
HeaderFile=DHCGBoardDemo.h
ImplementationFile=DHCGBoardDemo.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=ID_FILE_SAVE

[CLS:CDHCGBoardDemoDoc]
Type=0
HeaderFile=DHCGBoardDemoDoc.h
ImplementationFile=DHCGBoardDemoDoc.cpp
Filter=N
LastObject=CDHCGBoardDemoDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CDHCGBoardDemoView]
Type=0
HeaderFile=DHCGBoardDemoView.h
ImplementationFile=DHCGBoardDemoView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_CGCARD_SNAP


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=DHCGBoardDemo.cpp
ImplementationFile=DHCGBoardDemo.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=20
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342177287
Control6=IDC_STATIC,static,1342308994
Control7=IDC_STATIC,static,1342308994
Control8=IDC_STATIC,static,1342308994
Control9=IDC_STATIC,static,1342308994
Control10=IDC_STATIC,static,1342308994
Control11=IDC_STATIC,static,1342308994
Control12=IDC_STATIC,static,1342308994
Control13=IDC_PHYSICAL_MEM,static,1342308992
Control14=IDC_AVAIL_VIRTUAL_MEM,static,1342308992
Control15=IDC_AVAIL_MEM,static,1342308992
Control16=IDC_CPU,static,1342308992
Control17=IDC_OS,static,1342308992
Control18=IDC_TOTAL_SPACE,static,1342308992
Control19=IDC_FREE_SPACE,static,1342308992
Control20=IDC_DHIMAGE,static,1342308864

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE_AS
Command4=ID_FILE_PRINT
Command5=ID_FILE_PRINT_PREVIEW
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_CGCARD_MODE_DIRECTX
Command10=ID_CGCARD_MODE_SCREEN
Command11=ID_CGCARD_ATUOFORMAT
Command12=ID_CGCARD_PARAM
Command13=ID_CGCARD_CG210PARA
Command14=ID_CGCARD_SNAP
Command15=ID_CGCARD_MEM
Command16=ID_CGBOARD_CAPTUREMEM
Command17=ID_CGBOARD_MASK
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_APP_ABOUT
CommandCount=20

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE_AS
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_CGBOARDPLAY
Command9=ID_CGBOARDSTOP
Command10=ID_APP_ABOUT
CommandCount=10

[DLG:IDD_AVERAGENUM_DLG]
Type=1
Class=CAverageNumDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_AVENUM,edit,1350639617
Control4=IDC_AVEDLG_TISHI,static,1342308352
Control5=IDC_STATIC,static,1342308865
Control6=IDC_SPIN_NUM,msctls_updown32,1342177312

[CLS:CAverageNumDlg]
Type=0
HeaderFile=AverageNumDlg.h
ImplementationFile=AverageNumDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAverageNumDlg
VirtualFilter=dWC

[DLG:IDD_PROPPAGE1_IMAGESET]
Type=1
Class=?
ControlCount=21
Control1=IDC_Brightness,static,1342177280
Control2=IDC_BRIGHTNESS_SB,scrollbar,1342373888
Control3=IDC_BriNum,static,1342312961
Control4=IDC_Contrast,static,1342177280
Control5=IDC_CONTRAST_SB,scrollbar,1342242816
Control6=IDC_ConNum,static,1342312961
Control7=IDC_Hue,static,1342177280
Control8=IDC_HUE_SB,scrollbar,1342242816
Control9=IDC_HueNum,static,1342312961
Control10=IDC_Saturation,static,1342177280
Control11=IDC_SATURATION_SB,scrollbar,1342242816
Control12=IDC_SatNum,static,1342312961
Control13=IDC_CLAMPLEVEL,static,1073741824
Control14=IDC_CLAMPLEVEL_SB,scrollbar,1073807360
Control15=IDC_CLAMPLEVELNum,static,1073877505
Control16=IDC_BANDPASS,static,1073741824
Control17=IDC_BANDPASS_SB,scrollbar,1073807360
Control18=IDC_BANDPASSNum,static,1073877505
Control19=IDC_DEFAULT,button,1342242816
Control20=IDC_BUTTON_LIVE,button,1342242816
Control21=IDC_BUTTON_FREEZE,button,1342242816

[DLG:IDD_PROPPAGE2_SOURCE]
Type=1
Class=?
ControlCount=10
Control1=IDC_RADIO_SOURCE1,button,1342308361
Control2=IDC_RADIO_SOURCE2,button,1342177289
Control3=IDC_RADIO_SOURCE3,button,1342177289
Control4=IDC_RADIO_SOURCE4,button,1342177289
Control5=IDC_RADIO_SOURCE5,button,1342177289
Control6=IDC_RADIO_SOURCE6,button,1342177289
Control7=IDC_RADIO_YC1,button,1342177289
Control8=IDC_RADIO_YC2,button,1342177289
Control9=IDC_RADIO_YC3,button,1342177289
Control10=IDC_STATIC,button,1342177287

[DLG:IDD_PROPPAGE3_COLOR]
Type=1
Class=?
ControlCount=7
Control1=IDC_RADIO_YUV422,button,1342312457
Control2=IDC_RADIO_RGB24,button,1342181385
Control3=IDC_RADIO_RGB16,button,1342181385
Control4=IDC_RADIO_RGB15,button,1342181385
Control5=IDC_RADIO_RGB32,button,1342181385
Control6=IDC_RADIO_RGB8,button,1342181385
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_PROPPAGE4_FIELD]
Type=1
Class=?
ControlCount=9
Control1=IDC_RADIO_FRAME,button,1342308361
Control2=IDC_RADIO_FIELD,button,1342177289
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_DISPLAY_CLIP,button,1342308361
Control6=IDC_DISPLAY_SCALE,button,1342177289
Control7=IDC_STATIC,button,1342177287
Control8=IDC_MODE_PAL,button,1342308361
Control9=IDC_MODE_NTSC,button,1342177289

[DLG:IDD_PROPPAGE5_WINDOWS]
Type=1
Class=?
ControlCount=14
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STARTX,edit,1350631552
Control5=IDC_SPIN_STARTX,msctls_updown32,1342177334
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STARTY,edit,1350631552
Control8=IDC_SPIN_STARTY,msctls_updown32,1342177334
Control9=IDC_STATIC,static,1342308352
Control10=IDC_IMAGE_WIDTH,edit,1350631552
Control11=IDC_SPIN_WIDTH,msctls_updown32,1342177334
Control12=IDC_STATIC,static,1342308352
Control13=IDC_IMAGE_HEIGHT,edit,1350631552
Control14=IDC_SPIN_HEIGHT,msctls_updown32,1342177334

[CLS:CdlgMask]
Type=0
HeaderFile=dlgMask.h
ImplementationFile=dlgMask.cpp
BaseClass=CDialog
Filter=D
LastObject=CdlgMask
VirtualFilter=dWC

