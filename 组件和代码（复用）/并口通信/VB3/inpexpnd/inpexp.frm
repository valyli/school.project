VERSION 2.00
Begin Form frmMain 
   Caption         =   "Parallel Port Resource"
   ClientHeight    =   2160
   ClientLeft      =   756
   ClientTop       =   1632
   ClientWidth     =   3144
   ForeColor       =   &H00C0C0C0&
   Height          =   2820
   Left            =   708
   LinkTopic       =   "Form1"
   ScaleHeight     =   2160
   ScaleWidth      =   3144
   Top             =   1020
   Width           =   3240
   Begin CommandButton cmdReadBytes 
      Caption         =   "Read Bytes"
      Height          =   612
      Left            =   1680
      TabIndex        =   6
      Top             =   360
      Width           =   1212
   End
   Begin Frame fraInputBytes 
      Caption         =   "Input Bytes"
      Height          =   1692
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1212
      Begin Label lblByteIn 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   4
         Left            =   240
         TabIndex        =   5
         Top             =   1200
         Width           =   492
      End
      Begin Label lblByteIn 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   3
         Left            =   240
         TabIndex        =   4
         Top             =   960
         Width           =   492
      End
      Begin Label lblByteIn 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   2
         Left            =   240
         TabIndex        =   3
         Top             =   720
         Width           =   492
      End
      Begin Label lblByteIn 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   1
         Left            =   240
         TabIndex        =   2
         Top             =   480
         Width           =   492
      End
      Begin Label lblByteIn 
         BorderStyle     =   1  'Fixed Single
         Height          =   252
         Index           =   0
         Left            =   240
         TabIndex        =   1
         Top             =   240
         Width           =   492
      End
   End
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
Dim DataIn%(0 To 7)
Dim DataByte%(0 To 4)

Sub cmdReadBytes_Click ()
Dim BitNumber%
'The control port selects a bit number to read.
'The status port holds the data to be read.
For BitNumber = 0 To 7
    ControlPortWrite BaseAddress, BitNumber
    DataIn(BitNumber) = StatusPortRead(BaseAddress)
Next BitNumber
GetBytesFromDataIn
DisplayResults
End Sub

Sub DisplayResults ()
Dim ByteNumber%
For ByteNumber = 0 To 4
lblByteIn(ByteNumber).Caption = Hex$(DataByte(ByteNumber)) & "h"
Next ByteNumber
End Sub

Sub Form_Load ()
StartUp
End Sub

Sub Form_Unload (Cancel%)
ShutDown

End Sub

Sub GetBytesFromDataIn ()
'Bits 3-7 of the 8 bytes contain data.
'To make 5 data bytes from these bits,
'each data byte contains one bit from each byte read.
'For example, data byte 0 contains 8 "bit 3s," one from each byte read.
Dim ByteNumber%
Dim BitNumber%
Dim BitToAdd%
For ByteNumber = 0 To 4
    DataByte(ByteNumber) = 0
    'BitRead gets the selected bit value (ByteNumber + 3)
    'from the selected byte read (DataIn(BitNumber)).
    'To get the bit value for the created data byte, multiply times 2^BitNumber.
    'Add each bit value to the created byte.
    For BitNumber = 0 To 7
        BitToAdd = (BitRead(DataIn(BitNumber), ByteNumber + 3)) * 2 ^ BitNumber
        DataByte(ByteNumber) = DataByte(ByteNumber) + BitToAdd
    Next BitNumber
Next ByteNumber
End Sub

Sub mnuPort_Click (index%)
frmSelectPort.Show
End Sub

