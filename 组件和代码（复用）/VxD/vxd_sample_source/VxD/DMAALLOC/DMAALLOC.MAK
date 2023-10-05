CFLAGS     = -DWIN32 -DCON -Di386 -D_X86_ -D_NTWIN -W3 -Gs -D_DEBUG -Zi
CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG
LFLAGS     = -machine:i386 -debug:notmapped,full -debugtype:cv -subsystem:console kernel32.lib 
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: dmaalloc.vxd

dmaalloc.obj: dmaalloc.c
        cl $(CVXDFLAGS) -Fo$@ -Fl %s

dmaddb.obj: dmaddb.asm
        ml $(AFLAGS) -Fo$@ %s

vxdcall.obj: vxdcall.c
        cl $(CVXDFLAGS) -Fo$@ %s

dmaalloc.vxd: dmaddb.obj dmaalloc.obj ..\wrappers\vxdcall.obj ..\wrappers\wrappers.clb dmaalloc.def 
        echo >NUL @<<dmaalloc.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:dmaalloc.def -OUT:dmaalloc.vxd -MAP:dmaalloc.map
-VXD vxdwraps.clb wrappers.clb vxdcall.obj dmaddb.obj dmaalloc.obj 
<<
        link @dmaalloc.crf
        mapsym dmaalloc


