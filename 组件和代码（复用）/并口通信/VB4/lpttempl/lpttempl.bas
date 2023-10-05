Attribute VB_Name = "LPTTEMPL1"
Option Explicit
#If Win32 Then
Declare Function GetPrivateProfileStringByKeyName& Lib "Kernel32" _
Alias "GetPrivateProfileStringA" _
(ByVal lpApplicationName$, ByVal lpszKey$, ByVal lpszDefault$, _
ByVal lpszReturnBuffer$, ByVal cchReturnBuffer&, ByVal lpszFile$)

Declare Function WritePrivateProfileString& Lib "Kernel32" _
Alias "WritePrivateProfileStringA" _
(ByVal lpApplicationName$, ByVal lpKeyName$, ByVal lpString$, ByVal lpFileName$)

Declare Function GetWindowsDirectory& Lib "Kernel32" _
Alias "GetWindowsDirectoryA" (ByVal lpBuffer$, ByVal nSize%)

#Else

Declare Function GetPrivateProfileStringByKeyName% Lib "Kernel" _
Alias "GetPrivateProfileString" _
(ByVal lpApplicationName$, ByVal lpKeyName$, ByVal lpDefault$, _
ByVal lpReturnedString$, ByVal nSize%, ByVal lpFileName$)

Declare Function WritePrivateProfileString% Lib "Kernel" _
(ByVal _
lpApplicationName$, ByVal lpKeyName$, ByVal lpString$, ByVal lpFileName$)

Declare Function GetWindowsDirectory% Lib "Kernel" (ByVal lpBuffer$, ByVal nSize%)

#End If

Type PortData
    Name As String
    Address As Integer
    PortType As String
    EcpModeDescription As String
    EcpModeValue As Integer
    Enabled As Integer
End Type
Global Port(0 To 3) As PortData
Global BaseAddress%
Global PortType$
Global IniFile$

Global EcrAddress%
Global EcrData%
Global EcpDataPortAddress%
Global EppDataPort0Address%
Global IndexOfSelectedPort%
Global PortDescription$

Global EcpExists%
Global SppExists%
Global PS2Exists%
Global EppExists%

Function GetEcpModeDescription$(EcpModeValue%)
Select Case EcpModeValue
    Case 0
        GetEcpModeDescription = "SPP"
    Case 1
        GetEcpModeDescription = "PS/2"
    Case 10
        GetEcpModeDescription = "Fast Centronics"
    Case 11
        GetEcpModeDescription = "ECP"
    Case 100
        GetEcpModeDescription = "EPP"
    Case 110
        GetEcpModeDescription = "Test"
    Case 111
        GetEcpModeDescription = "Configuration"
End Select
End Function

Sub GetIniData()
'Use the Windows API call GetPrivateProfileString to read user information
'from an ini file.

Dim NumberOfCharacters%
Dim ReturnBuffer As String * 128
Dim Index%
Dim WindowsDirectory$

'The API functions read data into fixed-length string buffers
'and return the number of characters in the entry.
'Use Left$ to discard all characters to the right of the final character in the entry.

'Get the path of the Windows directory, where the ini file is stored.
NumberOfCharacters = GetWindowsDirectory(ReturnBuffer, 127)
WindowsDirectory = Left$(ReturnBuffer, NumberOfCharacters)
IniFile = WindowsDirectory + "\lptprogs.ini"

'If the ini file doesn't exist, don't try to read it.
If Not Dir$(IniFile) = "" Then
    'The port addresses:
    Port(0).Address = CInt(VbGetPrivateProfileString("lptdata", "Port0Address", IniFile))
    Port(1).Address = CInt(VbGetPrivateProfileString("lptdata", "Port1Address", IniFile))
    Port(2).Address = CInt(VbGetPrivateProfileString("lptdata", "Port2Address", IniFile))
    Port(3).Address = CInt(VbGetPrivateProfileString("lptdata", "Port3Address", IniFile))
    
    'The port types:
    Port(0).PortType = VbGetPrivateProfileString("lptdata", "Port0Type", IniFile)
    Port(1).PortType = VbGetPrivateProfileString("lptdata", "Port1Type", IniFile)
    Port(2).PortType = VbGetPrivateProfileString("lptdata", "Port2Type", IniFile)
    Port(3).PortType = VbGetPrivateProfileString("lptdata", "Port3Type", IniFile)
    
    'Port enabled?
    Port(0).Enabled = CInt(VbGetPrivateProfileString("lptdata", "Port0Enabled", IniFile))
    Port(1).Enabled = CInt(VbGetPrivateProfileString("lptdata", "Port1Enabled", IniFile))
    Port(2).Enabled = CInt(VbGetPrivateProfileString("lptdata", "Port2Enabled", IniFile))
    Port(3).Enabled = CInt(VbGetPrivateProfileString("lptdata", "Port3Enabled", IniFile))
    
    'The selected port
    IndexOfSelectedPort = CInt(VbGetPrivateProfileString("lptdata", "IndexOfSelectedPort", IniFile))
