CFLAGS     = -DWIN32 -DCON -Di386 -D_X86_ -D_NTWIN -W3 -Gs -D_DEBUG -Zi
CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG
LFLAGS     = -machine:i386 -debug:notmapped,full -debugtype:cv -subsystem:console kernel32.lib 
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: apcvxd.vxd

apcvxd.obj: apcvxd.c
        cl $(CVXDFLAGS) -Fo$@ %s

apcddb.obj: apcddb.asm
        ml $(AFLAGS) -Fo$@ %s

apcvxd.vxd: apcddb.obj apcvxd.obj ..\..\..\wrappers\vxdcall.obj ..\..\..\wrappers\wrappers.clb apcvxd.def 
        echo >NUL @<<apcvxd.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:apcvxd.def -OUT:apcvxd.vxd -MAP:apcvxd.map
-VXD vxdwraps.clb wrappers.clb vxdcall.obj apcddb.obj apcvxd.obj 
<<
        link @apcvxd.crf
        mapsym apcvxd


