VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Complete"
   ClientHeight    =   2532
   ClientLeft      =   3984
   ClientTop       =   5160
   ClientWidth     =   4224
   ForeColor       =   &H00C0C0C0&
   Height          =   3192
   Left            =   3936
   LinkTopic       =   "Form1"
   ScaleHeight     =   2532
   ScaleWidth      =   4224
   Top             =   4548
   Width           =   4320
   Begin TextBox txtDataOut 
      Height          =   372
      Left            =   120
      MaxLength       =   16
      MultiLine       =   -1  'True
      TabIndex        =   2
      Text            =   "Hello, world"
      Top             =   1560
      Width           =   1932
   End
   Begin CommandButton cmdReadDataFromPort 
      Caption         =   "Receive"
      Height          =   732
      Left            =   2280
      TabIndex        =   1
      Top             =   120
      Width           =   1572
   End
   Begin Timer tmrTimedOut 
      Enabled         =   0   'False
      Interval        =   5000
      Left            =   3720
      Top             =   2040
   End
   Begin CommandButton cmdWriteDataToPort 
      Caption         =   "Send"
      Height          =   732
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1572
   End
   Begin Label lblByte 
      Alignment       =   2  'Center
      Caption         =   "(EPP Mode)"
      Height          =   252
      Left            =   2280
      TabIndex        =   6
      Top             =   1200
      Width           =   1572
   End
   Begin Label lblCompatibility 
      Alignment       =   2  'Center
      Caption         =   "(EPP Mode)"
      Height          =   372
      Left            =   120
      TabIndex        =   7
      Top             =   1200
      Width           =   1812
   End
   Begin Label lblDataInDisplay 
      BorderStyle     =   1  'Fixed Single
      Height          =   372
      Left            =   2160
      TabIndex        =   5
      Top             =   1560
      Width           =   1932
      WordWrap        =   -1  'True
   End
   Begin Label lblDataIn 
      Alignment       =   2  'Center
      Caption         =   "Data In"
      Height          =   252
      Left            =   2400
      TabIndex        =   4
      Top             =   960
      Width           =   1332
   End
   Begin Label lblDataOut 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      Caption         =   "DataOut"
      Height          =   252
      Left            =   240
      TabIndex        =   3
      Top             =   960
      Width           =   1584
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

Dim StatusPortData%
Dim ControlPortData%
Dim TimedOut%
Dim DirectionSet%
Dim DataIn%
Dim LowNibble%
Dim HighNibble%
Dim ReadAnother%
Dim Character$

Sub cmdReadDataFromPort_Click ()
'Read characters from the parallel port.
'Display the received characters on the form.
Dim CharNumber%
CharNumber = 0
TimedOut = False
lblDataInDisplay.Caption = ""
DirectionSet = DirectionRequest("PeripheralToPc")
tmrTimedOut.Enabled = True

'Read bytes at the port.
'After each byte, read the status port.
'Stop reading if S3 =1 (indicates end of transmission).
ReadAnother = True
Do Until ReadAnother = False Or TimedOut = True
    DoEvents
    ReadByteFromPort
    lblDataInDisplay.Caption = lblDataInDisplay.Caption + Chr$(DataIn)
    CharNumber = CharNumber + 1
Loop
    If Not (TimedOut) Then
	MsgBox "Successful transfer", 0, "Result"
    End If
CharNumber = 0
tmrTimedOut.Enabled = False
'Re-enable the data outputs.
DirectionSet = DirectionRequest("PcToPeripheral")
End Sub

Sub cmdWriteDataToPort_Click ()
Dim CharNumber%
TimedOut = False
tmrTimedOut.Enabled = True
ControlPortData = ControlPortRead(BaseAddress)
BitSet ControlPortData, 1
ControlPortWrite ControlPortData, BaseAddress
'Write the characters in the text box to the parallel port.
For CharNumber = 1 To 16
    If Not (TimedOut) Then
	'Write each character in sequence
	Character = Mid$(txtDataOut.Text, CharNumber, 1)
	If Character = "" Then Character = " "
	WriteByteToPort
    End If
