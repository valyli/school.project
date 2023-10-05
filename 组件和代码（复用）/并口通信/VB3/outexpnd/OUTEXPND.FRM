VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   3060
   ClientLeft      =   3648
   ClientTop       =   2208
   ClientWidth     =   3852
   ForeColor       =   &H00C0C0C0&
   Height          =   3720
   Left            =   3600
   LinkTopic       =   "Form1"
   ScaleHeight     =   3060
   ScaleWidth      =   3852
   Top             =   1596
   Width           =   3948
   Begin TextBox txtByteToWrite 
      Height          =   372
      Left            =   2760
      TabIndex        =   13
      Text            =   "00"
      Top             =   2040
      Width           =   492
   End
   Begin CommandButton cmdWriteByte 
      Caption         =   "Write Byte"
      Height          =   492
      Left            =   2400
      TabIndex        =   11
      Top             =   600
      Width           =   1212
   End
   Begin Frame fraDisplayBytes 
      Height          =   2772
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2172
      Begin OptionButton optByte 
         Caption         =   "0"
         Height          =   252
         Index           =   0
         Left            =   240
         TabIndex        =   8
         Top             =   600
         Value           =   -1  'True
         Width           =   492
      End
      Begin OptionButton optByte 
         Caption         =   "1"
         Height          =   252
         Index           =   1
         Left            =   240
         TabIndex        =   7
         Top             =   840
         Width           =   492
      End
      Begin OptionButton optByte 
         Caption         =   "2"
         Height          =   252
         Index           =   2
         Left            =   240
         TabIndex        =   6
         Top             =   1080
         Width           =   492
      End
      Begin OptionButton optByte 
         Caption         =   "3"
         Height          =   252
         Index           =   3
         Left            =   240
         TabIndex        =   5
         Top             =   1320
         Width           =   492
      End
      Begin OptionButton optByte 
         Caption         =   "4"
         Height          =   252
         Index           =   4
         Left            =   240
         TabIndex        =   4
         Top             =   1560
         Width           =   492
      End
      Begin OptionButton optByte 
         Caption         =   "5"
         Height          =   252
         Index           =   5
         Left            =   240
         TabIndex        =   3
         Top             =   1800
         Width           =   492
      End
      Begin OptionButton optByte 
         Caption         =   "6"
         Height          =   252
         Index           =   6
         Left            =   240
         TabIndex        =   2
         Top             =   2040
         Width           =   492
      End
      Begin OptionButton optByte 
         Caption         =   "7"
         Height          =   252
         Index           =   7
         Left            =   240
         TabIndex        =   1
         Top             =   2280
         Width           =   492
      End
      Begin Label lblByte 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   7
         Left            =   1080
         TabIndex        =   14
         Top             =   2280
         Width           =   732
      End
      Begin Label lblByte 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   6
         Left            =   1080
         TabIndex        =   15
         Top             =   2040
         Width           =   732
      End
      Begin Label lblByte 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   5
         Left            =   1080
         TabIndex        =   16
         Top             =   1800
         Width           =   732
      End
      Begin Label lblByte 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   4
         Left            =   1080
         TabIndex        =   21
         Top             =   1560
         Width           =   732
      End
      Begin Label lblByte 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   3
         Left            =   1080
         TabIndex        =   20
         Top             =   1320
         Width           =   732
      End
      Begin Label lblByte 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   2
         Left            =   1080
         TabIndex        =   19
         Top             =   1080
         Width           =   732
      End
      Begin Label lblByte 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   1
         Left            =   1080
         TabIndex        =   18
         Top             =   840
         Width           =   732
      End
      Begin Label lblByte 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   0
         Left            =   1080
         TabIndex        =   17
         Top             =   600
         Width           =   732
      End
      Begin Label lblByteWritten 
         AutoSize        =   -1  'True
         Caption         =   "Byte Written"
         Height          =   192
         Left            =   960
         TabIndex        =   10
         Top             =   360
         Width           =   1008
      End
      Begin Label lblByteNumber 
         AutoSize        =   -1  'True
         Caption         =   "Byte #"
         Height          =   192
         Left            =   240
         TabIndex        =   9
         Top             =   360
         Width           =   540
      End
   End
   Begin Label lblByteToWrite 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      Caption         =   "Byte to Write (0-FF)"
      Height          =   432
      Left            =   2400
      TabIndex        =   12
      Top             =   1560
      Width           =   1248
      WordWrap        =   -1  'True
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
Dim ByteNumber%
Dim ControlPortData%

Sub cmdWriteByte_Click ()
'Write the value in the "Byte to Write" text box to the selected output (1-8).
DataPortWrite BaseAddress, CInt("&h" & txtByteToWrite.Text)
'Select an output by writing its number to Control Port, bits 0-2, with bit 3 = 1.
'This brings the output's CLK input low.
'Then set Control bit 3 = 0 to bring all CLK inputs high.
'This latches the value at the data port to the selected output.
ControlPortWrite BaseAddress, ByteNumber + 8
ControlPortWrite BaseAddress, 0
'Display the result.
lblByte(ByteNumber).Caption = ""
lblByte(ByteNumber).Caption = txtByteToWrite.Text & "h"
End Sub

Sub Form_Load ()
StartUp
'This program enables you to control as many as 64 output bits (8 bytes).
'The user selects an output byte from a group of option buttons
'and enters a value in a text box.
'Clicking on the Write control button writes the value to the selected output.

'Bring all CLK inputs high by bringing Control Port bit 3 low.
ControlPortData = ControlPortRead(BaseAddress)
BitReset ControlPortData, 3
ControlPortWrite BaseAddress, ControlPortData
End Sub

Sub Form_Unload (Cancel%)
'Save the BaseAddress and PortType in the ini file.
WriteIniData
End
End Sub

Sub mnuPort_Click (Index%)
frmSelectPort.Show
End Sub

Sub optByte_Click (Index As Integer)
ByteNumber = Index
End Sub

