VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   1452
   ClientLeft      =   8268
   ClientTop       =   7248
   ClientWidth     =   3432
   ForeColor       =   &H00C0C0C0&
   Height          =   2112
   Left            =   8220
   LinkTopic       =   "Form1"
   ScaleHeight     =   1452
   ScaleWidth      =   3432
   Top             =   6636
   Width           =   3528
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

Sub Form_Load ()
StartUp
End Sub

Sub Form_Unload (Cancel%)
ShutDown
End
End Sub

Sub mnuPort_Click (Index%)
frmSelectPort.Show
End Sub

