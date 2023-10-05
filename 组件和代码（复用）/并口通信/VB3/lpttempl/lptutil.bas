'Lptutil.bas
'General purpose routines for use with the PC's parallel port.
'Port accesses require a DLL with Inp and Out.
Option Explicit

Function DataPortRead% (BaseAddress%)
'Reads a parallel port's data port.
DataPortRead = Inp(BaseAddress)
End Function

Sub DataPortWrite (BaseAddress%, Value%)
'Writes a byte to a parallel port's data port.
Out BaseAddress, Value
End Sub

Function StatusPortRead% (BaseAddress%)
'Reads a parallel port's status port.
'Calculates the status-port address from the port's
'base address, and inverts bit 7 of the byte read.
'The status-port hardware reinverts these bits,
'so the value read matches the value at the connector.
StatusPortRead = (Inp(BaseAddress + 1) Xor &H80)
End Function

Function BitRead% (Variable%, BitNumber%)
'Returns the value (0 or 1) of the requested bit in a Variable.
Dim BitValue%
BitValue = 2 ^ BitNumber 'the value of the requested bit
BitRead = (Variable And BitValue) \ BitValue
End Function

Sub BitReset (Variable%, BitNumber%)
'Resets (clears) the requested bit in a Variable.
Dim BitValue, CurrentValue%
'The value of the requested bit.
BitValue = 2 ^ BitNumber
Variable = Variable And (&HFFFF - BitValue)
End Sub

Sub BitSet (Variable%, BitNumber%)
'Sets the requested bit in a Variable.
Dim BitValue, CurrentValue%
'The value of the requested bit.
BitValue = 2 ^ BitNumber
Variable = Variable Or BitValue
End Sub

Sub BitToggle (Variable%, BitNumber%)
'Toggles the requested bit in a Variable.
Dim BitValue, CurrentValue%
'The value of the requested bit.
BitValue = 2 ^ BitNumber
'Is the current value 0 or 1?
CurrentValue = Variable And BitValue
Select Case CurrentValue
    Case 0
        'If current value = 0, set it
        Variable = Variable Or BitValue
    Case Else
        'If current value = 1, reset it
        Variable = Variable And (&HFFFF - BitValue)
End Select
End Sub

Function ControlPortRead% (BaseAddress%)
'Reads a parallel port's control port.
'Calculates the control-port address from the port's
'base address, and inverts bits 0, 1, & 3 of the byte read.
'The control-port hardware reinverts these bits,
'so the value read matches the value at the connector.
ControlPortRead = (Inp(BaseAddress + 2) Xor &HB)
End Function

Sub ControlPortWrite (BaseAddress%, Value%)
'Writes a Value to a parallel port's control port.
'Calculates the control-port address from the port's
'base address, and inverts bits 0, 1, & 3.
'The control-port hardware reinverts these bits,
'so Value is written to the port connector.
Out BaseAddress + 2, Value Xor &HB
End Sub

