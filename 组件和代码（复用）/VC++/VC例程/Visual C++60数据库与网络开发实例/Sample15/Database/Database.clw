; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDialogData1
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Database.h"
LastPage=0

ClassCount=9
Class1=CDatabaseApp
Class2=CDatabaseDoc
Class3=CDatabaseView
Class4=CMainFrame

ResourceCount=9
Resource1=IDD_DATABASE_FORM
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_DIALOG_DATA
Class6=CDialogData
Class7=CDaoRecordsetEmployees
Resource4=IDD_ABOUTBOX
Class8=CRecordsetEmployees
Resource5=IDD_DATABASE_FORM (English (U.S.))
Resource6=IDD_DIALOG_DATA (English (U.S.))
Resource7=IDD_DIALOG1
Resource8=IDD_ABOUTBOX (English (U.S.))
Class9=CDialogData1
Resource9=IDR_MAINFRAME (English (U.S.))

[CLS:CDatabaseApp]
Type=0
HeaderFile=Database.h
ImplementationFile=Database.cpp
Filter=N
LastObject=CDatabaseApp

[CLS:CDatabaseDoc]
Type=0
HeaderFile=DatabaseDoc.h
ImplementationFile=DatabaseDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CDatabaseDoc

[CLS:CDatabaseView]
Type=0
HeaderFile=DatabaseView.h
ImplementationFile=DatabaseView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=CDatabaseView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=Database.cpp
ImplementationFile=Database.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308353

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_VIEW_TOOLBAR
Command10=ID_VIEW_STATUS_BAR
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_CUT
Command12=ID_EDIT_UNDO
CommandCount=12

[DLG:IDD_DATABASE_FORM]
Type=1
Class=CDatabaseView
ControlCount=4
Control1=IDC_STATIC,static,1342308353
Control2=IDC_EDIT_SSN,edit,1350631552
Control3=IDC_BUTTON_FIND,button,1342242816
Control4=IDC_STATIC,static,1342308353

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_APP_ABOUT
CommandCount=6

[DLG:IDD_DIALOG_DATA]
Type=1
Class=CDialogData
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_NAME,edit,1350631552
Control4=IDC_EDIT_ADDRESS,edit,1352732676
Control5=IDC_EDIT_TITLE,edit,1350631552
Control6=IDC_EDIT_HIRED,edit,1350631552
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_EDIT_SSN,edit,1350567941
Control12=IDC_STATIC,static,1342308352

[CLS:CDialogData]
Type=0
HeaderFile=DialogData.h
ImplementationFile=DialogData.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_ADDRESS
VirtualFilter=dWC

[DB:CDaoRecordsetEmployees]
DB=1
DBType=DAO
ColumnCount=5
Column1=[SSN], 8, 8
Column2=[NAME], 12, 50
Column3=[ADDRESS], -1, 0
Column4=[TITLE], 12, 50
Column5=[HIRE DATE], 11, 8

[CLS:CDaoRecordsetEmployees]
Type=0
HeaderFile=DaoRecordsetEmployees.h
ImplementationFile=DaoRecordsetEmployees.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[CLS:CRecordsetEmployees]
Type=0
HeaderFile=RecordsetEmployees.h
ImplementationFile=RecordsetEmployees.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CRecordsetEmployees]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[SSN], 8, 8
Column2=[NAME], 12, 50
Column3=[ADDRESS], -1, 1073741824
Column4=[TITLE], 12, 50
Column5=[HIRE DATE], 11, 16

[DLG:IDD_DIALOG_DATA (English (U.S.))]
Type=1
Class=CDialogData
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_NAME,edit,1350631552
Control4=IDC_EDIT_ADDRESS,edit,1352732676
Control5=IDC_EDIT_TITLE,edit,1350631552
Control6=IDC_EDIT_HIRED,edit,1350631552
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_EDIT_SSN,edit,1350567941
Control12=IDC_STATIC,static,1342308352

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_APP_ABOUT
CommandCount=6

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_VIEW_TOOLBAR
Command10=ID_VIEW_STATUS_BAR
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_EDIT_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_CUT
Command12=ID_EDIT_UNDO
CommandCount=12

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308353

[DLG:IDD_DATABASE_FORM (English (U.S.))]
Type=1
Class=CDatabaseView
ControlCount=4
Control1=IDC_STATIC,static,1342308353
Control2=IDC_EDIT_SSN,edit,1350631552
Control3=IDC_BUTTON_FIND,button,1342242816
Control4=IDC_STATIC,static,1342308353

[DLG:IDD_DIALOG1]
Type=1
Class=CDialogData1
ControlCount=12
Control1=IDOK2,button,1342242817
Control2=IDCANCEL2,button,1342242816
Control3=IDC_EDIT_NAME,edit,1350631552
Control4=IDC_EDIT_ADDRESS,edit,1352732676
Control5=IDC_EDIT_TITLE,edit,1350631552
Control6=IDC_EDIT_HIRED,edit,1350631552
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_EDIT_SSN,edit,1350567941
Control12=IDC_STATIC,static,1342308352

[CLS:CDialogData1]
Type=0
HeaderFile=DialogData1.h
ImplementationFile=DialogData1.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

