VERSION 4.00
Begin VB.Form frmMain 
   Appearance      =   0  'Flat
   BackColor       =   &H80000005&
   Caption         =   "Parallel Port Complete"
   ClientHeight    =   1692
   ClientLeft      =   3816
   ClientTop       =   4944
   ClientWidth     =   2892
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
   Height          =   2352
   Left            =   3768
   LinkTopic       =   "Form1"
   ScaleHeight     =   1692
   ScaleWidth      =   2892
   Top             =   4332
   Width           =   2988
   Begin VB.CommandButton cmdCancelTransfer 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Cancel"
      Enabled         =   0   'False
      Height          =   612
      Left            =   1560
      TabIndex        =   1
      Top             =   120
      Width           =   1212
   End
   Begin VB.Timer tmrWatchForIncomingFile 
      Enabled         =   0   'False
      Left            =   1080
      Top             =   1200
   End
   Begin VB.Timer tmrTimedOut 
      Enabled         =   0   'False
      Interval        =   5000
      Left            =   120
      Top             =   1200
   End
   Begin VB.CommandButton cmdWriteFileToPort 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      Caption         =   "Send File"
      Enabled         =   0   'False
      Height          =   612
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1332
   End
   Begin MSComDlg.CommonDialog cdlFileReceived 
      Left            =   1560
      Top             =   1200
      _Version        =   65536
      _ExtentX        =   677
      _ExtentY        =   677
      _StockProps     =   0
      CancelError     =   -1  'True
   End
   Begin MSComDlg.CommonDialog cdlFileToSend 
      Left            =   600
      Top             =   1200
      _Version        =   65536
      _ExtentX        =   677
      _ExtentY        =   677
      _StockProps     =   0
      CancelError     =   -1  'True
   End
   Begin VB.Label lblProgress 
      Appearance      =   0  'Flat
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   192
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   60
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
Private Declare Function GetPrivateProfileString% Lib "Kernel" (ByVal lpApplicationName$, ByVal lpKeyName$, ByVal lpDefault$, ByVal lpReturnedString$, ByVal nSize%, ByVal lpFileName$)
Private Declare Function WritePrivateProfileString% Lib "Kernel" (ByVal lpSection$, ByVal lpKeyName As Any, ByVal lpString$, ByVal lplFileName$)
Dim StatusPortData%
Dim TimedOut%
Dim LowNibble%
Dim HighNibble%
Dim FileLengthByte%(0 To 3)
Dim S6%
Dim TimedOutInterval&
Dim TransferCancelled%

Private Sub cmdCancelTransfer_Click()
'Simulate a timeout to cause the transfer to end.
TransferCancelled = True
tmrTimedOut.Interval = 1
InitializeToIdleCondition
End Sub

Private Sub cmdWriteFileToPort_Click()
'Allow the user to select a file from a common-dialog box.
'Then write the filename, file length, and the file itself to the parallel port.
Const OFN_FILEMUSTEXIST = &H1000&
Dim ByteNumber&
Dim ByteToWrite%
Dim SelectedFile$
Dim CharacterRead$
Dim FileLength&
Dim FileNameToSend$
tmrWatchForIncomingFile.Enabled = False
tmrTimedOut.Interval = 0
TimedOut = False
On Error GoTo ErrorHandlerWr
cdlFileToSend.Filter = "All files (*.*)|*.*"
cdlFileToSend.filename = ""
cdlFileToSend.Flags = OFN_FILEMUSTEXIST

'Get the selected file from the common dialog box.
cdlFileToSend.Action = 1
cmdWriteFileToPort.Enabled = False
'Write the filename and length to the port.
SelectedFile = cdlFileToSend.filename
FileLength = FileLen(SelectedFile)
DivideFileLengthInto4Bytes (FileLength)
cmdCancelTransfer.Enabled = True
lblProgress.Caption = "Waiting for response..."
'Extract the filename from SelectedFile, which includes a path.
FileNameToSend = GetFilenameToSend(SelectedFile)
'Write the filename to the port.
For ByteNumber = 1 To 12
    WriteByteToPort Asc(Mid$(FileNameToSend, ByteNumber, 1))
Next ByteNumber
'Write the file length to the port.
For ByteNumber = 0 To 3
    WriteByteToPort FileLengthByte(ByteNumber)
