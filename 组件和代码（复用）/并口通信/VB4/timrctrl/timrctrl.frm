VERSION 4.00
Begin VB.Form frmMain 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   2820
   ClientLeft      =   4572
   ClientTop       =   1992
   ClientWidth     =   3132
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
   Height          =   3480
   Left            =   4524
   LinkTopic       =   "Form1"
   ScaleHeight     =   2820
   ScaleWidth      =   3132
   Top             =   1380
   Width           =   3228
   Begin VB.Frame fraTimeOfLastAlarm 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Time of Last Alarm"
      ForeColor       =   &H80000008&
      Height          =   612
      Left            =   120
      TabIndex        =   10
      Top             =   1440
      Width           =   2892
      Begin VB.Label lblTimeOfLastAlarm 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   240
         TabIndex        =   9
         Top             =   240
         Width           =   2532
      End
   End
   Begin VB.CommandButton cmdStop 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Stop"
      Height          =   492
      Left            =   1800
      TabIndex        =   8
      Top             =   2160
      Width           =   1212
   End
   Begin VB.CommandButton cmdStart 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Start"
      Height          =   492
      Left            =   120
      TabIndex        =   7
      Top             =   2160
      Width           =   1212
   End
   Begin VB.Frame fraAlarmFrequency 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Alarm Frequency"
      ForeColor       =   &H80000008&
      Height          =   1212
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2892
      Begin VB.TextBox txtSeconds 
         Appearance      =   0  'Flat
         Height          =   372
         Left            =   1920
         TabIndex        =   3
         Text            =   "0"
         Top             =   600
         Width           =   612
      End
      Begin VB.TextBox txtMinutes 
         Appearance      =   0  'Flat
         Height          =   372
         Left            =   1080
         TabIndex        =   2
         Text            =   "0"
         Top             =   600
         Width           =   612
      End
      Begin VB.TextBox txtHours 
         Appearance      =   0  'Flat
         Height          =   372
         Left            =   240
         TabIndex        =   1
         Text            =   "0"
         Top             =   600
         Width           =   612
      End
      Begin VB.Label lblSeconds 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Seconds"
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   1920
         TabIndex        =   6
         Top             =   360
         Width           =   852
      End
      Begin VB.Label lblMinutes 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Minutes"
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   1080
         TabIndex        =   5
         Top             =   360
         Width           =   852
      End
      Begin VB.Label lblHours 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Hours"
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   240
         TabIndex        =   4
         Top             =   360
         Width           =   732
      End
   End
   Begin VB.Timer tmrAlarm 
      Enabled         =   0   'False
      Left            =   1440
      Top             =   2160
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
Dim IntervalSeconds&
Dim IntervalMinutes%
Dim IntervalHours%
Dim LongDelay%
Dim Alarm%
Dim SecondsCounter%
Dim MinutesCounter%

Private Sub AlarmEvents()
Beep
'Place code to execute periodically here.
End Sub

Private Sub cmdStart_Click()
SetTimerInterval
tmrAlarm.Enabled = True
End Sub

Private Sub cmdStop_Click()
tmrAlarm.Enabled = False
End Sub

Private Sub Form_Load()
StartUp
End Sub

Private Sub Form_Unload(Cancel%)
ShutDown
End
End Sub

Private Sub mnuPort_Click(Index%)
frmSelectPort.Show
End Sub

Private Sub SetTimerInterval()
Dim Hours$
Dim Minutes$
Dim Seconds$
LongDelay = False
Alarm = False
Hours = txtHours.Text
Minutes = txtMinutes.Text
Seconds = txtSeconds.Text
If Hours = "" Then Hours = "0"
If Minutes = "" Then Minutes = "0"
If Seconds = "" Then Seconds = "0"
IntervalSeconds = Val(Hours) * 3600 + Val(Minutes) * 60 + Val(Seconds)
If IntervalSeconds < 60 Then
    tmrAlarm.Interval = IntervalSeconds * 1000
Else
    'For long delay, check the time once/minute
    tmrAlarm.Interval = 60000
    LongDelay = True
    'Get the number of minutes.
    IntervalMinutes = IntervalSeconds \ 60
End If
End Sub

Private Sub tmrAlarm_Timer()
If LongDelay Then
    'Decrement the minutes remaining; see if count is finished.
    IntervalMinutes = IntervalMinutes - 1
    If IntervalMinutes <= 0 Then
        Alarm = True
    End If
Else
    Alarm = True
End If
If Alarm = True Then
    'Reset time variables
    SetTimerInterval
    lblTimeOfLastAlarm.Caption = Time$
    AlarmEvents
End If
End Sub

Private Sub txtHours_Change()
If txtHours.Text <> "" Then
    txtSeconds.Text = ""
    txtSeconds.Enabled = False
    lblSeconds.Enabled = False
    End If
End Sub

Private Sub txtMinutes_Change()
If txtMinutes.Text <> "" Then
    txtSeconds.Text = ""
    txtSeconds.Enabled = False
    lblSeconds.Enabled = False
End If
End Sub

