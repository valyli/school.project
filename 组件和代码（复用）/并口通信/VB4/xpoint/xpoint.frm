VERSION 4.00
Begin VB.Form frmMain 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   2676
   ClientLeft      =   2724
   ClientTop       =   4212
   ClientWidth     =   5208
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   0
      weight          =   700
      size            =   7.8
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H00C0C0C0&
   Height          =   3336
   Left            =   2676
   LinkTopic       =   "Form1"
   ScaleHeight     =   2676
   ScaleWidth      =   5208
   Top             =   3600
   Width           =   5304
   Begin MSGrid.Grid grdXY 
      Height          =   2052
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   4932
      _Version        =   65536
      _ExtentX        =   8700
      _ExtentY        =   3620
      _StockProps     =   77
      ForeColor       =   -2147483640
      BackColor       =   16777215
      Rows            =   9
      Cols            =   9
      ScrollBars      =   0
      HighLight       =   0   'False
   End
   Begin VB.Label lblXY 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   252
      Left            =   720
      TabIndex        =   1
      Top             =   120
      Width           =   3612
   End
   Begin VB.Menu mnuSetup 
      Caption         =   "&Setup"
      Index           =   0
      Begin VB.Menu mnuPort 
         Caption         =   "&Port..."
         Index           =   0
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit
Dim SwitchState$
Const OPENSWITCH% = 0
Const CLOSESWITCH% = 1

Private Sub ActivateSwitch(OpenOrClose%)
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

Private Sub DisplayResults()
Select Case SwitchState
    Case "Closed"
        grdXY.Text = "X"
    Case "Open"
        grdXY.Text = ""
End Select
End Sub

Private Sub Form_Load()
StartUp
LabelTheGrid
End Sub

Private Sub Form_Unload(Cancel As Integer)
End
End Sub

Private Sub grdXY_Click()
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

Private Sub LabelTheGrid()
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

Private Sub mnuPort_Click(Index%)
frmSelectPort.Show

End Sub

