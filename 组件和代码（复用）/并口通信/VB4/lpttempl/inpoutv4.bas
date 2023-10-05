Attribute VB_Name = "inpout"
'Declare Inp and Out for port I/O
'Two versions, for 16-bit and 32-bit Visual Basic 4 programs.

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


