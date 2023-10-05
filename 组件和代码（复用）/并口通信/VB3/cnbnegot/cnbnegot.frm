VERSION 2.00
Begin Form frmMain 
   Caption         =   " Parallel Port Complete"
   ClientHeight    =   2532
   ClientLeft      =   8076
   ClientTop       =   6060
   ClientWidth     =   4104
   ForeColor       =   &H00C0C0C0&
   Height          =   3192
   Left            =   8028
   LinkTopic       =   "Form1"
   ScaleHeight     =   2532
   ScaleWidth      =   4104
   Top             =   5448
   Width           =   4200
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
   Begin Label lblReceiveMode 
      Alignment       =   2  'Center
      Caption         =   "(Nibble Mode)"
      Height          =   252
      Left            =   2280
      TabIndex        =   6
      Top             =   1200
      Width           =   1572
   End
   Begin Label lblCompatibility 
      Alignment       =   2  'Center
      Caption         =   "(Compatibility Mode)"
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
Dim Timedout%
Dim DirectionSet%
Dim DataIn%
Dim LowNibble%
Dim HighNibble%
Dim ReadAnother%
Dim Character$
Dim OriginalControlPortData%

Sub cmdReadDataFromPort_Click ()
'Read characters from the parallel port.
'Display the received characters on the form.
Dim CharNumber%
Dim RequestedMode$
Dim SuccessfulNegotiation%
CharNumber = 0
Timedout = False
lblDataInDisplay.Caption = ""
'Tell the peripheral which mode to use.
Select Case Port(IndexOfSelectedPort).PortType
    Case "SPP"
	RequestedMode = "NibbleMode"
	lblReceiveMode.Caption = "(Nibble Mode)"
    Case Else
	RequestedMode = "ByteMode"
	lblReceiveMode.Caption = "(Byte Mode)"
End Select
SuccessfulNegotiation = Negotiate(RequestedMode)
If SuccessfulNegotiation Then
    tmrTimedOut.Enabled = True
    'Read characters at the port.
    ReadAnother = True
    Do
	DoEvents
	ReadByteFromPort (RequestedMode)
	lblDataInDisplay.Caption = lblDataInDisplay.Caption + Chr$(DataIn)
	CharNumber = CharNumber + 1
    Loop Until ReadAnother = False Or Timedout = True
    If Not (Timedout) Then
	MsgBox "Successful transfer", 0, "Result"
    End If
    CharNumber = 0
    tmrTimedOut.Enabled = False
Else
    MsgBox "Failed negotiation", 0, "Result"
End If
ReturnToCompatibilityMode
End Sub

Sub cmdWriteDataToPort_Click ()
Dim CharNumber%
Timedout = False
tmrTimedOut.Enabled = True
'Write the characters in the text box to the parallel port.
For CharNumber = 1 To 16
    If Not (Timedout) Then
	'Write each character in sequence
	Character = Mid$(txtDataOut.Text, CharNumber, 1)
	If Character = "" Then Character = " "
	WriteByteToPort
    End If
Next CharNumber
If Not (Timedout) Then
    MsgBox "Successful transfer", 0, "Result"
End If
tmrTimedOut.Enabled = False
End Sub

Sub Form_Load ()
Startup
Dim PortExists%
'Save the original control-port settings.
ControlPortData = ControlPortRead(BaseAddress)
OriginalControlPortData = ControlPortData
Load frmSelectPort
frmSelectPort.Hide
frmMain.Show
'Timeout limit for peripheral.
tmrTimedOut.Interval = 5000
tmrTimedOut.Enabled = False
txtDataOut.Text = "abcdefghijklmnop"
'Initialize control bits
BitSet ControlPortData, 0
BitSet ControlPortData, 1
BitReset ControlPortData, 3
BitReset ControlPortData, 5
ControlPortWrite BaseAddress, ControlPortData
PortExists = TestPort(IndexOfSelectedPort)
End Sub

Sub Form_Unload (Cancel%)
WriteIniData
ControlPortWrite BaseAddress, OriginalControlPortData
End Sub

