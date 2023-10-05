VERSION 4.00
Begin VB.Form frmMain 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   1848
   ClientLeft      =   3648
   ClientTop       =   5088
   ClientWidth     =   3072
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
   Height          =   2508
   Left            =   3600
   LinkTopic       =   "Form1"
   ScaleHeight     =   1848
   ScaleWidth      =   3072
   Top             =   4476
   Width           =   3168
   Begin VB.CommandButton cmdReadByte 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Read Byte"
      Height          =   612
      Left            =   840
      TabIndex        =   0
      Top             =   840
      Width           =   1332
   End
   Begin VB.Label lblByteIn 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   252
      Left            =   1200
      TabIndex        =   1
      Top             =   360
      Width           =   492
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
Const SelectHighNibble% = 1
Const Clock% = 2

Private Sub cmdReadByte_Click()
Dim LowNibble%
Dim HighNibble%
Dim ByteIn%
'Latch the data
ControlPortWrite BaseAddress, Clock
ControlPortWrite BaseAddress, 0
'Read the nibbles at bits 4-7.
LowNibble = StatusPortRead(BaseAddress) \ &H10
ControlPortWrite BaseAddress, SelectHighNibble
HighNibble = StatusPortRead(BaseAddress) And &HF0
ByteIn = LowNibble + HighNibble
lblByteIn.Caption = Hex$(ByteIn) + "h"
End Sub

Private Sub Form_Load()
StartUp
'Initialize the control port.
ControlPortWrite BaseAddress, 0
End Sub

Private Sub Form_Unload(Cancel%)
ShutDown
End
End Sub

Private Sub mnuPort_Click(Index%)
frmSelectPort.Show
End Sub

