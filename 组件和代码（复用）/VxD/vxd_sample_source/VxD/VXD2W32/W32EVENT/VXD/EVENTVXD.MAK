CFLAGS     = -DWIN32 -DCON -Di386 -D_X86_ -D_NTWIN -W3 -Gs -D_DEBUG -Zi
CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG
LFLAGS     = -machine:i386 -debug:notmapped,full -debugtype:cv -subsystem:console kernel32.lib 
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: eventvxd.vxd

eventvxd.obj: eventvxd.c
        cl $(CVXDFLAGS) -Fo$@ %s

eventddb.obj: eventddb.asm
        ml $(AFLAGS) -Fo$@ %s

eventvxd.vxd: eventddb.obj eventvxd.obj ..\..\..\wrappers\vxdcall.obj ..\..\..\wrappers\wrappers.clb eventvxd.def 
        echo >NUL @<<eventvxd.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:eventvxd.def -OUT:eventvxd.vxd -MAP:eventvxd.map
-VXD vxdwraps.clb wrappers.clb vxdcall.obj eventddb.obj eventvxd.obj 
<<
        link @eventvxd.crf
        mapsym eventvxd


