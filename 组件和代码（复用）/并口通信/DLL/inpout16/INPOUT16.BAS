'Source code for inpout16.dll.
'Enables Visual Basic 3 and 16-bit Visual Basic 4
'programs to do direct port I/O (Inp and Out).
'To be compiled with PowerBasic's DLL compiler v1.1

$COMPILE DLL

SUB Out16(BYVAL PortAddress AS INTEGER, BYVAL Value AS INTEGER) EXPORT
Out PortAddress%, Value%
END SUB

Function Inp16(BYVAL PortAddress AS INTEGER) EXPORT AS INTEGER
Function = Inp(PortAddress%)
END Function