End If
End Sub

Function ReadEcpMode%(TestAddress%)
'The Ecr mode is in bits 5, 6, and 7 of the ECR.
EcrAddress = TestAddress + &H402
EcrData = Inp(EcrAddress)
ReadEcpMode = (EcrData And &HE0) \ &H20
End Function

Function ReadEppTimeoutBit%(BaseAddress%)
'Reads and clears the EPP timeout bit (status port bit 0).
'Should be done after each EPP operation.
'The method for clearing the bit varies, so try 3 ways:
'1. Write 1 to it.
'2. Write 0 to it.
'3. Read it again.
Dim StatusPortAddress%
Dim ReadAgain%
StatusPortAddress = BaseAddress + 1
ReadEppTimeoutBit = BitRead(StatusPortRead(BaseAddress), 0)
Out StatusPortAddress, 1
Out StatusPortAddress, 0
ReadAgain = BitRead(StatusPortRead(BaseAddress), 0)
End Function

Sub SetEcpMode(EcpModeValue%)
'Store the Ecp mode's value and description in the Port array.
Port(IndexOfSelectedPort).EcpModeValue = EcpModeValue
Port(IndexOfSelectedPort).EcpModeDescription = GetEcpModeDescription(EcpModeValue)
EcrAddress = BaseAddress + &H402
'Read the ECR & clear bits 5, 6, 7.
EcrData = Inp(EcrAddress) And &H1F
'Write the selected value to bits 5, 6, 7.
EcrData = EcrData + EcpModeValue * &H20
Out EcrAddress, EcrData
End Sub

Sub ShutDown()
WriteIniData
End
End Sub

Sub StartUp()
Dim PortExists%
Dim Index%
'Get information from the ini file.
GetIniData

'Load the forms.
frmMain.Left = (Screen.Width - frmMain.Width) / 2
frmMain.Top = (Screen.Height - frmMain.Height) / 2
Load frmSelectPort
frmSelectPort.optPortName(IndexOfSelectedPort).Value = True
frmMain.Show
End Sub

Function TestForEcp%(TestAddress%)
'Test for the presence of an ECP.
'If the ECP is idle and the FIFO empty,
'in the ECP's Ecr (at Base Address+402h),
'bit 1(Fifo full)=0, and bit 0(Fifo empty)=1.
'The first test is to see if these bits differ from the
'corresponding bits in the control port (at Base Address+2).
'If so, a further test is to write 34h to the Ecr,
'then read it back. Bit 1 is read/write, and bit 0 is read-only.
'If the value read is 35h, the port is an ECP.
Dim EcrBit0%
Dim EcrBit1%
Dim ControlBit0%
Dim ControlBit1%
Dim ControlPortData%
Dim TestEcrAddress%
Dim OriginalEcrData%
TestForEcp = False
EcrAddress = TestAddress + &H402

'Read ECR bits 0 & 1 and Control Port bit 1.
EcrData = Inp(EcrAddress)
EcrBit0 = BitRead(EcrData, 0)
EcrBit1 = BitRead(EcrData, 1)
ControlPortData = ControlPortRead(TestAddress)
ControlBit1 = BitRead(ControlPortData, 1)
If EcrBit0 = 1 And EcrBit1 = 0 Then
    'Compare control bit 1 to ECR bit 1.
    'Toggle the control bit if necessary,
    'to be sure the two registers are different.
    If ControlBit1 = 0 Then
        ControlPortWrite TestAddress, &HF
        ControlPortData = ControlPortRead(TestAddress)
        ControlBit1 = BitRead(ControlPortData, 1)
    End If
    If EcrBit1 <> ControlBit1 Then
        OriginalEcrData = EcrData
        Out EcrAddress, &H34
        EcrData = Inp(EcrAddress)
        If EcrData = &H35 Then
            TestForEcp = True
        End If
        'Restore the ECR to its original value.
        Out EcrAddress, OriginalEcrData
    End If
End If
End Function

