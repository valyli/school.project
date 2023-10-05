CFLAGS     = -DWIN32 -DCON -Di386 -D_X86_ -D_NTWIN -W3 -Gs -D_DEBUG -Zi
CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG
LFLAGS     = -machine:i386 -debug:notmapped,full -debugtype:cv -subsystem:console kernel32.lib 
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: postvxd.vxd

postvxd.obj: postvxd.c
        cl $(CVXDFLAGS) -Fo$@ %s

postddb.obj: postddb.asm
        ml $(AFLAGS) -Fo$@ %s

postvxd.vxd: postddb.obj postvxd.obj ..\..\wrappers\vxdcall.obj ..\..\wrappers\wrappers.clb postvxd.def 
        echo >NUL @<<postvxd.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:postvxd.def -OUT:postvxd.vxd -MAP:postvxd.map
-VXD vxdwraps.clb wrappers.clb vxdcall.obj postddb.obj postvxd.obj 
<<
        link @postvxd.crf
        mapsym postvxd


