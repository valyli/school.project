VERSION 4.00
Begin VB.Form frmSelectPort 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   2748
   ClientLeft      =   2976
   ClientTop       =   5544
   ClientWidth     =   6264
   BeginProperty Font 
      name            =   "MS Sans Serif"
      charset         =   0
      weight          =   700
      size            =   7.8
      underline       =   0   'False
      italic          =   0   'False
      strikethrough   =   0   'False
   EndProperty
   ForeColor       =   &H80000008&
   Height          =   3132
   Left            =   2928
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2748
   ScaleWidth      =   6264
   Top             =   5208
   Width           =   6360
   Begin VB.ComboBox cboEcpMode 
      Appearance      =   0  'Flat
      Height          =   288
      Index           =   0
      Left            =   4440
      Style           =   2  'Dropdown List
      TabIndex        =   9
      Top             =   720
      Width           =   1572
   End
   Begin VB.CommandButton cmdAddPort 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Add a Port"
      Height          =   492
      Left            =   120
      TabIndex        =   0
      Top             =   1680
      Width           =   1452
   End
   Begin VB.Frame fraPort 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Ports"
      ForeColor       =   &H80000008&
      Height          =   1932
      Left            =   1800
      TabIndex        =   7
      Top             =   120
      Width           =   4332
      Begin VB.ComboBox cboEcpMode 
         Appearance      =   0  'Flat
         Height          =   288
         Index           =   3
         Left            =   2640
         Style           =   2  'Dropdown List
         TabIndex        =   24
         Top             =   1320
         Visible         =   0   'False
         Width           =   1572
      End
      Begin VB.ComboBox cboEcpMode 
         Appearance      =   0  'Flat
         Height          =   288
         Index           =   2
         Left            =   2640
         Style           =   2  'Dropdown List
         TabIndex        =   23
         Top             =   1080
         Visible         =   0   'False
         Width           =   1572
      End
      Begin VB.ComboBox cboEcpMode 
         Appearance      =   0  'Flat
         Height          =   288
         Index           =   1
         Left            =   2640
         Style           =   2  'Dropdown List
         TabIndex        =   22
         Top             =   840
         Visible         =   0   'False
         Width           =   1572
      End
      Begin VB.OptionButton optPortName 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "User"
         Enabled         =   0   'False
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   3
         Left            =   120
         TabIndex        =   3
         Top             =   1320
         Width           =   852
      End
      Begin VB.OptionButton optPortName 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "LPT3"
         Enabled         =   0   'False
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   2
         Left            =   120
         TabIndex        =   4
         Top             =   1080
         Width           =   852
      End
      Begin VB.OptionButton optPortName 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "LPT2"
         Enabled         =   0   'False
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   1
         Left            =   120
         TabIndex        =   5
         Top             =   840
         Width           =   852
      End
      Begin VB.OptionButton optPortName 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "LPT1"
         Enabled         =   0   'False
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   0
         Left            =   120
         TabIndex        =   8
         Top             =   600
         Width           =   852
      End
      Begin VB.Label lblType 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   3
         Left            =   1800
         TabIndex        =   21
         Top             =   1320
         Visible         =   0   'False
         Width           =   852
      End
      Begin VB.Label lblType 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   2
         Left            =   1800
         TabIndex        =   20
         Top             =   1080
         Visible         =   0   'False
         Width           =   852
      End
      Begin VB.Label lblType 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   1
         Left            =   1800
         TabIndex        =   19
         Top             =   840
         Visible         =   0   'False
         Width           =   852
      End
      Begin VB.Label lblAddress 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   3
         Left            =   960
         TabIndex        =   18
         Top             =   1320
         Width           =   852
      End
      Begin VB.Label lblAddress 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   2
         Left            =   960
         TabIndex        =   17
         Top             =   1080
         Width           =   852
      End
      Begin VB.Label lblAddress 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   1
         Left            =   960
         TabIndex        =   16
         Top             =   840
         Width           =   852
      End
      Begin VB.Label lblType 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   0
         Left            =   1800
         TabIndex        =   15
         Top             =   600
         Visible         =   0   'False
         Width           =   852
      End
      Begin VB.Label lblAddress 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   0
         Left            =   960
         TabIndex        =   14
         Top             =   600
         Width           =   852
      End
      Begin VB.Label lblEcpMode 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "ECP Mode"
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   2640
         TabIndex        =   13
         Top             =   360
         Width           =   1212
      End
      Begin VB.Label lblTypeHeading 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Type"
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   1800
         TabIndex        =   12
         Top             =   360
         Width           =   852
      End
      Begin VB.Label lblAddressHeading 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Address"
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   960
         TabIndex        =   11
         Top             =   360
         Width           =   852
      End
      Begin VB.Label lblPort 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Port"
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   120
         TabIndex        =   10
         Top             =   360
         Width           =   852
      End
   End
   Begin VB.CommandButton cmdFindPorts 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Find Ports"
      Height          =   492
      Left            =   120
      TabIndex        =   6
      Top             =   960
      Width           =   1452
   End
   Begin VB.CommandButton cmdOK 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   492
      Left            =   4680
      TabIndex        =   2
      Top             =   2160
      Width           =   1452
   End
   Begin VB.CommandButton cmdTestPort 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Test Port"
      Height          =   492
      Left            =   120
      TabIndex        =   1
      Top             =   240
      Width           =   1452
   End