Sub MakeByteFromNibbles ()
'Get the 8 bits from LowNibble and HighNibble
'and arrange them into a byte.
Dim Bit0%
Dim Bit1%
Dim Bit2%
Dim Bit3%
Dim Bit4%
Dim Bit5%
Dim Bit6%
Dim Bit7%

Bit0 = BitRead(LowNibble, 5)
Bit1 = BitRead(LowNibble, 4) * 2
Bit2 = BitRead(LowNibble, 3) * 4
Bit3 = BitRead(LowNibble, 7) * 8
Bit4 = BitRead(HighNibble, 5) * &H10
Bit5 = BitRead(HighNibble, 4) * &H20
Bit6 = BitRead(HighNibble, 3) * &H40
Bit7 = BitRead(HighNibble, 7) * &H80
DataIn = Bit0 + Bit1 + Bit2 + Bit3 + Bit4 + Bit5 + Bit6 + Bit7
End Sub

Sub mnuPort_Click (Index%)
'Show the dialog box that enables users to select
'and test a port.
frmSelectPort.Show

End Sub

Function Negotiate (RequestedMode$)
Dim ExtensibilityByte%
Dim XFlag%
Dim S4%
Select Case RequestedMode
    Case "NibbleMode"
	ExtensibilityByte = 0
    Case "ByteMode"
	ExtensibilityByte = 1
    End Select
ControlPortData = ControlPortRead(BaseAddress)
DataPortWrite BaseAddress, ExtensibilityByte
BitSet ControlPortData, 3
BitSet ControlPortData, 0
BitReset ControlPortData, 1
ControlPortWrite BaseAddress, ControlPortData
tmrTimedOut.Enabled = True
'Wait for S3=1, S4=1, S5=1, S6=0.
Do
    DoEvents
    StatusPortData = StatusPortRead(BaseAddress)
Loop Until ((StatusPortData And &H78) = &H38) Or Timedout
S4 = BitRead(StatusPortData, 4)
If S4 = 1 Then
    Negotiate = True
Else
    Negotiate = False
End If
'Peripheral latches the byte.
BitReset ControlPortData, 0
ControlPortWrite BaseAddress, ControlPortData
BitSet ControlPortData, 0
BitSet ControlPortData, 1
ControlPortWrite BaseAddress, ControlPortData
'Wait for S3=0, S5=0, S6=1.
Do
DoEvents
    StatusPortData = StatusPortRead(BaseAddress)
Loop Until ((StatusPortData And &H68) = &H40) Or Timedout
'If using Byte mode, disable the data outputs.
If RequestedMode = "ByteMode" Then
    BitSet ControlPortData, 5
    ControlPortWrite BaseAddress, ControlPortData
End If
tmrTimedOut.Enabled = False
End Function