Next ByteNumber
'Enable the timeout timer.
tmrTimedOut.Interval = TimedOutInterval
lblProgress.Caption = "Transferring file..."
Open SelectedFile For Input As #1
For ByteNumber = 1 To FileLength
   'Read 1 character from the file; send its ASCII code
   WriteByteToPort Asc(Input$(1, #1))
Next ByteNumber
If Not (TimedOut) Then
    lblProgress.Caption = "Successful transfer"
End If
GoTo EndTransferWr

ErrorHandlerWr:
TransferCancelled = True
Resume EndTransferWr

EndTransferWr:
Close #1
If TransferCancelled = True Then
    DisplayCancelMessage
End If
InitializeToIdleCondition
End Sub

Private Sub DisplayCancelMessage()
lblProgress.Caption = "Transfer cancelled."
TransferCancelled = False
End Sub

Private Sub DivideByteIntoNibbles(ByteToDivide%)
'Divide a byte into low and high nibbles.
'Each nibble is stored in a byte.
'Bit 3 is the strobe.
'Bits 5-7 are unused.
'Original bit 0 = Low Nibble bit 0
'Original bit 1 = Low Nibble bit 1
'Original bit 2 = Low Nibble bit 2
'Original bit 3 = Low Nibble bit 4
'Original bit 4 = High Nibble bit 0
'Original bit 5 = High Nibble bit 1
'Original bit 6 = High Nibble bit 2
'Original bit 7 = High Nibble bit 4
Dim Bit0%
Dim Bit1%
Dim Bit2%
Dim Bit4%
Bit0 = ByteToDivide And 1
Bit1 = ByteToDivide And 2
Bit2 = ByteToDivide And 4
Bit4 = (ByteToDivide And 8) * 2
LowNibble = Bit0 + Bit1 + Bit2 + Bit4
Bit0 = (ByteToDivide And &H10) \ &H10
Bit1 = (ByteToDivide And &H20) \ &H10
Bit2 = (ByteToDivide And &H40) \ &H10
Bit4 = (ByteToDivide And &H80) \ 8
HighNibble = Bit0 + Bit1 + Bit2 + Bit4
End Sub

Private Sub DivideFileLengthInto4Bytes(FileLength&)
FileLengthByte(0) = FileLength And &HFF
FileLengthByte(1) = ((FileLength \ &H100) And &HFF)
FileLengthByte(2) = ((FileLength \ &H10000) And &HFF)
FileLengthByte(3) = ((FileLength \ &H1000000) And &HFF)
End Sub

Private Sub Form_Load()
StartUp
InitializeToIdleCondition
End Sub

Private Sub Form_Unload(Cancel%)
WriteIniData
Unload frmNewPortAddress
Unload frmSelectPort
End Sub

Private Function GetFileLength&()
GetFileLength = FileLengthByte(0) + FileLengthByte(1) * &H100 + FileLengthByte(2) * &H10000 + FileLengthByte(3) * &H1000000
End Function

Private Function GetFilenameToSend$(SelectedFile$)
'SelectedFile contains the filename and path.
'Extract the file name only into FileNameToSend.
'FilenameToSend is 12 characters. Extra characters are spaces.
Dim Character$
Dim CharacterNumber%
Dim ByteNumber%
Dim FileNameToSend$

FileNameToSend = ""
ByteNumber = Len(SelectedFile)
'Starting from the right, find the filename in the string.
Do
    Character = Mid$(SelectedFile, ByteNumber, 1)
    FileNameToSend = Character & FileNameToSend
    ByteNumber = ByteNumber - 1
Loop Until ByteNumber = Len(SelectedFile) - 13 Or ByteNumber = 0 Or Character = "\"
If Character = "\" Then
    FileNameToSend = Right$(FileNameToSend, Len(FileNameToSend) - 1)
End If
'Pad the filename with spaces until it has 12 characters.
For CharacterNumber = Len(FileNameToSend) + 1 To 12
    FileNameToSend = FileNameToSend & " "
Next CharacterNumber
GetFilenameToSend = FileNameToSend
End Function

Private Sub InitializeToIdleCondition()
TimedOutInterval = 5000
tmrTimedOut.Interval = TimedOutInterval
tmrTimedOut.Enabled = False
tmrWatchForIncomingFile.Interval = 1000
'Initialize D3 (strobe) to 1.
DataPortWrite BaseAddress, 8
'Wait for the opposite end to set D3=1 (not busy).
Do
    StatusPortData = StatusPortRead(BaseAddress)
    S6 = BitRead(StatusPortData, 6)
    DoEvents
Loop Until S6 = 1
tmrWatchForIncomingFile.Enabled = True
cmdWriteFileToPort.Enabled = True
cmdCancelTransfer.Enabled = False
End Sub

Private Function MakeByteFromNibbles%(LowNibble%, HighNibble%)
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

Bit0 = BitRead(LowNibble, 3)
Bit1 = BitRead(LowNibble, 4) * 2
Bit2 = BitRead(LowNibble, 5) * 4
Bit3 = BitRead(LowNibble, 7) * 8
Bit4 = BitRead(HighNibble, 3) * &H10
Bit5 = BitRead(HighNibble, 4) * &H20
Bit6 = BitRead(HighNibble, 5) * &H40
Bit7 = BitRead(HighNibble, 7) * &H80
MakeByteFromNibbles = Bit0 + Bit1 + Bit2 + Bit3 + Bit4 + Bit5 + Bit6 + Bit7
End Function

Private Sub mnuPort_Click(Index%)
frmSelectPort.Show

End Sub

Private Function ReadByteFromPort%()
'Read a byte of data at the status port, in 2 nibbles.
tmrTimedOut.Enabled = True
'When S6=0, set D3=0.
Do
    LowNibble = StatusPortRead(BaseAddress)
    S6 = BitRead(LowNibble, 6)
    DoEvents
    Loop Until (S6 = 0) Or TimedOut
DataPortWrite BaseAddress, 0
'When the peripheral responds by setting S6=1, set D3=1.
'LowNibble holds 4 bits of data.
Do
    LowNibble = StatusPortRead(BaseAddress)
    S6 = BitRead(LowNibble, 6)
    DoEvents
Loop Until (S6 = 1) Or TimedOut
DataPortWrite BaseAddress, 8
'When S6=0 again, set D3=0.
Do
    HighNibble = StatusPortRead(BaseAddress)
    S6 = BitRead(HighNibble, 6)
    DoEvents
Loop Until (S6 = 0) Or TimedOut
DataPortWrite BaseAddress, 0
'When the peripheral responds by setting S6=1, set D3=1.
'HighNibble holds 4 bits of data.
Do
    HighNibble = StatusPortRead(BaseAddress)
    S6 = BitRead(HighNibble, 6)
    DoEvents
Loop Until (S6 = 1) Or TimedOut
DataPortWrite BaseAddress, 8
ReadByteFromPort = MakeByteFromNibbles(LowNibble, HighNibble)
tmrTimedOut.Enabled = False
End Function

Private Sub ReadFileFromPort()
'This subroutine runs when tmrWatchForIncomingFile detects an incoming file.
'Read the filename and display it in a common-dialog box.
'When the user has selected a filename and path, read the file length
'and store the file in the selected filename.
Dim FileLength&
Dim ByteRead%
Dim ByteNumber&
Const OFN_OVERWRITEPROMPT = &H2&
Dim FileReceived$
Dim CharacterToWrite$
tmrWatchForIncomingFile.Enabled = False
tmrTimedOut.Interval = TimedOutInterval
cdlFileReceived.Filter = "All files (*.*)|*.*"
cdlFileReceived.filename = ""
cdlFileReceived.Flags = OFN_OVERWRITEPROMPT
On Error GoTo ErrorHandlerRd
FileReceived = ""

'Read the filename and display the common-dialog box.
For ByteNumber = 1 To 12
    FileReceived = FileReceived & Chr$(ReadByteFromPort())
Next ByteNumber
cdlFileReceived.filename = FileReceived
cdlFileReceived.Action = 2
lblProgress.Caption = "Receiving file..."
cmdCancelTransfer.Enabled = True
Open cdlFileReceived.filename For Output As #1

'Read the file length.
For ByteNumber = 0 To 3
    FileLengthByte(ByteNumber) = ReadByteFromPort()
Next ByteNumber

'Read and store the file.
If Not (TimedOut) Then
    FileLength = GetFileLength()
    For ByteNumber = 1 To FileLength
        CharacterToWrite = Chr$(ReadByteFromPort())
        Print #1, CharacterToWrite;
    Next ByteNumber
    lblProgress.Caption = "Successful transfer"
End If

GoTo EndTransferRd

ErrorHandlerRd:
TransferCancelled = True
Resume EndTransferRd

EndTransferRd:
Close #1
If TransferCancelled = True Then
    DisplayCancelMessage
End If
InitializeToIdleCondition
End Sub

Private Sub tmrTimedOut_Timer()
TimedOut = True
lblProgress.Caption = "Remote system not responding"
tmrTimedOut.Enabled = False
End Sub

Private Sub tmrWatchForIncomingFile_Timer()
'When not sending a file, poll Status bit 6.
'If S6=0, the opposite end is sending a file.
StatusPortData = StatusPortRead(BaseAddress)
S6 = BitRead(StatusPortData, 6)
If S6 = 0 Then ReadFileFromPort
End Sub

Private Sub WriteByteToPort(ByteToWrite%)
'Write a byte to the data port, in 2 nibbles.
'The remote system reads the data at its status port.
'The data bits are D0, D1, D2, and D4.
'D3 is the strobe.
DivideByteIntoNibbles (ByteToWrite)
tmrTimedOut.Enabled = True
'When S6=1 (not busy), write the low nibble and set D3=0.
Do
    StatusPortData = StatusPortRead(BaseAddress)
    S6 = BitRead(StatusPortData, 6)
    DoEvents
Loop Until (S6 = 1) Or TimedOut
DataPortWrite BaseAddress, LowNibble
'When the peripheral responds by setting S6=0, set D3=1.
Do
    StatusPortData = StatusPortRead(BaseAddress)
    S6 = BitRead(StatusPortData, 6)
    DoEvents
Loop Until (S6 = 0) Or TimedOut
DataPortWrite BaseAddress, LowNibble + 8
'When S6=1, write the high nibble and set D3=0.
Do
    StatusPortData = StatusPortRead(BaseAddress)
    S6 = BitRead(StatusPortData, 6)
    DoEvents
Loop Until (S6 = 1) Or TimedOut
DataPortWrite BaseAddress, HighNibble
'When the peripheral responds by setting S6=0, set D3=1.
Do
    StatusPortData = StatusPortRead(BaseAddress)
    S6 = BitRead(StatusPortData, 6)
    DoEvents
Loop Until (S6 = 0) Or TimedOut
DataPortWrite BaseAddress, HighNibble + 8
tmrTimedOut.Enabled = False
End Sub