Next CharNumber
If Not (TimedOut) Then
    MsgBox "Successful transfer", 0, "Result"
End If
tmrTimedOut.Enabled = False
End Sub

Function DirectionRequest% (Direction$)
Dim S3%
Dim C3%
Direction = LCase$(Direction)
ControlPortData = ControlPortRead(BaseAddress)
BitSet ControlPortData, 1
'Set Control port bits to match the selected direction.
'For control bit 5,
'0 enables the data outputs, 1 tristates the outputs.
Select Case Direction
    Case "pctoperipheral"
	BitSet ControlPortData, 3
	BitReset ControlPortData, 5
	C3 = 1
    Case "peripheraltopc"
	BitReset ControlPortData, 3
	BitSet ControlPortData, 5
	C3 = 0
    Case Else
    End Select
ControlPortWrite BaseAddress, ControlPortData
tmrTimedOut.Enabled = True
Do
    'Wait for the peripheral to acknowldege the
    'direction change.
    StatusPortData = StatusPortRead(BaseAddress)
    S3 = BitRead(StatusPortData, 3)
    DoEvents
    If TimedOut Then Exit Function
Loop Until C3 = S3
If C3 = S3 Then tmrTimedOut.Enabled = False
End Function

Sub Form_Load ()
Startup
DirectionSet = DirectionRequest("PcToPeripheral")
'Timeout limit for peripheral.
tmrTimedOut.Interval = 5000
tmrTimedOut.Enabled = False
EPPDataPort0Address = BaseAddress + 4
'Initial test data
txtDataOut.Text = "0123456789ABCDEF"

End Sub

Sub Form_Unload (Cancel%)
Shutdown
End
End Sub

Sub mnuPort_Click (Index%)
frmSelectPort.Show

End Sub

Sub ReadByteFromPort ()
'Read one character from the parallel port.
'Uses EPP mode.
Dim S7%
Dim S3%
Dim DataPortData%
'Wait for S7=0.
Do
    StatusPortData = StatusPortRead(BaseAddress)
    S7 = BitRead(StatusPortData, 7)
    If ReadEppTimeoutBit(BaseAddress) = 1 Then
	tmrTimedOut_Timer
    End If
    DoEvents
    If TimedOut Then Exit Sub
Loop Until S7 = 0
'Read the byte
DataIn = DataPortRead(EPPDataPort0Address)

'Check the timeout bit.
'If it's set, clear it and display the timeout message.
Dim ByteTimeout%
ByteTimeout = ReadEppTimeoutBit(BaseAddress)
If ByteTimeout = 1 Then
    tmrTimedOut_Timer
End If

'If S3 =1, the transmission is complete.
StatusPortData = StatusPortRead(BaseAddress)
If (StatusPortData And 8) > 0 Then
    ReadAnother = False
End If
End Sub

Sub tmrTimedOut_Timer ()
'On timeout, display a message and switch
'direction to PC-to-peripheral.
TimedOut = True
MsgBox "Peripheral not responding", 0, "Warning"
DirectionSet = DirectionRequest("PcToPeripheral")
tmrTimedOut.Enabled = False
End Sub

Sub WriteByteToPort ()
'Write one character to the parallel port.
'Uses EPP mode.
Dim S7%
Dim ByteTimeout%
'Wait for Busy (S7)=0, then write a byte to the data port.
Do
    StatusPortData = StatusPortRead(BaseAddress)
    S7 = BitRead(StatusPortData, 7)
    DoEvents
    If TimedOut Then Exit Sub
Loop Until S7 = 0
If Character = "" Then Character = " "
DataPortWrite EPPDataPort0Address, Asc(Character)

'Check the timeout bit.
'If it's set, clear it and display the timeout message.
ByteTimeout = ReadEppTimeoutBit(BaseAddress)
If ByteTimeout = 1 Then
    tmrTimedOut_Timer
End If
End Sub

