VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Complete"
   ClientHeight    =   2580
   ClientLeft      =   864
   ClientTop       =   1692
   ClientWidth     =   3072
   ForeColor       =   &H00C0C0C0&
   Height          =   3240
   Left            =   816
   LinkTopic       =   "Form1"
   ScaleHeight     =   2580
   ScaleWidth      =   3072
   Top             =   1080
   Width           =   3168
   Begin CommandButton cmdReadPorts 
      Caption         =   "Read Ports"
      Height          =   492
      Left            =   1680
      TabIndex        =   17
      Top             =   240
      Width           =   1212
   End
   Begin Frame fraADC 
      Caption         =   "Analog Inputs"
      Height          =   2292
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1452
      Begin Label lblChannelNumber 
         Caption         =   "7"
         Height          =   252
         Index           =   7
         Left            =   120
         TabIndex        =   16
         Top             =   1920
         Width           =   252
      End
      Begin Label lblChannelNumber 
         Caption         =   "6"
         Height          =   252
         Index           =   6
         Left            =   120
         TabIndex        =   15
         Top             =   1680
         Width           =   252
      End
      Begin Label lblChannelNumber 
         Caption         =   "5"
         Height          =   252
         Index           =   5
         Left            =   120
         TabIndex        =   14
         Top             =   1440
         Width           =   252
      End
      Begin Label lblChannelNumber 
         Caption         =   "4"
         Height          =   252
         Index           =   4
         Left            =   120
         TabIndex        =   13
         Top             =   1200
         Width           =   252
      End
      Begin Label lblChannelNumber 
         Caption         =   "3"
         Height          =   252
         Index           =   3
         Left            =   120
         TabIndex        =   12
         Top             =   960
         Width           =   252
      End
      Begin Label lblChannelNumber 
         Caption         =   "2"
         Height          =   252
         Index           =   2
         Left            =   120
         TabIndex        =   11
         Top             =   720
         Width           =   252
      End
      Begin Label lblChannelNumber 
         Caption         =   "1"
         Height          =   252
         Index           =   1
         Left            =   120
         TabIndex        =   10
         Top             =   480
         Width           =   252
      End
      Begin Label lblChannelNumber 
         Caption         =   "0"
         Height          =   252
         Index           =   0
         Left            =   120
         TabIndex        =   9
         Top             =   240
         Width           =   252
      End
      Begin Label lblADC 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   7
         Left            =   480
         TabIndex        =   8
         Top             =   1920
         Width           =   420
      End
      Begin Label lblADC 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   6
         Left            =   480
         TabIndex        =   7
         Top             =   1680
         Width           =   420
      End
      Begin Label lblADC 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   5
         Left            =   480
         TabIndex        =   6
         Top             =   1440
         Width           =   420
      End
      Begin Label lblADC 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   4
         Left            =   480
         TabIndex        =   5
         Top             =   1200
         Width           =   420
      End
      Begin Label lblADC 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   3
         Left            =   480
         TabIndex        =   4
         Top             =   960
         Width           =   420
      End
      Begin Label lblADC 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   2
         Left            =   480
         TabIndex        =   3
         Top             =   720
         Width           =   420
      End
      Begin Label lblADC 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   1
         Left            =   480
         TabIndex        =   2
         Top             =   480
         Width           =   420
      End
      Begin Label lblADC 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   0
         Left            =   480
         TabIndex        =   1
         Top             =   240
         Width           =   420
      End
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
Const Start% = 8
Const HighNibbleSelect% = &H10
Dim DataIn%(0 To 7)
Dim ChannelNumber%
Dim LowNibble%
Dim HighNibble%


Sub cmdReadPorts_Click ()
Dim EOC%
For ChannelNumber = 0 To 7
    'Select the channel.
    DataPortWrite BaseAddress, ChannelNumber
    'Pulse Start to begin a conversion.
    DataPortWrite BaseAddress, ChannelNumber + Start
    DataPortWrite BaseAddress, ChannelNumber
    'Wait for EOC
    Do
        DoEvents
        LowNibble = StatusPortRead(BaseAddress)
        EOC = BitRead(LowNibble, 6)
    Loop Until EOC = 1
    'Read the byte in 2 nibbles.
    DataPortWrite BaseAddress, ChannelNumber + HighNibbleSelect
    HighNibble = StatusPortRead(BaseAddress)
    DataIn(ChannelNumber) = MakeByteFromNibbles()
Next ChannelNumber
DisplayResult
End Sub

Sub DisplayResult ()
For ChannelNumber = 0 To 7
    lblADC(ChannelNumber).Caption = Hex$(DataIn(ChannelNumber)) & "h"
Next ChannelNumber
End Sub

Sub Form_Load ()
StartUp
End Sub

Sub Form_Unload (Cancel%)
ShutDown
End Sub

Function MakeByteFromNibbles% ()
Dim S0%, S1%, S2%, S3%, S4%, S5%, S6%, S7%
S0 = (LowNibble And 8) \ 8
S1 = (LowNibble And &H10) \ 8
S2 = (LowNibble And &H20) \ 8
S3 = (LowNibble And &H80) \ &H10
S4 = (HighNibble And 8) * 2
S5 = (HighNibble And &H10) * 2
S6 = (HighNibble And &H20) * 2
S7 = HighNibble And &H80
MakeByteFromNibbles = S0 + S1 + S2 + S3 + S4 + S5 + S6 + S7
End Function

Sub mnuPort_Click (Index%)
frmSelectPort.Show
End Sub

