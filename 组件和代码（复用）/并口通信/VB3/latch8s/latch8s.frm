VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   1848
   ClientLeft      =   3648
   ClientTop       =   5088
   ClientWidth     =   3072
   ForeColor       =   &H00C0C0C0&
   Height          =   2508
   Left            =   3600
   LinkTopic       =   "Form1"
   ScaleHeight     =   1848
   ScaleWidth      =   3072
   Top             =   4476
   Width           =   3168
   Begin CommandButton cmdReadByte 
      Caption         =   "Read Byte"
      Height          =   612
      Left            =   840
      TabIndex        =   0
      Top             =   840
      Width           =   1332
   End
   Begin Label lblByteIn 
      BorderStyle     =   1  'Fixed Single
      Height          =   252
      Left            =   1200
      TabIndex        =   1
      Top             =   360
      Width           =   492
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
Const SelectHighNibble% = 1
Const Clock% = 2

Sub cmdReadByte_Click ()
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

Sub Form_Load ()
StartUp
'Initialize the control port.
ControlPortWrite BaseAddress, 0
End Sub

Sub Form_Unload (Cancel%)
ShutDown
End
End Sub

Sub mnuPort_Click (Index%)
frmSelectPort.Show
End Sub

