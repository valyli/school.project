Attribute VB_Name = "inpout"

'Visual Basic declarations for direct port I/O 
'with Inp and Out.

'For use in 16-bit and 32-bit Visual Basic 4 programs.
'In a 32-bit program, Win32 is True, and the program 
'uses the inpout32.dll. In a 16-bit program, Win32 is False, 
'and the program uses the inpout16.dll.

#If Win32 Then
'DLL procedure names are case-sensitive in VB4.
'Use Aliases so Inp and Out don't have to have matching case in VB.
Public Declare Function Inp Lib "inpout32.dll" _
Alias "Inp32" (ByVal PortAddress As Integer) As Integer
Public Declare Sub Out Lib "inpout32.dll" _
Alias "Out32" (ByVal PortAddress As Integer, ByVal Value As Integer)

#Else
Public Declare Function Inp Lib "inpout16.Dll" _
Alias "Inp16" (ByVal PortAddress As Integer) As Integer
Public Declare Sub Out Lib "inpout16.Dll" _
Alias "Out16" (ByVal PortAddress As Integer, ByVal Value As Integer)
#End If
