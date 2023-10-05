Option Explicit

Sub ReadPorts (BaseAddress As Integer)
'Read the data, status, and control ports of selected port.
'Display the byte read and each bit in the byte.
Dim ByteRead As Integer
Dim BitNumber As Integer
Dim BitValue As Integer

ByteRead = DataPortRead(BaseAddress)
frmMain.lblDataPortByte(0).Caption = Hex$(ByteRead) + "h"
For BitNumber = 0 To 7
    BitValue = BitRead(ByteRead, BitNumber)
    frmMain.lblDataBit(BitNumber).Caption = BitValue
Next BitNumber

ByteRead = StatusPortRead(BaseAddress)
frmMain.lblStatusPortByte(0).Caption = Hex$(ByteRead) + "h"
For BitNumber = 0 To 7
    BitValue = BitRead(ByteRead, BitNumber)
    frmMain.lblStatusBit(BitNumber).Caption = BitValue
Next BitNumber

ByteRead = ControlPortRead(BaseAddress)
frmMain.lblControlPortByte(0).Caption = Hex$(ByteRead) + "h"
For BitNumber = 0 To 7
    BitValue = BitRead(ByteRead, BitNumber)
    frmMain.lblControlBit(BitNumber).Caption = BitValue
Next BitNumber


End Sub

