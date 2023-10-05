VERSION 4.00
Begin VB.Form frmMain 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   2916
   ClientLeft      =   8808
   ClientTop       =   5748
   ClientWidth     =   3240
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
   Height          =   3576
   Left            =   8760
   LinkTopic       =   "Form1"
   ScaleHeight     =   2916
   ScaleWidth      =   3240
   Top             =   5136
   Width           =   3336
   Begin VB.Frame fraCurrentTime 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Current Time"
      ForeColor       =   &H80000008&
      Height          =   612
      Left            =   120
      TabIndex        =   11
      Top             =   1440
      Width           =   2052
      Begin VB.Label lblCurrentTime 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   120
         TabIndex        =   12
         Top             =   240
         Width           =   1332
      End
   End
   Begin VB.Frame fraTimeOfLastAlarm 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Time of Last Alarm"
      ForeColor       =   &H80000008&
      Height          =   612
      Left            =   120
      TabIndex        =   10
      Top             =   2160
      Width           =   2052
      Begin VB.Label lblTimeOfLastAlarm 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   240
         TabIndex        =   9
         Top             =   240
         Width           =   1212
      End
   End
   Begin VB.CommandButton cmdStop 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Stop"
      Height          =   492
      Left            =   2280
      TabIndex        =   8
      Top             =   2280
      Width           =   852
   End
   Begin VB.CommandButton cmdStart 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Start"
      Height          =   492
      Left            =   2280
      TabIndex        =   7
      Top             =   1560
      Width           =   852
   End
   Begin VB.Frame fraAlarmTimeOrRate 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Alarm Time"
      ForeColor       =   &H80000008&
      Height          =   1212
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   2892
      Begin VB.TextBox txtSecond 
         Appearance      =   0  'Flat
         Height          =   372
         Left            =   1920
         TabIndex        =   3
         Top             =   600
         Width           =   612
      End
      Begin VB.TextBox txtMinute 
         Appearance      =   0  'Flat
         Height          =   372
         Left            =   1080
         TabIndex        =   2
         Top             =   600
         Width           =   612
      End
      Begin VB.TextBox txtHour 
         Appearance      =   0  'Flat
         Height          =   372
         Left            =   240
         TabIndex        =   1
         Top             =   600
         Width           =   612
      End
      Begin VB.Label lblSecond 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Second"
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   1920
         TabIndex        =   6
         Top             =   360
         Width           =   852
      End
      Begin VB.Label lblMinute 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Minute"
         ForeColor       =   &H80000008&
         Height          =   252
         Left            =   1080
         TabIndex        =   5
         Top             =   360
         Width           =   852
      End
      Begin VB.Label lblHour 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "Hour"
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
      Left            =   2640
      Top             =   240
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
Dim Alarm%
Dim AlarmTime$
Dim AlarmSounded%
Dim SkipHours%
Dim SkipMinutes%
Dim SkipSeconds%

Private Sub AlarmEvents()
'Place code to execute on alarm here.
End Sub

Private Sub cmdStart_Click()
Dim AlarmHour$
Dim AlarmMinute$
Dim AlarmSecond$
AlarmHour = txtHour.Text
AlarmMinute = txtMinute.Text
AlarmSecond = txtSecond.Text
If AlarmHour = "" Then
    SkipHours = True
    AlarmHour = "00"
Else
    SkipHours = False
End If
If AlarmMinute = "" Then
    SkipMinutes = True
    AlarmMinute = "00"
Else
    SkipMinutes = False
End If
If AlarmSecond = "" Then
    SkipSeconds = True
    AlarmSecond = "00"
Else
    SkipSeconds = False
End If
AlarmTime = Format$(AlarmHour & ":" & AlarmMinute & ":" & AlarmSecond, "hh:mm:ss")
AlarmSounded = True
tmrAlarm.Enabled = True
End Sub

Private Sub cmdStop_Click()
tmrAlarm.Enabled = False
End Sub

Private Sub Form_Load()
StartUp
'This determines how often the program checks for alarm conditions:
tmrAlarm.Interval = 500
End Sub

Private Sub Form_Unload(Cancel%)
ShutDown
End
End Sub

Private Sub mnuPort_Click(Index%)
frmSelectPort.Show
End Sub

Private Sub tmrAlarm_Timer()
Dim CurrentTime$
Dim CurrentHour%
Dim CurrentMinute%
Dim CurrentSecond%
Dim HourMatch%
Dim MinuteMatch%
Dim SecondMatch%
'Save the current time.
CurrentTime = Time$
lblCurrentTime.Caption = CurrentTime
CurrentHour = DatePart("h", CurrentTime)
CurrentMinute = DatePart("n", CurrentTime)
CurrentSecond = DatePart("s", CurrentTime)
'See if the current hours, minutes, and seconds match the alarm conditions.
'If a field in AlarmTime is blank (unused), use the value from CurrentTime.
If SkipHours Then
    AlarmTime = Format$((DatePart("h", CurrentTime) & ":" & DatePart("n", AlarmTime) & ":" & DatePart("s", AlarmTime)), "hh:nn:ss")
End If
If SkipMinutes Then
    AlarmTime = Format$((DatePart("h", AlarmTime) & ":" & DatePart("n", CurrentTime) & ":" & DatePart("s", AlarmTime)), "hh:nn:ss")
End If
If SkipSeconds Then
    AlarmTime = Format$((DatePart("h", AlarmTime) & ":" & DatePart("n", CurrentTime) & ":" & DatePart("s", CurrentTime)), "hh:nn:ss")
End If
If (CurrentTime >= AlarmTime) And Not AlarmSounded Then
    AlarmSounded = True
    Beep
    lblTimeOfLastAlarm.Caption = CurrentTime
    AlarmEvents
End If
If (CurrentTime < AlarmTime) And AlarmSounded Then
    'If the alarm field(s) have cycled back to 0,
    'set AlarmSounded to false to allow the next alarm.
    AlarmSounded = False
End If
End Sub