Function TestForEpp%(TestAddress%)
'Write to an Epp register, then read it back.
'If the reads match the writes, it's probably an Epp.
Dim ByteRead%
Dim StatusPortData%
Dim EppAddressPort%
Dim TimeoutBit%
Dim StatusPortAddress%
StatusPortAddress = TestAddress + 1
TestForEpp = False
'Use EppAddressPort for testing.
'SPPs, ECPs, and PS/2 ports don't have this register.
EppAddressPort = TestAddress + 3
Out EppAddressPort, &H55
'Clear the timeout bit after each EPP operation.
TimeoutBit = ReadEppTimeoutBit%(TestAddress%)
ByteRead = Inp(EppAddressPort)
TimeoutBit = ReadEppTimeoutBit%(TestAddress%)
If ByteRead = &H55 Then
    Out EppAddressPort, &HAA
    TimeoutBit = ReadEppTimeoutBit%(TestAddress%)
    ByteRead = Inp(EppAddressPort)
    TimeoutBit = ReadEppTimeoutBit%(TestAddress%)
    If ByteRead = &HAA Then
        TestForEpp = True
    End If
End If
End Function

Function TestForPS2%(TestAddress%)
'Tests a parallel port's data port for bidirectional ability.
'First, try to tri-state (disable) the data outputs by
'setting bit 5 of the Control port.
'Then write 2 values to the data port and read each back
'If the values match, the data outputs are not disabled,
'and the port is not bidirectional.
'If the values don't match,
'the data outputs are disabled and the port is bidirectional.
Dim DataInput%
Dim ControlPortData%
Dim OriginalControlPortData%
Dim OriginalDataPortData%

'Set Control port bit 5.
ControlPortWrite TestAddress, &H2F
TestForPS2 = False
'Write the first byte and read it back:
DataPortWrite TestAddress, &H55
DataInput = DataPortRead(TestAddress)
'If it doesn't match, the port is bidirectional.
If Not DataInput = &H55 Then TestForPS2 = True
'If it matches, write another and read it back.
If DataInput = &H55 Then
    DataPortWrite TestAddress, &HAA
    DataInput = DataPortRead(TestAddress)
    'If it doesn't match, the port is bidirectional
    If Not DataInput = &HAA Then
        TestForPS2 = True
    End If
End If
'Reset Control port bit 5
ControlPortWrite TestAddress, &HF
End Function

Function TestForSpp%(TestAddress%)
'Write two bytes and read them back.
'If the reads match the writes, the port exists.
Dim ByteRead%
'Be sure that control port bit 5 = 0 (data outputs enabled).
ControlPortWrite TestAddress, &HF
TestForSpp = False
DataPortWrite TestAddress, &H55
ByteRead = DataPortRead(TestAddress)
If ByteRead = &H55 Then
    DataPortWrite TestAddress, &HAA
    ByteRead = DataPortRead(TestAddress)
    If ByteRead = &HAA Then
        TestForSpp = True
    End If
End If
End Function

Function TestPort%(PortIndex%)
'Test for a port's presence, and if it exists, the type of port.
'In order, check for the presence of an ECP, EPP, SPP, and PS/2 port.
'Update the information in the Port array  and the display.
Dim EcpModeDescription$
Dim EcpModeValue%
Dim TestAddress%
TestPort = False
EcpExists = False
EppExists = False
SppExists = False
PS2Exists = False
PortType = ""
TestAddress = Port(PortIndex).Address
'Begin by hiding all port details.
frmSelectPort.lblAddress(PortIndex).Visible = False
frmSelectPort.lblType(PortIndex).Visible = False
frmSelectPort.cboEcpMode(PortIndex).Visible = False

EcpExists = TestForEcp(TestAddress)
If EcpExists Then
    PortType = "ECP"
    'Read the current Ecp mode.
    EcpModeValue = ReadEcpMode(TestAddress)
Else
    'If it's not an ECP, look for an EPP.
    'If TestAddress = 3BCh, skip the EPP test.
    'EPPs aren't allowed at 3BCh due to possible conflict
    'with video memory.
    frmSelectPort.cboEcpMode(PortIndex).Visible = False
    If TestAddress = &H3BC Then
        EppExists = False
    Else
        EppExists = TestForEpp(TestAddress)
    End If
    If EppExists Then
        PortType = "EPP"
    Else
        'If it's not an EPP, look for an SPP.
        SppExists = TestForSpp(TestAddress)
        If SppExists Then
            'Test for a PS/2 port only if the SPP exists
            '(because if the port doesn't exist, it will pass the PS/2 test!)
            PS2Exists = TestForPS2(TestAddress)
            If PS2Exists Then
                PortType = "PS/2"
            Else
                PortType = "SPP"
            End If
        Else
            PortType = ""
        End If

    End If
