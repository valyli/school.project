Parallel Port Complete
by Jan Axelson

published by
Lakeview Research
2209 Winnebago St.
Madison, WI 53704
Phone: 608-241-5824
Fax: 608-241-5848
Email: jaxelson@lvr.com
WWW: http://www.lvr.com

This file describes the contents of the program disk that accompanies the book Parallel Port Complete. There are two versions of this file: readme.rtf is in Rich Text format, and readme.txt is plain ASCII text. They contain identical information.

About the Disk

The disk has four main directories:
\DLL contains DLLs for adding add Inp and Out routines for direct port access in Visual Basic.
\VB3 contains Visual Basic 3 (VB3) versions of the projects described in the book.
\VB4 contains Visual Basic 4 (VB4) versions of the projects described in the book. These projects will load and run under 16-bit and 32-bit Visual Basic 4.
\Basic52 contains program code for the peripheral circuits in Chapters 13 through 15.
The sections that follow describe the contents of each directory and how to use them.

Rules for Use

All of the files on this disk are provided for your use. You may use any or all portions of the files in your programs and distribute such programs without payment of royalties, if you agree to the following disclaimer:
The information, computer programs, documentation, and other material on this disk are provided "as is," without warranty of any kind, expressed or implied, including without limitation any warranty concerning the accuracy, adequacy, or completeness of the material or the results obtained from using the material. Neither the publisher nor the author shall be responsible for any claims attributable to errors, omissions, or other inaccuracies in the material on this disk. In no event shall the publisher or author be liable for direct, indirect, special, incidental, or consequential damages in connection with, or arising out of, the construction, performance, or other use of the materials contained herein.

Questions Problems, or Suggestions

If you have any questions, problems, or suggestions relating to the files on this disk or the material in the book, the best way to reach me is by email at jaxelson@lvr.com.

Copying the Files

For faster and more convenient access, you may copy the files on the floppy to a hard disk. The simplest way to do this is to copy the entire disk, including the subdirectories, to any subdirectory (folder) on your hard disk.

Windows 3.1 example

To copy the contents of the disk from drive A to directory \ppc on drive C:
1. In the File Manager, double click to open both Hard Drive C and Floppy Drive A.
2. To create the directory \ppc on Drive C, select the c:\ window, then in the File menu select Create Directory, and type ppc.
3. In the Drive A window, select a:\ and use the mouse to drag the contents of Drive A to the \ppc directory on Drive C.

Windows 95 example

To copy the contents of the disk from drive A to directory \ppc on drive C:
1. Click on My Computer and click to open Hard Drive C and Floppy Drive A.
2. To create the directory \ppc on Drive C, click on File, New, Folder and type ppc.
3. On Drive A, click on Edit, Select All, and use the mouse to drag the contents of Drive A to the \ppc folder on Drive C.

About the DLLs

The \DLL directory has three subdirectories. Each contains a DLL that adds the ability to do port I/O in Visual Basic programs. Which to use depends on your program's abilities and requirements.

For VB3 and 16-bit VB4 programs:

\inpout16 contains files related to inpout16.dll, which contains Inp and Out for port access in VB3 programs and 16-bit VB4 programs.
inpout16.dll is the DLL.
inpoutv3.bas has declarations for Inp and Out.
inpout16.txt explains how to use the DLL.
inpout16.bas is the source code for the DLL, which was created with PowerBasic's DLL compiler.

For 32-bit VB4 programs:

\inpout32 contains files related to inpout32.dll, which contains Inp and Out for port access in 32-bit VB4 programs.
inpout32.dll is the DLL.
inpout32.bas has declarations for Inp and Out.
inpoutv4.bas has declarations for Inp and Out in both inpout16 and inpout32. Use this when you want to use one file for 32-bit and 16-bit VB4 programs.
inpout32.txt explains how to use the DLL.
inpout32.bas is the source code for the DLL, which was created with Borland's Delphi 2.0 object Pascal compiler.

Another option for VB3 and 16-bit VB4 programs:

\vbasm contains files related to vbasm.dll, which includes routines for port I/O (VbInp, VbOut) as well as software interrupts (Call VbInterrupt), and direct memory access (VbPoke, VbPeek). Vbasm is for use only with 16-bit programs. Because of the differences between Windows 3.1 and Win 32, there is no equivalent for 32-bit programs.
vbasm.dll is the DLL.
vbasm.txt is declarations for the routines in vbasm.dll.
vbasm.wri explains how to use the DLL.

About the Projects

Each subdirectory in \VB3 and \VB4 contains a project that you may load into Visual Basic's programming environment. From there, you may run the programs, modify them, create .exe files, or use the code in any way you wish.
Each project was originally created in VB3. The VB4 projects are identical, except for these differences:
They use inpoutv4.bas in place of inpoutv3.bas.
The API declarations in lpttempl.bas use conditional compiling to allow 16-bit or 32-bit API calls.
The project files are .vbp format rather than .mak format.
Other file changes are made automatically when a VB3 project is saved in VB4.

The Project Files

Each project's .mak (VB3) or .vbp (VB4) file lists the files used by the project. The project's subdirectory contains the project's startup form and any other files unique to that project. Each project also uses five files in the \lpttempl subdirectory.
For example, these are the files listed in the outexpnd project's .mak file:
OUTEXPND.FRM
..\LPTTEMPL\LPTUTIL.BAS
..\LPTTEMPL\INPOUTV3.BAS
..\LPTTEMPL\LPTTEMPL.BAS
..\LPTTEMPL\NEWPORT.FRM
..\LPTTEMPL\PORTSEL.FRM
This file specification:
..\LPTTEMPL\LPTUTIL.BAS
means that the .mak or .vbp file expects to find the \lpttempl subdirectory at the same level in the directory tree as the project's subdirectory.
If you load the projects from the floppy, or if you copy the floppy to hard disk as described above, all project files will be in the expected locations. If a file is in a different location from that specified in the .mak or .vbp file, you may use Add File to load the file. Use Save Project to save any new file locations in the .mak or .vbp file. Another option is to use a text editor to change the file locations in the .mak or .vbp file.

