'Visual Basic declarations for direct port I/O 
'with Inp and Out.
'For use in Visual Basic 3 programs and 
'16-bit Visual Basic 4 programs.

Declare Function Inp Lib "inpout16.Dll" Alias "Inp16" (ByVal PortAddress As Integer) As Integer
Declare Sub Out Lib "inpout16.Dll" Alias "Out16" (ByVal PortAddress As Integer, ByVal Value As Integer)
