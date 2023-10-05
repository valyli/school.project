; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUsingDBView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "UsingDB.h"
LastPage=0

ClassCount=6
Class1=CUsingDBApp
Class2=CUsingDBDoc
Class3=CUsingDBView
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource7=IDD_USINGDB_FORM
Resource8=IDD_ABOUTBOX (English (U.S.))
Resource9=IDR_MAINFRAME (English (U.S.))
Class5=CUsingDBSet
Resource10=IDD_USINGDB_FORM (English (U.S.))

[CLS:CUsingDBApp]
Type=0
HeaderFile=UsingDB.h
ImplementationFile=UsingDB.cpp
Filter=N

[CLS:CUsingDBDoc]
Type=0
HeaderFile=UsingDBDoc.h
ImplementationFile=UsingDBDoc.cpp
Filter=N

[CLS:CUsingDBView]
Type=0
HeaderFile=UsingDBView.h
ImplementationFile=UsingDBView.cpp
Filter=D
LastObject=IDC_EDIT2

[CLS:CUsingDBSet]
Type=0
HeaderFile=UsingDBSet.h
ImplementationFile=UsingDBSet.cpp
Filter=N

[DB:CUsingDBSet]
DB=1
DBType=ODBC
ColumnCount=15
Column1=[Remote_Host], 12, 50
Column2=[Path_Info], 12, 50
Column3=[HTTP_User_Agent], 12, 75
Column4=[ID], 4, 4
Column5=[CustomerID], 12, 5
Column6=[CompanyName], 12, 40
Column7=[ContactName], 12, 30
Column8=[ContactTitle], 12, 30
Column9=[Address], 12, 60
Column10=[City], 12, 15
Column11=[Region], 12, 15
Column12=[PostalCode], 12, 10
Column13=[Country], 12, 15
Column14=[Phone], 12, 24
Column15=[Fax], 12, 24


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=UsingDB.cpp
ImplementationFile=UsingDB.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_RECORD_FIRST
Command11=ID_RECORD_PREV
Command12=ID_RECORD_NEXT
Command13=ID_RECORD_LAST
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_EDIT_UNDO
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
CommandCount=11
Command1=ID_FILE_PRINT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT

[DLG:IDD_USINGDB_FORM]
Type=1
Class=CUsingDBView

[DLG:IDD_USINGDB_FORM (English (U.S.))]
Type=1
Class=CUsingDBView
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_RECORD_FIRST
Command6=ID_RECORD_PREV
Command7=ID_RECORD_NEXT
Command8=ID_RECORD_LAST
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_PRINT
Command2=ID_FILE_PRINT_PREVIEW
Command3=ID_FILE_PRINT_SETUP
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_RECORD_FIRST
Command10=ID_RECORD_PREV
Command11=ID_RECORD_NEXT
Command12=ID_RECORD_LAST
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_PRINT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
CommandCount=11

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

