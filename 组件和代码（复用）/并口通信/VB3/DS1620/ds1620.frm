VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Complete"
   ClientHeight    =   4584
   ClientLeft      =   168
   ClientTop       =   4116
   ClientWidth     =   4680
   ForeColor       =   &H00C0C0C0&
   Height          =   5244
   Left            =   120
   LinkTopic       =   "Form1"
   ScaleHeight     =   4584
   ScaleWidth      =   4680
   Top             =   3504
   Width           =   4776
   Begin CommandButton cmdClearHistory 
      Caption         =   "Clear History"
      Height          =   492
      Left            =   2520
      TabIndex        =   23
      Top             =   1440
      Width           =   1812
   End
   Begin CommandButton cmdApplySettings 
      Caption         =   "Apply Settings"
      Height          =   492
      Left            =   2520
      TabIndex        =   22
      Top             =   2640
      Width           =   1812
   End
   Begin Timer tmrWatchForAlarms 
      Enabled         =   0   'False
      Interval        =   1000
      Left            =   3720
      Top             =   3960
   End
   Begin Timer tmrReset 
      Enabled         =   0   'False
      Interval        =   500
      Left            =   3720
      Top             =   3480
   End
   Begin Frame fraAlarmTemperatures 
      Caption         =   "Alarm Temperatures"
      Height          =   1212
      Left            =   2400
      TabIndex        =   3
      Top             =   3240
      Width           =   2052
      Begin Timer tmrWaitForConversion 
         Enabled         =   0   'False
         Interval        =   1000
         Left            =   1680
         Top             =   240
      End
      Begin TextBox txtHighAlarmTemperature 
         Height          =   288
         Left            =   840
         TabIndex        =   8
         Text            =   "72"
         Top             =   720
         Width           =   372
      End
      Begin TextBox txtLowAlarmTemperature 
         Height          =   288
         Left            =   840
         TabIndex        =   9
         Text            =   "68"
         Top             =   360
         Width           =   372
      End
      Begin Label lblHighAlarmTemperature 
         Caption         =   "High"
         Height          =   252
         Left            =   120
         TabIndex        =   10
         Top             =   720
         Width           =   612
      End
      Begin Label lblLowAlarmTemperature 
         Caption         =   "Low"
         Height          =   252
         Left            =   120
         TabIndex        =   11
         Top             =   360
         Width           =   612
      End
   End
   Begin Frame fraInterface 
      Caption         =   "Interface"
      Height          =   852
      Left            =   240
      TabIndex        =   18
      Top             =   3600
      Width           =   1932
      Begin OptionButton optInterface 
         Caption         =   "Standalone"
         Height          =   252
         Index           =   1
         Left            =   240
         TabIndex        =   20
         Top             =   480
         Width           =   1332
      End
      Begin OptionButton optInterface 
         Caption         =   "CPU"
         Height          =   252
         Index           =   0
         Left            =   240
         TabIndex        =   19
         Top             =   240
         Width           =   1332
      End
   End
   Begin Frame fraMode 
      Caption         =   "Mode"
      Height          =   852
      Left            =   240
      TabIndex        =   15
      Top             =   2640
      Width           =   1932
      Begin OptionButton optMode 
         Caption         =   "1-shot"
         Height          =   252
         Index           =   1
         Left            =   240
         TabIndex        =   17
         Top             =   480
         Width           =   1212
      End
      Begin OptionButton optMode 
         Caption         =   "Continuous"
         Height          =   252
         Index           =   0
         Left            =   240
         TabIndex        =   16
         Top             =   240
         Width           =   1212
      End
   End
   Begin Frame fraAlarmHistory 
      Caption         =   "Alarm History"
      Height          =   852
      Left            =   240
      TabIndex        =   12
      Top             =   1680
      Width           =   1932
      Begin Label lblLowFlag 
         Caption         =   "Low"
         Height          =   252
         Left            =   240
         TabIndex        =   14
         Top             =   240
         Width           =   972
      End
      Begin Label lblHighFlag 
         Caption         =   "High"
         Height          =   252
         Left            =   240
         TabIndex        =   13
         Top             =   480
         Width           =   852
      End
   End
   Begin Frame fraCurrentConditions 
      Caption         =   "Current Conditions"
      Height          =   1332
      Left            =   240
      TabIndex        =   4
      Top             =   240
      Width           =   1932
      Begin Label lblCurrentTemperature 
         Height          =   252
         Left            =   240
         TabIndex        =   21
         Top             =   240
         Width           =   1572
      End
      Begin Label lblCombination 
         Caption         =   "Combination"
         Enabled         =   0   'False
         Height          =   252
         Left            =   240
         TabIndex        =   7
         Top             =   960
         Width           =   1092
      End
      Begin Label lblLow 
         Caption         =   "Low"
         Enabled         =   0   'False
         Height          =   252
         Left            =   240
         TabIndex        =   6
         Top             =   720
         Width           =   1212
      End
      Begin Label lblHigh 
         Caption         =   "High"
         Enabled         =   0   'False
         Height          =   252
         Left            =   240
         TabIndex        =   5
         Top             =   480
         Width           =   1212
      End
   End
   Begin CommandButton cmdReadConfiguration 
      Caption         =   "Read Configuration"
      Height          =   492
      Left            =   2520
      TabIndex        =   2
      Top             =   2040
      Width           =   1812
   End
   Begin CommandButton cmdStopConvert 
      Caption         =   "Stop Convert"
      Height          =   492
      Left            =   2520
      TabIndex        =   1
      Top             =   840
      Width           =   1812
   End
   Begin CommandButton cmdStartConvert 
      Caption         =   "Start Convert"
      Height          =   492
      Left            =   2520
      TabIndex        =   0
      Top             =   240
      Width           =   1812
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
'DS1620 signals:
'Inputs connect to Control port outputs:
Const DataIO = 1: 'bit 0 (this bit is I/O)
Const Clock = 2: 'bit 1"
Const ResetOff = 4: 'bit 2
Const ReadDirection = 8: 'bit 3
'Outputs connect to Status port inputs:
Const HighTrigger = 8:  'bit 3
Const LowTrigger = &H10: 'bit 4
Const CombinationTrigger = &H20: 'bit 5
Dim ModeSelect%
Dim InterfaceSelect%
Dim ConfigurationData%
Dim StopConvert%