End If

If PortType = "" Then
   frmSelectPort.optPortName(PortIndex).Enabled = False
   Port(PortIndex).PortType = ""
   Port(PortIndex).Address = 0
   Port(PortIndex).Enabled = False
Else
    TestPort = True
    Port(PortIndex).Enabled = True
    Port(PortIndex).PortType = PortType
    Port(PortIndex).Enabled = True
    If EcpExists Then
        Port(PortIndex).EcpModeValue = EcpModeValue
        Port(PortIndex).EcpModeDescription = GetEcpModeDescription(EcpModeValue)
    End If
End If
UpdateLabels
End Function

Sub UpdateLabels()
'Use the information in the Port array to update the on-screen display.
Dim Index%
Dim EcpModeValue%
For Index = 0 To 3
    frmSelectPort.lblAddress(Index).Caption = Hex$(Port(Index).Address) + "h"
    If Port(Index).Enabled = True Then
        frmSelectPort.optPortName(Index).Enabled = True
        frmSelectPort.lblAddress(Index).Visible = True
        frmSelectPort.lblType(Index).Caption = Port(Index).PortType
        frmSelectPort.lblType(Index).Visible = True
        If Port(Index).PortType = "ECP" Then
            EcpModeValue = ReadEcpMode(Port(Index).Address)
            frmSelectPort.cboEcpMode(Index).ListIndex = EcpModeValue
            Port(Index).EcpModeValue = EcpModeValue
            Port(Index).EcpModeDescription = GetEcpModeDescription(EcpModeValue)
            frmSelectPort.cboEcpMode(Index).Visible = True
        Else
            frmSelectPort.cboEcpMode(Index).Visible = False
        End If
    Else
        frmSelectPort.optPortName(Index).Enabled = False
        frmSelectPort.lblAddress(Index).Visible = False
        frmSelectPort.lblType(Index).Visible = False
        frmSelectPort.cboEcpMode(Index).Visible = False
    
    End If
Next Index
End Sub

Function VbGetPrivateProfileString$(section$, key$, file$)
    Dim KeyValue$
    Dim Characters%
    KeyValue = String$(128, 0)
    Characters = GetPrivateProfileStringByKeyName(section, key, "", KeyValue, 127, file)
    KeyValue = Left$(KeyValue, Characters)
    VbGetPrivateProfileString = KeyValue
End Function

Sub WriteIniData()
Dim BaseAddressWrite%
Dim PortTypeWrite%
Dim Index%
Dim IniWrite%

'Use Windows API call WritePrivateProfileString to save initialization information.
'If the ini file doesn't exist, it will be created and stored in the Windows directory.

'The port addresses:
IniWrite = WritePrivateProfileString("lptdata", "Port0Address", CStr(Port(0).Address), IniFile)
IniWrite = WritePrivateProfileString("lptdata", "Port1Address", CStr(Port(1).Address), IniFile)
IniWrite = WritePrivateProfileString("lptdata", "Port2Address", CStr(Port(2).Address), IniFile)
IniWrite = WritePrivateProfileString("lptdata", "Port3Address", CStr(Port(3).Address), IniFile)

'The port types:
IniWrite = WritePrivateProfileString("lptdata", "Port0Type", Port(0).PortType, IniFile)
IniWrite = WritePrivateProfileString("lptdata", "Port1Type", Port(1).PortType, IniFile)
IniWrite = WritePrivateProfileString("lptdata", "Port2Type", Port(2).PortType, IniFile)
IniWrite = WritePrivateProfileString("lptdata", "Port3Type", Port(3).PortType, IniFile)

'Port enabled?
IniWrite = WritePrivateProfileString("lptdata", "Port0Enabled", CStr(Port(0).Enabled), IniFile)
IniWrite = WritePrivateProfileString("lptdata", "Port1Enabled", CStr(Port(1).Enabled), IniFile)
IniWrite = WritePrivateProfileString("lptdata", "Port2Enabled", CStr(Port(2).Enabled), IniFile)
IniWrite = WritePrivateProfileString("lptdata", "Port3Enabled", CStr(Port(3).Enabled), IniFile)

'Find the selected port and save it:
Index = 4
Do
    Index = Index - 1
Loop Until (frmSelectPort.optPortName(Index).Value = True) Or Index = 0
IniWrite = WritePrivateProfileString("lptdata", "IndexOfSelectedPort", CStr(Index), IniFile)

End Sub

