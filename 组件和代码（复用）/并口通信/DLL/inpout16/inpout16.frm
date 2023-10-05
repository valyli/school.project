VERSION 2.00
Begin Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   1704
   ClientLeft      =   1848
   ClientTop       =   1932
   ClientWidth     =   2520
   Height          =   2088
   Left            =   1800
   LinkTopic       =   "Form1"
   ScaleHeight     =   1704
   ScaleWidth      =   2520
   Top             =   1596
   Width           =   2616
   Begin TextBox Text1 
      Height          =   372
      Left            =   240
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   1080
      Width           =   1812
   End
   Begin CommandButton Command1 
      Caption         =   "Write to Port"
      Height          =   852
      Left            =   360
      TabIndex        =   0
      Top             =   120
      Width           =   1692
   End
End
Option Explicit
Dim Value As Integer
Dim PortAddress As Integer

Private Sub Command1_Click ()
'Write to the port.
Out PortAddress, Value
'Read back and display the result.
Text1.Text = Inp(PortAddress)
Value = Value + 1
If Value = 255 Then Value = 0
End Sub

Private Sub Form_Load ()
'Test program for inpout16.dll
Value = 0
'Change PortAddress to match the port address to write to:
'(Usual parallel-port addresses are &h378, &h278, &h3BC)
PortAddress = &H378
End Sub