Sub cmdApplySettings_Click ()
'Write user changes to the DS1620.
Dim Temperature%
If txtHighAlarmTemperature.Text <> "" Then
    Temperature = ConvertToChipFormat(CInt(txtHighAlarmTemperature.Text))
    WriteInstruction (1)
    WriteData Temperature
End If
If txtLowAlarmTemperature.Text <> "" Then
    Temperature = ConvertToChipFormat(CInt(txtLowAlarmTemperature.Text))
    WriteInstruction (2)
    WriteData Temperature
End If
'Read the configuration register,
'set or clear the interface and mode-select bits,
'and write the values back.
ConfigurationData = ReadConfiguration()
If optMode(0).Value = True Then
    ModeSelect = 0
Else
    ModeSelect = 1
End If
If optInterface(0).Value = True Then
    InterfaceSelect = 0
Else
    InterfaceSelect = 1
End If
WriteConfiguration ((ConfigurationData And &HFC) Or (ModeSelect + InterfaceSelect * 2))
End Sub

Sub cmdClearHistory_Click ()
Dim Configuration%
'To clear the alarm history,
'write 0 to bits 5 & 6 of configuration register.
Configuration = ReadConfiguration() And &H9F
WriteConfiguration (Configuration)
ReadChip
End Sub

Sub cmdReadConfiguration_Click ()
ReadChip
UpdateUserControls
End Sub

