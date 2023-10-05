VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Complete"
   ClientHeight    =   2352
   ClientLeft      =   4860
   ClientTop       =   1668
   ClientWidth     =   4224
   ForeColor       =   &H00C0C0C0&
   Height          =   3012
   Left            =   4812
   LinkTopic       =   "Form1"
   ScaleHeight     =   2352
   ScaleWidth      =   4224
   Top             =   1056
   Width           =   4320
   Begin TextBox txtDataOut 
      Height          =   492
      Left            =   120
      MaxLength       =   32
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
      Caption         =   "(ECP Mode)"
      Height          =   252
      Left            =   2280
      TabIndex        =   6
      Top             =   1200
      Width           =   1572
   End
   Begin Label lblCompatibility 
      Alignment       =   2  'Center
      Caption         =   "(ECP Mode)"
      Height          =   372
      Left            =   120
      TabIndex        =   7
      Top             =   1200
      Width           =   1812
   End
   Begin Label lblDataInDisplay 
      BorderStyle     =   1  'Fixed Single
      Height          =   492
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
Dim ReadAnother%
Dim Character$
Dim EcrAddress%
Dim ECPDataPortAddress%
Dim EcpMode%
Dim FifoEmpty%

Function CheckFifoEmpty% ()
'Bit 0 of the Ecr indicates Fifo empty.
'1=empty; 0=not empty
EcrData = Inp(EcrAddress)
If BitRead(EcrData, 0) = 1 Then
    CheckFifoEmpty = True
Else CheckFifoEmpty = False
End If
'If BitRead(EcrData, 2) = 1 Then
'    CheckFifoEmpty = False
'Else CheckFifoEmpty = True
'End If

Dim FifoFull%
FifoFull = BitRead(EcrData, 1)
End Function

Function CheckFifoFull ()
'Bit 1 of the Ecr indicates Fifo full.
'1=full; 0=not full
Dim FifoFull%
EcrData = Inp(EcrAddress)
If BitRead(EcrData, 1) = 1 Then
    CheckFifoFull = True
Else
    CheckFifoFull = False
End If
End Function

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
ReadAnother = True
'Empty the Fifo
Do
    FifoEmpty = CheckFifoEmpty()
Loop Until FifoEmpty = True
Do Until CharNumber = 32 Or TimedOut = True
    DoEvents
    FifoEmpty = CheckFifoEmpty()
    If FifoEmpty = False Then
	DoEvents
	DataIn = DataPortRead(ECPDataPortAddress)
	lblDataInDisplay.Caption = lblDataInDisplay.Caption + Chr$(DataIn)
	CharNumber = CharNumber + 1
    End If
Loop
    If Not (TimedOut) Then
	MsgBox "Successful transfer", 0, "Result"
    End If
lblDataInDisplay.Caption = ""
'Set C2 to tell peripheral to stop sending
BitSet ControlPortData, 2
'ControlPortWrite BaseAddress, ControlPortData
CharNumber = 0
tmrTimedOut.Enabled = False
'Re-enable the data outputs.
DirectionSet = DirectionRequest("PcToPeripheral")
End Sub

Sub cmdWriteDataToPort_Click ()
Dim CharNumber%
Dim FifoFull%
TimedOut = False
tmrTimedOut.Enabled = True
DirectionSet = DirectionRequest("PcToPeripheral")
tmrTimedOut.Enabled = True
'Write the characters in the text box to the parallel port.
For CharNumber = 1 To 32
    Do
	DoEvents
	FifoFull = CheckFifoFull()
    Loop Until (Not (FifoFull)) Or (TimedOut = True)
    'Write each character in sequence
    Character = Mid$(txtDataOut.Text, CharNumber, 1)
    If Character = "" Then Character = " "
    DataPortWrite ECPDataPortAddress, Asc(Character)
Next CharNumber
Do
    DoEvents
    FifoEmpty = CheckFifoEmpty()
Loop Until FifoEmpty Or TimedOut
If Not (TimedOut) Then
    MsgBox "Successful transfer", 0, "Result"
End If
tmrTimedOut.Enabled = False
End Sub

Function DirectionRequest% (Direction$)
Dim S3%
Dim PeripheralResponse
'Use the ECP's PS2 mode to switch directions.
SetEcpMode (1)
Direction = LCase$(Direction)
ControlPortData = ControlPortRead(BaseAddress)
BitSet ControlPortData, 0
BitSet ControlPortData, 3
'Set Control port bits to match the selected direction.
'For control bit 5,
'0 enables the data outputs, 1 tristates the outputs.
Select Case Direction
    Case "pctoperipheral"
	BitReset ControlPortData, 1
	BitSet ControlPortData, 2
	PeripheralResponse = 1
    Case "peripheraltopc"
	BitSet ControlPortData, 1
	BitSet ControlPortData, 5
	ControlPortWrite BaseAddress, ControlPortData
	BitReset ControlPortData, 2
	PeripheralResponse = 0
    Case Else
    End Select
ControlPortWrite BaseAddress, ControlPortData
tmrTimedOut.Enabled = True
Do
    'Wait for the peripheral to acknowledge the
    'direction change.
    StatusPortData = StatusPortRead(BaseAddress)
    S3 = BitRead(StatusPortData, 3)
    DoEvents
    If TimedOut Then Exit Function
Loop Until S3 = PeripheralResponse
If S3 = 1 Then
    tmrTimedOut.Enabled = False
    'Enable the data outputs only after the peripheral
    'has acknowledged the direction change to
    'PC-to-peripheral.
    BitReset ControlPortData, 5
    ControlPortWrite BaseAddress, ControlPortData
End If
'Switch to ECP mode.
SetEcpMode (3)
End Function

Sub Form_Load ()
Dim PortIndex%
Startup
ECPDataPortAddress = BaseAddress + &H400
EcrAddress = BaseAddress + &H402

frmMain.Show
'Timeout limit for peripheral.
tmrTimedOut.Interval = 5000
tmrTimedOut.Enabled = False
'Initial test data
txtDataOut.Text = "000102030405060708090A0B0C0D0E0F"
'Initial Ecr setting (PS2 mode, no DMA or interrupts)
Out EcrAddress, &H30
'DirectionSet = DirectionRequest("PcToPeripheral")
Do
    DoEvents
    FifoEmpty = CheckFifoEmpty()
    DataIn = DataPortRead(ECPDataPortAddress)
Loop Until FifoEmpty



End Sub

Sub Form_Unload (Cancel%)
Shutdown
End
End Sub

Sub mnuPort_Click (index%)
'Show the dialog box that enables users to select
'and test ports.
frmSelectPort.Show

End Sub

Sub tmrTimedOut_Timer ()
'On timeout, display a message and switch
'direction to PC-to-peripheral.
TimedOut = True
MsgBox "Peripheral not responding", 0, "Warning"
DirectionSet = DirectionRequest("PcToPeripheral")
tmrTimedOut.Enabled = False
End Sub