End
Attribute VB_Name = "frmSelectPort"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Option Explicit

Private Sub cboEcpMode_Click(Index As Integer)
SetEcpMode (cboEcpMode(Index).ListIndex)
End Sub

Private Sub cmdAddPort_Click()
'Display a text box to enable user to add a port
'at a nonstandard address.
frmNewPortAddress.Show
End Sub

Private Sub cmdFindPorts_Click()
'Test the port at each of the standard addresses,
'and at the non-standard address, if the user has entered one.
Dim Index%
Dim PortExists%
Dim Count%
Index = 0
'First, test address 3BCh
Port(Index).Address = &H3BC
PortExists = TestPort(Index)
'If there is a port at 3BCh, increment the index.
If Not (Port(Index).Address) = 0 Then
    Index = Index + 1
End If
'Test address 378h
Port(Index).Address = &H378
PortExists = TestPort(Index)
'If the port exists, increment the index.
If Not (Port(Index).Address) = 0 Then
    Index = Index + 1
End If
'Test address 278h
Port(Index).Address = &H278
PortExists = TestPort(Index)
'Disable option buttons of unused LPT ports
For Count = Index + 1 To 2
    optPortName(Count).Enabled = False
    Port(Count).Enabled = False
Next Count
If Not (Port(3).Address = 0) Then
    PortExists = TestPort(Index)
Else
    optPortName(3).Enabled = False
End If
End Sub

Private Sub cmdOK_Click()
frmSelectPort.Hide
End Sub

Private Sub cmdTestPort_Click()
Dim PortExists%
Dim Index%
'Get the address of the selected port
Index = -1
Do
    Index = Index + 1
Loop Until optPortName(Index).Value = True
PortExists = TestPort(Index)
Select Case PortExists
    Case True
        MsgBox "Passed: Port " + Hex$(BaseAddress) + "h is " + Port(Index).PortType + ".", 0, "Test Result:"
    Case False
        MsgBox "Failed port test. ", 0, "Test Result:"
End Select

End Sub

Private Sub Form_Load()
Dim Index%
Left = (Screen.Width - Width) / 2
Top = (Screen.Height - Height) / 2

'Load the combo boxes with the ECP modes.
For Index = 0 To 3
    cboEcpMode(Index).AddItem "SPP (original)"
Next Index
For Index = 0 To 3
    cboEcpMode(Index).AddItem "bidirectional"
Next Index
For Index = 0 To 3
    cboEcpMode(Index).AddItem "Fast Centronics"
Next Index
For Index = 0 To 3
    cboEcpMode(Index).AddItem "ECP"
Next Index
For Index = 0 To 3
    cboEcpMode(Index).AddItem "EPP"
Next Index
For Index = 0 To 3
    cboEcpMode(Index).AddItem "reserved"
Next Index
For Index = 0 To 3
    cboEcpMode(Index).AddItem "reserved"
Next Index
For Index = 0 To 3
    cboEcpMode(Index).AddItem "test"
Next Index
For Index = 0 To 3
    cboEcpMode(Index).AddItem "configuration"
Next Index

'Enable the option buttons for existing ports.
For Index = 0 To 3
    optPortName(Index).Enabled = Port(Index).Enabled
Next Index
UpdateLabels
End Sub

Private Sub optPortName_Click(Index As Integer)
'Store the address and index of the selected port.
Dim Count%
BaseAddress = Port(Index).Address
IndexOfSelectedPort = Index
EcpDataPortAddress = BaseAddress + &H400
EcrAddress = BaseAddress + &H402
For Count = 0 To 3
    cboEcpMode(Count).Enabled = False
Next Count
cboEcpMode(Index).Enabled = True
End Sub

