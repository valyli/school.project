VERSION 2.00
Begin Form frmNewPortAddress 
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   1488
   ClientLeft      =   876
   ClientTop       =   1404
   ClientWidth     =   4092
   Height          =   1872
   Left            =   828
   LinkTopic       =   "Form1"
   ScaleHeight     =   1488
   ScaleWidth      =   4092
   Top             =   1068
   Width           =   4188
   Begin CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   492
      Left            =   1560
      TabIndex        =   4
      Top             =   840
      Width           =   852
   End
   Begin CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   492
      Left            =   2640
      TabIndex        =   3
      Top             =   840
      Width           =   852
   End
   Begin TextBox txtAddressOfNonStandardPort 
      Height          =   372
      Left            =   3000
      TabIndex        =   0
      Top             =   240
      Width           =   612
   End
   Begin Label lblh 
      Caption         =   "h"
      Height          =   372
      Left            =   3720
      TabIndex        =   2
      Top             =   240
      Width           =   252
   End
   Begin Label lblAddressOfNonStandardPort 
      Caption         =   "Address of nonstandard port:"
      Height          =   372
      Left            =   120
      TabIndex        =   1
      Top             =   240
      Width           =   2772
   End
End
Option Explicit

Sub cmdCancel_Click ()
frmNewPortAddress.Hide
End Sub

Sub cmdOK_Click ()
Dim NewPortAddress%
Dim IndexOfNewPort%
Dim Character$
Dim ValidEntry%
ValidEntry = True
IndexOfNewPort = 3
'Read the port address entered by the user.
'If the address is within the accepted range, hide this form,
'enable the port's option button, and display the address.
'If the address is out of range, display a message.
'If the text box is empty, disable the port's option button.
Select Case txtAddressOfNonStandardPort.Text
    Case ""
        NewPortAddress = 0
        port(IndexOfNewPort).Address = 0
        port(IndexOfNewPort).PortType = ""
        port(IndexOfNewPort).Enabled = False
        frmSelectPort.optPortName(0).Value = True
        frmNewPortAddress.Hide
        UpdateLabels
    Case Else
        NewPortAddress = CInt(Val("&h" & txtAddressOfNonStandardPort.Text))
        If NewPortAddress > 0 And NewPortAddress < &H800 Then
            port(IndexOfNewPort).Address = NewPortAddress
            port(IndexOfNewPort).Enabled = True
            frmSelectPort.optPortName(IndexOfNewPort).Value = True
            frmNewPortAddress.Hide
            UpdateLabels
        Else
            MsgBox "The port address must be between 0 and 7FFF. Leave the address blank if there is no port."
        End If
End Select
End Sub

Sub Form_Load ()
Left = (Screen.Width - Width) / 2
Top = (Screen.Height - Height) / 2
End Sub

