VERSION 4.00
Begin VB.Form frmMain 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   1452
   ClientLeft      =   8700
   ClientTop       =   6816
   ClientWidth     =   3432
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
   Height          =   2112
   Left            =   8652
   LinkTopic       =   "Form1"
   ScaleHeight     =   1452
   ScaleWidth      =   3432
   Top             =   6204
   Width           =   3528
   Begin VB.Timer tmrPoll 
      Enabled         =   0   'False
      Left            =   240
      Top             =   120
   End
   Begin VB.Label lblAlarm 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   372
      Left            =   600
      TabIndex        =   0
      Top             =   360
      Width           =   2292
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
Dim PollBit%
Dim FlipFlopClearBit%
Dim ControlPortData%

Private Sub Alarm()
lblAlarm.Caption = "Switch pressed at " + Time$
End Sub

Private Sub ClearFlipFlop()
'Pulse the Clear input of the flip-flop
'so new switch presses can be detected.
ControlPortData = ControlPortRead(BaseAddress)
BitReset ControlPortData, FlipFlopClearBit
ControlPortWrite BaseAddress, ControlPortData
BitSet ControlPortData, FlipFlopClearBit
ControlPortWrite BaseAddress, ControlPortData
End Sub

Private Sub Form_Load()
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

Private Sub Form_Unload(Cancel%)
ShutDown
End
End Sub

Private Sub mnuPort_Click(Index%)
frmSelectPort.Show
End Sub

Private Sub tmrPoll_Timer()
Dim SwitchPress%
'Read the bit being polled.
'If the bit = 1, call the Alarm subroutine.
SwitchPress = BitRead(StatusPortRead(BaseAddress), PollBit)
If SwitchPress = 1 Then
    ClearFlipFlop
    Alarm
End If
End Sub

