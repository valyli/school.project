VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   1452
   ClientLeft      =   8700
   ClientTop       =   6816
   ClientWidth     =   3432
   ForeColor       =   &H00C0C0C0&
   Height          =   2112
   Left            =   8652
   LinkTopic       =   "Form1"
   ScaleHeight     =   1452
   ScaleWidth      =   3432
   Top             =   6204
   Width           =   3528
   Begin Timer tmrPoll 
      Enabled         =   0   'False
      Left            =   240
      Top             =   120
   End
   Begin Label lblAlarm 
      Height          =   372
      Left            =   600
      TabIndex        =   0
      Top             =   360
      Width           =   2292
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
Dim PollBit%
Dim FlipFlopClearBit%
Dim ControlPortData%

Sub Alarm ()
lblAlarm.Caption = "Switch pressed at " + Time$
End Sub

Sub ClearFlipFlop ()
'Pulse the Clear input of the flip-flop
'so new switch presses can be detected.
ControlPortData = ControlPortRead(BaseAddress)
BitReset ControlPortData, FlipFlopClearBit
ControlPortWrite BaseAddress, ControlPortData
BitSet ControlPortData, FlipFlopClearBit
ControlPortWrite BaseAddress, ControlPortData
End Sub

Sub Form_Load ()
StartUp
'The Status-port bit that the program polls:
PollBit = 3
'The Control-port bit that clears the flip-flop:
FlipFlopClearBit = 0
ClearFlipFlop
tmrPoll.Interval = 1000
tmrPoll.Enabled = True
lblAlarm.Caption = "Waiting for alarms..."
End Sub

Sub Form_Unload (Cancel%)
ShutDown
End
End Sub

Sub mnuPort_Click (Index%)
frmSelectPort.Show
End Sub

Sub tmrPoll_Timer ()
Dim SwitchPress%
'Read the bit being polled.
'If the bit = 1, call the Alarm subroutine.
SwitchPress = BitRead(StatusPortRead(BaseAddress), PollBit)
If SwitchPress = 1 Then
    ClearFlipFlop
    Alarm
End If
End Sub