Sub cmdStartConvert_Click ()
Dim Temperature%
WriteInstruction (&HEE)
WaitForConversion
WriteInstruction (&HAA)
Temperature = ReadData()
lblCurrentTemperature.Caption = CSng(ConvertFromChipFormat(Temperature)) & " degrees C"
StopConvert = False
End Sub

Sub cmdStopConvert_Click ()
WriteInstruction (&H22)
StopConvert = True
End Sub

Function ConvertFromChipFormat! (ValueToConvert%)
'Temperature values read from the chip use 2's complement for negative
'numbers. LSB (bit 0) = 2^-1, or 0.5.
'Bits 0-7 indicate temperature, bit 8 = 1 for negative values.
'This function converts the integer read from the chip
'to a positive or negative floating-point value.
'For negative values, get the temperature value from the 2's complement
'& clear bit 8.
If (ValueToConvert And &H100) = &H100 Then
    ValueToConvert = (ValueToConvert - 1) Xor &H1FF
    ValueToConvert = -(ValueToConvert And &HFF)
End If
'Divide by 2
ConvertFromChipFormat = CSng(ValueToConvert) / 2
End Function

Function ConvertToChipFormat% (ValueToConvert!)
'Converts a floating-point temperature to the format
'required by the DS1620.
ValueToConvert = ValueToConvert * 2
'If negative, put in 2's complement format.
If ValueToConvert < 0 Then
    ValueToConvert = (Abs(ValueToConvert) Xor &H1FF) + 1
End If
ConvertToChipFormat = CSng(ValueToConvert)
End Function

Sub Form_Load ()
StartUp
tmrReset.Enabled = False
tmrReset.Interval = 5
tmrWatchForAlarms.Enabled = True
tmrWatchForAlarms.Interval = 1000
tmrWaitForConversion.Enabled = False
tmrWaitForConversion.Interval = 1000
lblHigh.Enabled = False
lblLow.Enabled = False
lblCombination.Enabled = False
lblHighFlag.Enabled = False
lblLowFlag.Enabled = False
StopConvert = False
'Initialize control bits.
ControlPortWrite BaseAddress, &HE
ResetChip
ReadChip
UpdateUserControls
End Sub

Sub Form_Unload (Cancel%)
ShutDown
End
End Sub

Sub mnuPort_Click (index%)
frmSelectPort.Show
End Sub

Sub optInterface_Click (index As Integer)
InterfaceSelect = index
End Sub

Sub optMode_Click (index As Integer)
ModeSelect = index
End Sub

Sub ReadChip ()
'Reads the configuration register & alarms
'& displays the results.
Dim Flag%
Dim Temperature%
Dim Alarms%
Dim Alarm%
ConfigurationData = ReadConfiguration()
'Alarm flags (past alarms)
Flag = BitRead(ConfigurationData, 5)
If Flag = 1 Then
    lblLowFlag.Enabled = True
Else
    lblLowFlag.Enabled = False
End If
Flag = BitRead(ConfigurationData, 6)
If Flag = 1 Then
    lblHighFlag.Enabled = True
Else
    lblHighFlag.Enabled = False
End If
'Alarm inputs (current alarms)
Alarms = StatusPortRead(BaseAddress)
Alarm = BitRead(Alarms, 3)
If Alarm = 1 Then
    lblHigh.Enabled = True
Else
    lblHigh.Enabled = False
End If
Alarm = BitRead(Alarms, 4)
If Alarm = 1 Then
    lblLow.Enabled = True
Else
    lblLow.Enabled = False
End If
Alarm = BitRead(Alarms, 5)
If Alarm = 1 Then
    lblCombination.Enabled = True
Else
    lblCombination.Enabled = False
End If
'Read these, but update only when
'UpdateUserControls is called.
ModeSelect = BitRead(ConfigurationData, 0)
InterfaceSelect = BitRead(ConfigurationData, 1)
End Sub

Function ReadConfiguration ()
WriteInstruction (&HAC)
ReadConfiguration = ReadData()
End Function

