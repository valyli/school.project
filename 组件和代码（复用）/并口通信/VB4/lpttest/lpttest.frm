VERSION 4.00
Begin VB.Form frmMain 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   5304
   ClientLeft      =   4200
   ClientTop       =   3108
   ClientWidth     =   3360
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
   Height          =   5964
   Left            =   4152
   LinkTopic       =   "Form1"
   ScaleHeight     =   5304
   ScaleWidth      =   3360
   Top             =   2496
   Width           =   3456
   Begin VB.Frame fraStatusPort 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Status Port              "
      ForeColor       =   &H80000008&
      Height          =   1212
      Left            =   120
      TabIndex        =   38
      Top             =   3960
      Width           =   3132
      Begin VB.Label lblStatusBitNumber 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "7"
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   7
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblStatusBitNumber 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "6"
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   6
         Left            =   480
         TabIndex        =   54
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblStatusBitNumber 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "5"
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   5
         Left            =   840
         TabIndex        =   53
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblStatusBitNumber 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "4"
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   4
         Left            =   1200
         TabIndex        =   52
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblStatusBitNumber 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "3"
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   3
         Left            =   1560
         TabIndex        =   51
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblStatusBitNumber 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "2"
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   2
         Left            =   1920
         TabIndex        =   50
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblStatusBitNumber 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "1"
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   1
         Left            =   2280
         TabIndex        =   49
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblStatusBitNumber 
         Alignment       =   2  'Center
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "0"
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   0
         Left            =   2640
         TabIndex        =   48
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblStatusBit 
         Appearance      =   0  'Flat
         BackColor       =   &H00E0E0E0&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   0
         Left            =   2640
         TabIndex        =   47
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblStatusBit 
         Appearance      =   0  'Flat
         BackColor       =   &H00E0E0E0&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   1
         Left            =   2280
         TabIndex        =   46
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblStatusBit 
         Appearance      =   0  'Flat
         BackColor       =   &H00E0E0E0&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   2
         Left            =   1920
         TabIndex        =   45
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblStatusBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   3
         Left            =   1560
         TabIndex        =   44
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblStatusBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   4
         Left            =   1200
         TabIndex        =   43
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblStatusBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   5
         Left            =   840
         TabIndex        =   42
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblStatusBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   6
         Left            =   480
         TabIndex        =   41
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblStatusBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   7
         Left            =   120
         TabIndex        =   40
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblStatusPortByte 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   0
         Left            =   1080
         TabIndex        =   39
         Top             =   0
         Width           =   492
      End
   End
   Begin VB.Frame fraControlPort 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Control Port             "
      ForeColor       =   &H80000008&
      Height          =   1212
      Left            =   120
      TabIndex        =   20
      Top             =   2520
      Width           =   3132
      Begin VB.CommandButton cmdControlBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "0"
         Height          =   372
         Index           =   0
         Left            =   2640
         TabIndex        =   28
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdControlBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "1"
         Height          =   372
         Index           =   1
         Left            =   2280
         TabIndex        =   27
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdControlBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "2"
         Height          =   372
         Index           =   2
         Left            =   1920
         TabIndex        =   26
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdControlBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "3"
         Height          =   372
         Index           =   3
         Left            =   1560
         TabIndex        =   25
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdControlBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "4"
         Height          =   372
         Index           =   4
         Left            =   1200
         TabIndex        =   24
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdControlBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "5"
         Height          =   372
         Index           =   5
         Left            =   840
         TabIndex        =   23
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdControlBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "6"
         Height          =   372
         Index           =   6
         Left            =   480
         TabIndex        =   22
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdControlBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "7"
         Height          =   372
         Index           =   7
         Left            =   120
         TabIndex        =   21
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblControlBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   0
         Left            =   2640
         TabIndex        =   37
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblControlBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   1
         Left            =   2280
         TabIndex        =   36
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblControlBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   2
         Left            =   1920
         TabIndex        =   35
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblControlBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   3
         Left            =   1560
         TabIndex        =   34
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblControlBit 
         Appearance      =   0  'Flat
         BackColor       =   &H00E0E0E0&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   4
         Left            =   1200
         TabIndex        =   33
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblControlBit 
         Appearance      =   0  'Flat
         BackColor       =   &H00E0E0E0&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   5
         Left            =   840
         TabIndex        =   32
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblControlBit 
         Appearance      =   0  'Flat
         BackColor       =   &H00E0E0E0&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   6
         Left            =   480
         TabIndex        =   31
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblControlBit 
         Appearance      =   0  'Flat
         BackColor       =   &H00E0E0E0&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   7
         Left            =   120
         TabIndex        =   30
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblControlPortByte 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   0
         Left            =   1200
         TabIndex        =   29
         Top             =   0
         Width           =   492
      End
   End
   Begin VB.Frame fraDataPort 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Data Port          "
      ForeColor       =   &H80000008&
      Height          =   1212
      Left            =   120
      TabIndex        =   2
      Top             =   1080
      Width           =   3132
      Begin VB.CommandButton cmdDataBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "7"
         Height          =   372
         Index           =   7
         Left            =   120
         TabIndex        =   10
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdDataBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "6"
         Height          =   372
         Index           =   6
         Left            =   480
         TabIndex        =   9
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdDataBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "5"
         Height          =   372
         Index           =   5
         Left            =   840
         TabIndex        =   8
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdDataBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "4"
         Height          =   372
         Index           =   4
         Left            =   1200
         TabIndex        =   7
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdDataBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "3"
         Height          =   372
         Index           =   3
         Left            =   1560
         TabIndex        =   6
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdDataBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "2"
         Height          =   372
         Index           =   2
         Left            =   1920
         TabIndex        =   5
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdDataBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "1"
         Height          =   372
         Index           =   1
         Left            =   2280
         TabIndex        =   4
         Top             =   360
         Width           =   372
      End
      Begin VB.CommandButton cmdDataBitToggle 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         Caption         =   "0"
         Height          =   372
         Index           =   0
         Left            =   2640
         TabIndex        =   3
         Top             =   360
         Width           =   372
      End
      Begin VB.Label lblDataPortByte 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         ForeColor       =   &H80000008&
         Height          =   252
         Index           =   0
         Left            =   960
         TabIndex        =   19
         Top             =   0
         Width           =   492
      End
      Begin VB.Label lblDataBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   7
         Left            =   120
         TabIndex        =   18
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblDataBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   6
         Left            =   480
         TabIndex        =   17
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblDataBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   5
         Left            =   840
         TabIndex        =   16
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblDataBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   4
         Left            =   1200
         TabIndex        =   15
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblDataBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   3
         Left            =   1560
         TabIndex        =   14
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblDataBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   2
         Left            =   1920
         TabIndex        =   13
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblDataBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   1
         Left            =   2280
         TabIndex        =   12
         Top             =   720
         Width           =   372
      End
      Begin VB.Label lblDataBit 
         Appearance      =   0  'Flat
         BackColor       =   &H80000005&
         BorderStyle     =   1  'Fixed Single
         ForeColor       =   &H80000008&
         Height          =   372
         Index           =   0
         Left            =   2640
         TabIndex        =   11
         Top             =   720
         Width           =   372
      End
   End
   Begin VB.CommandButton cmdReadAll 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Read All"
      Height          =   612
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   1332
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

Private Sub cmdControlBitToggle_Click(Index As Integer)
'toggle a bit at the control port
Dim ControlPortData As Integer
ControlPortData = ControlPortRead(BaseAddress)
BitToggle ControlPortData, Index
ControlPortWrite BaseAddress, ControlPortData
ReadPorts (BaseAddress)
End Sub

Private Sub cmdDataBitToggle_Click(Index As Integer)
'toggle a bit at the data port
Dim DataPortData As Integer
DataPortData = DataPortRead(BaseAddress)
BitToggle DataPortData, Index
DataPortWrite BaseAddress, DataPortData
ReadPorts (BaseAddress)
End Sub

Private Sub cmdReadAll_Click()
ReadPorts (BaseAddress)
End Sub

Private Sub Form_Load()
StartUp
End Sub

Private Sub Form_Unload(Cancel As Integer)
ShutDown
End
End Sub

Private Sub mnuPort_Click(Index As Integer)
frmSelectPort.Show
End Sub