Sub ReadByteFromPort (RequestedMode$)
'Read one character from the parallel port
'Uses nibble or byte mode.
Dim S6%
ControlPortData = ControlPortRead(BaseAddress)
Select Case RequestedMode
    Case "NibbleMode"
	'When S6=0, read the status port into LowNibble and set C1=1.
	Do
	    LowNibble = StatusPortRead(BaseAddress)
	    S6 = BitRead(LowNibble, 6)
	    DoEvents
	    If Timedout Then Exit Sub
	Loop Until S6 = 0
	BitSet ControlPortData, 1
	ControlPortWrite BaseAddress, ControlPortData
	'When the peripheral responds by setting S6=1, set C1=0.
	Do
	    StatusPortData = StatusPortRead(BaseAddress)
	    S6 = BitRead(StatusPortData, 6)
	    DoEvents
	    If Timedout Then Exit Sub
	Loop Until S6 = 1
	BitReset ControlPortData, 1
	ControlPortWrite BaseAddress, ControlPortData
	'When S6=0 again, read the status port into HighNibble and set C1=1.
	Do
	    HighNibble = StatusPortRead(BaseAddress)
	    S6 = BitRead(HighNibble, 6)
	    DoEvents
	    If Timedout Then Exit Sub
	Loop Until S6 = 0
	BitSet ControlPortData, 1
	ControlPortWrite BaseAddress, ControlPortData
	'When the peripheral responds by setting S6=1, set C1=0.
	Do
	    StatusPortData = StatusPortRead(BaseAddress)
	    S6 = BitRead(StatusPortData, 6)
	    DoEvents
	    If Timedout Then Exit Sub
	Loop Until S6 = 1
	BitReset ControlPortData, 1
	ControlPortWrite BaseAddress, ControlPortData
	MakeByteFromNibbles
	'If any of S3 or S5 =1, the transmission is complete.
	If (StatusPortData And &H8) > 0 Then ReadAnother = False

    Case "ByteMode"
	BitSet ControlPortData, 0
	BitReset ControlPortData, 1
	ControlPortWrite BaseAddress, ControlPortData
	'When S6=0, read the data port and set control bits.
	Do
	    StatusPortData = StatusPortRead(BaseAddress)
	    S6 = BitRead(StatusPortData, 6)
	    DoEvents
	    If Timedout Then Exit Sub
	Loop Until S6 = 0
	DataIn = DataPortRead(BaseAddress)
	BitReset ControlPortData, 0
	BitSet ControlPortData, 1
	ControlPortWrite BaseAddress, ControlPortData
	'Wait for peripheral to respond by setting S6=1.
	Do
	    StatusPortData = StatusPortRead(BaseAddress)
	    S6 = BitRead(StatusPortData, 6)
	    DoEvents
	    If Timedout Then Exit Sub
	Loop Until S6 = 1
	BitReset ControlPortData, 1
	ControlPortWrite BaseAddress, ControlPortData
	'If S3 =1, the transmission is complete.
	If (StatusPortData And 8) > 0 Then
	    ReadAnother = False
	    BitSet ControlPortData, 0
	    ControlPortWrite BaseAddress, ControlPortData
	End If
End Select
End Sub

Sub ReturnToCompatibilityMode ()
Dim S6%
BitSet ControlPortData, 0
BitSet ControlPortData, 1
BitReset ControlPortData, 3
ControlPortWrite BaseAddress, ControlPortData
tmrTimedOut.Enabled = True
'Wait for S3=1, S4=1, S6=0, S7=1.
Do
    DoEvents
    StatusPortData = StatusPortRead(BaseAddress)
    Loop Until ((StatusPortData And &HD8) = &H98) Or Timedout
BitReset ControlPortData, 1
ControlPortWrite BaseAddress, ControlPortData
Do
    DoEvents
    StatusPortData = StatusPortRead(BaseAddress)
    S6 = BitRead(StatusPortData, 6)
Loop Until (S6 = 1) Or Timedout
BitSet ControlPortData, 1
'Re-enable the data outputs
BitReset ControlPortData, 5
ControlPortWrite BaseAddress, ControlPortData
tmrTimedOut.Enabled = False
End Sub

Sub tmrTimedOut_Timer ()
Timedout = True
MsgBox "Peripheral not responding", 0, "Warning"
tmrTimedOut.Enabled = False
ReturnToCompatibilityMode
End Sub

Sub WriteByteToPort ()
'Write one character to the parallel port
'Uses compatibility mode handshaking.
Dim S7%
'Wait for S7 (Busy) to be low.
Do
    StatusPortData = StatusPortRead(BaseAddress)
    S7 = BitRead(StatusPortData, 7)
    DoEvents
    If Timedout Then Exit Sub
    Loop Until S7 = 0
'Write the character.
If Character = "" Then Character = " "
DataPortWrite BaseAddress, Asc(Character)
'Complete the handshake.
BitReset ControlPortData, 0
ControlPortWrite BaseAddress, ControlPortData
Do
    StatusPortData = StatusPortRead(BaseAddress)
    S7 = BitRead(StatusPortData, 7)
    DoEvents
    If Timedout Then Exit Sub
    Loop Until S7 = 1
BitSet ControlPortData, 0
ControlPortWrite BaseAddress, ControlPortData
End Sub