Function ReadData% ()
Dim BitValue%
Dim DataIn%
Dim BitIn%
DataIn = 0
'Set the transceiver direction to allow reading DataIO.
'Write 1 to Control bit 0 to allow its use as an input.
ControlPortWrite BaseAddress, Clock + DataIO + ResetOff + ReadDirection
For BitValue = 0 To 8
    'When Clock=0, DS1620 outputs data on DataIO.
    ControlPortWrite BaseAddress, ReadDirection + DataIO + ResetOff
    'Read DataIO and add its value to ReadData
    BitIn = BitRead(ControlPortRead(BaseAddress), 0)
    DataIn = DataIn + BitIn * 2 ^ BitValue
    'Clock=1
    ControlPortWrite BaseAddress, Clock + ReadDirection + DataIO + ResetOff
Next BitValue
'Set ReadDirection=0 to switch transceiver back.
ControlPortWrite BaseAddress, Clock + DataIO + ResetOff
DataIn = DataIn And &H1FF
ReadData = DataIn
End Function

Sub ResetChip ()
'toggle Reset before each write
ControlPortWrite BaseAddress, Clock + DataIO
'wait at least 5 milliseconds
tmrReset.Enabled = True
Do
    DoEvents
Loop Until tmrReset.Enabled = False
ControlPortWrite BaseAddress, Clock + ResetOff + DataIO
End Sub

Sub tmrReset_Timer ()
'Ensures a reset pulse of at least 5 milliseconds.
tmrReset.Enabled = False
End Sub

Sub tmrWaitForConversion_Timer ()
tmrWaitForConversion.Enabled = False
End Sub

Sub tmrWatchForAlarms_Timer ()
'Read the alarms.
'If continuous mode is selected, read a conversion.
If (optMode(0).Value = True) And (StopConvert = False) Then
    cmdStartConvert.Value = True
End If
ReadChip
End Sub

Sub UpdateUserControls ()
'Updates the option buttons and alarm settings
'with the values read from the configuration register.
'(Verifies that the values were stored correctly.)
Dim Temperature%
'Read TH
WriteInstruction (&HA1)
Temperature = ReadData()
txtHighAlarmTemperature.Text = CSng(ConvertFromChipFormat(Temperature))
'Read TL
WriteInstruction (&HA2)
Temperature = ReadData()
txtLowAlarmTemperature.Text = CSng(ConvertFromChipFormat(Temperature))
optMode(ModeSelect).Value = True
optInterface(InterfaceSelect).Value = True
End Sub

Sub WaitForConversion ()
tmrWaitForConversion.Enabled = True
Do
    DoEvents
Loop Until tmrWaitForConversion.Enabled = False
End Sub

Sub WriteConfiguration (ConfigurationData%)
WriteInstruction (&HC)
WriteData (ConfigurationData)
End Sub

Sub WriteData (DataToWrite%)
'Writes data to the DS1620 after a write instruction
'Chip ignores bit 8 if unneeded
Dim BitNumber%
Dim BitValue%
For BitNumber = 0 To 8
    BitValue = BitRead(DataToWrite, BitNumber)
    'Clock=0
    ControlPortWrite BaseAddress, ResetOff
    'Set or clear DataIO to match the bit value.
    ControlPortWrite BaseAddress, BitValue + ResetOff
    'Clock=1
    ControlPortWrite BaseAddress, BitValue + Clock + ResetOff
Next BitNumber
End Sub

Sub WriteInstruction (Instruction%)
Dim BitNumber%
Dim BitValue%
'Toggle Reset before each write.
ResetChip
ControlPortWrite BaseAddress, Clock + ResetOff
For BitNumber = 0 To 7
    BitValue = BitRead(Instruction, BitNumber)
    'Clock=0
    ControlPortWrite BaseAddress, ResetOff
    'Set or clear DataIO to match the bit value
    ControlPortWrite BaseAddress, ResetOff + BitValue
    'Clock=1
    ControlPortWrite BaseAddress, Clock + ResetOff + BitValue
Next BitNumber
End Sub

