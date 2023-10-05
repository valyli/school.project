WIN32SDK_BINW16 = \win32sdk\binw16

all: skeleton.dll

!message
!message +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!message + To make the 16-bit skeleton.dll, you will need to have the  +
!message + Microsoft Thunk compiler and the Microsoft Macro Assembler  +
!message + (ML) on the path.                                           +
!message +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!message

skeleton.obj: skeleton.c skeleton.h
    cl -c -W3 -ASw -GD2s -Oi $*.c 

skeleton.asm: skeleton.thk
    thunk -t SKELETON -o skeleton.asm skeleton.thk

thk16.obj: skeleton.asm
    ml /DIS_16 /c /W3 /Fo thk16.obj skeleton.asm


skeleton.dll: skeleton.def skeleton.obj thk16.obj
    link skeleton+thk16,skeleton.dll,skeleton.map /MAP,sdllcew libw /nod/noe,skeleton.def
    $(WIN32SDK_BINW16)\rc -40 skeleton.dll
    mapsym skeleton
    implib skeleton.lib skeleton.dll
    copy skeleton.dll \windows\skeleton.dll