Using the inpout DLLs

In each project, Declare statements in inpoutv3.bas or inpoutv4.bas name one or more DLLs that contain routines called by the program.
The VB3 projects use inpoutv3.bas, which declares Inp and Out in inpout16.dll (in the \DLL\inpout16 subdirectory). The VB4 projects use inpoutv4.bas, which includes declarations for Inp and Out in both inpout16.dll and inpout32.dll (in the \DLL\inpout32 subdirectory).
To use inpout16.dll and inpout32.dll, copy them to one of these locations:
The Windows directory (usually \Windows)
The Windows system directory (usually \Windows\system)
The application's working directory. (In Visual Basic's programming environment, this is the Visual Basic directory.)
Or, if you want to store the DLL in a different directory, add the path to the filename in each declaration.
Each DLL's .txt file has further instructions for using the DLL.

The Project Directories

Each project corresponds to an application described in the book. Each project has its own subdirectory in \VB3 and \VB4.

VB3

All VB3 projects also use the following files in \VB3\lpttempl\:
inpoutv3.bas, declarations for Inp and Out.
lpttempl.bas, general-purpose routines used by all startup forms.
lptutil.bas, general-purpose parallel-port routines.
newport.frm, add a new port.
portsel.frm, select and test ports.

VB4

All VB4 projects also use the following files in \VB4\lpttempl\:
inpoutv4.bas, declarations for Inp and Out.
lpttempl.bas, general-purpose routines used by all startup forms.
lptutil.bas, general-purpose parallel-port routines.
newport.frm, add a new port.
portsel.frm, select and test ports.

Project Directories Arranged Alphabetically

\Adc0809, read an analog-to-digital converter, Chapter 8
\cnbnegot, compatibility, nibble, and byte-mode transfer, with negotiating, Chapter 13
\compbyte, compatibility and byte-mode transfer, Chapter 13
\compnibb, compatibility and nibble-mode transfer, Chapter 13
\Ds1620, link to a DS1620 temperature chip (synchronous serial interface), Chapter 9
\ecp, ECP-mode transfer, Chapter 15
\epp, EPP-mode transfer, Chapter 14
\inpexpnd, input expansion, Chapter 8
\latch8s, 8 latched inputs, using the Status bits, Chapter 8
\latch8sc, 8 latched inputs, using Status and Control bits, Chapter 8
\lpttempl, general-purpose template for parallel-port programs, Chapter 4
\lpttest, toggle and view parallel-port bits, Chapter 5
\outexpnd, output expansion, Chapter 7
\pcpcnibb, PC-to-PC nibble-mode transfer, Chapter 16
\polff, polled inputs, Chapter 10
\timeoday, trigger events on time of day, Chapter 10
\timrctrl, trigger periodic events, Chapter 10
\xpoint, control a crosspoint switch, Chapter 7

Project Directories Arranged by Chapter Number

\lpttempl, general-purpose template for parallel-port programs, Chapter 4
\lpttest, toggle and view parallel-port bits, Chapter 5
\outexpnd, output expansion, Chapter 7
\xpoint, control a crosspoint switch, Chapter 7
\Adc0809, read an analog-to-digital converter, Chapter 8
\inpexpnd, input expansion, Chapter 8
\latch8s, 8 latched inputs, using the Status bits, Chapter 8
\latch8sc, 8 latched inputs, using Status and Control bits, Chapter 8
\Ds1620, link to a DS1620 temperature chip (synchronous serial interface), Chapter 9
\polff, polled inputs, Chapter 10
\timeoday, trigger events on time of day, Chapter 10
\timrctrl, trigger periodic events, Chapter 10
\cnbnegot, compatibility, nibble, and byte-mode transfer, with negotiating, Chapter 13
\compbyte, compatibility and byte-mode transfer, Chapter 13
\compnibb, compatibility and nibble-mode transfer, Chapter 13
\epp, EPP-mode transfer, Chapter 14
\ecp, ECP-mode transfer, Chapter 15
\pcpcnibb, PC-to-PC nibble-mode transfer, Chapter 16

About the Basic-52 programs

The \Basic52 directory contains program code for the peripheral circuits in the projects in Chapters 13 through 15. These programs are written for the 8052-Basic microcontroller's Basic-52 interpreter, using the circuit shown in Appendix B in the book.
The programs are intended as a very basic demonstration of PC-to-peripheral transfers using the different modes. Peripheral devices are unique, and most will not use an 8052-Basic microcontroller. However, you may use the concepts in these programs as the basis for other peripheral circuits.
The syntax of the Basic-52 language is similar in many ways to other Basics. One nonstandard keyword used in the programs is XBY, used for reading and writing to external memory.
This statement writes the byte AAh (&hAA in Visual Basic) to FC00h in external memory:
  XBY(0FC00H)=0AAH
This statement stores the byte at FC02h in external memory in variable A:
  A=XBY(0FC02H)

Basic-52 Programs

These are the files in the \Basic52 directory:
B52cbyt.bas, compatibility and byte-mode transfer, Chapter 13
B52cnbn.bas, compatibility, nibble, and byte-mode transfer with negotiating, Chapter 13
B52cnib.bas, compatibility and nibble-mode transfer, Chapter 13
B52ecp.bas, ECP-mode transfer, Chapter 15
B52epp.bas, EPP-mode transfer, Chapter 14






