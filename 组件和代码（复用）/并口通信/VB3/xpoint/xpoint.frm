VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   2676
   ClientLeft      =   2724
   ClientTop       =   4212
   ClientWidth     =   5208
   ForeColor       =   &H00C0C0C0&
   Height          =   3336
   Left            =   2676
   LinkTopic       =   "Form1"
   ScaleHeight     =   2676
   ScaleWidth      =   5208
   Top             =   3600
   Width           =   5304
   Begin Grid grdXY 
      BackColor       =   &H00FFFFFF&
      Cols            =   9
      Height          =   2052
      HighLight       =   0   'False
      Left            =   120
      Rows            =   9
      ScrollBars      =   0  'None
      TabIndex        =   0
      Top             =   480
      Width           =   4932
   End
   Begin Label lblXY 
      Alignment       =   2  'Center
      Height          =   252
      Left            =   720
      TabIndex        =   1
      Top             =   120
      Width           =   3612
   End
   Begin Menu mnuSetup 
      Caption         =   "&Setup"
      Index           =   0
      Begin Menu mnuPort 
         Caption         =   "&Port..."
         Index           =   0
      End
   End
End
Option Explicit
Dim SwitchState$
Const OPENSWITCH% = 0
Const CLOSESWITCH% = 1

Sub ActivateSwitch (OpenOrClose%)
Dim Strobe%
Dim XY%
'Data port bit 7 = OpenOrClose (0=open, 1=close)
OpenOrClose = OpenOrClose * &H80
'Data port bit 6 = Strobe.
Strobe = &H40
'Data port bits 0-2 hold the X value, bits 3-5 hold the Y value.
XY = grdXY.Col - 1 + (grdXY.Row - 1) * 8
'Write the address, select open or close, Strobe = 1
DataPortWrite BaseAddress, XY + Strobe + OpenOrClose
'Pulse the Strobe input.
DataPortWrite BaseAddress, XY + OpenOrClose
DataPortWrite BaseAddress, XY + Strobe + OpenOrClose
End Sub

Sub DisplayResults ()
Select Case SwitchState
    Case "Closed"
        grdXY.Text = "X"
    Case "Open"
        grdXY.Text = ""
End Select
End Sub

Sub Form_Load ()
StartUp
LabelTheGrid
End Sub

Sub Form_Unload (Cancel As Integer)
End
End Sub

Sub grdXY_Click ()
Select Case grdXY.Text
    Case "X"
        ActivateSwitch OPENSWITCH
        SwitchState = "Open"
        DisplayResults
    Case Else
        ActivateSwitch CLOSESWITCH
        SwitchState = "Closed"
        DisplayResults
End Select
End Sub

Sub LabelTheGrid ()
Dim Row%
Dim Column%
grdXY.Col = 0
For Row = 1 To 8
    grdXY.Row = Row
    grdXY.Text = "Y" & Row - 1
Next Row
grdXY.Row = 0
For Column = 1 To 8
    grdXY.Col = Column
    grdXY.Text = "X" & Column - 1
Next Column
lblXY.Caption = "8 x 8 Crosspoint Switch"
End Sub

Sub mnuPort_Click (Index%)
frmSelectPort.Show

End Sub

