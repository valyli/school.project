VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   1848
   ClientLeft      =   1524
   ClientTop       =   5712
   ClientWidth     =   3072
   ForeColor       =   &H00C0C0C0&
   Height          =   2508
   Left            =   1476
   LinkTopic       =   "Form1"
   ScaleHeight     =   1848
   ScaleWidth      =   3072
   Top             =   5100
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
'Clock is control bit 3.
Const Clock% = 8
'Write 1 to bits C0-C2 to allow their use as inputs.
Const SetControlBitsAsInputs% = 7

Sub cmdReadByte_Click ()
Dim LowBits%
Dim HighBits%
Dim ByteIn%
'Latch the data.
ControlPortWrite BaseAddress, SetControlBitsAsInputs + Clock
ControlPortWrite BaseAddress, SetControlBitsAsInputs
'Read the bits at C0-C2, S3-S7.
LowBits = ControlPortRead(BaseAddress) And 7
HighBits = StatusPortRead(BaseAddress) And &HF8
ByteIn = LowBits + HighBits
lblByteIn.Caption = Hex$(ByteIn) + "h"
End Sub

Sub Form_Load ()
StartUp
'Initialize the control port.
ControlPortWrite BaseAddress, SetControlBitsAsInputs
End Sub

Sub Form_Unload (Cancel%)
ShutDown
End
End Sub

Sub mnuPort_Click (Index%)
frmSelectPort.Show
End Sub

