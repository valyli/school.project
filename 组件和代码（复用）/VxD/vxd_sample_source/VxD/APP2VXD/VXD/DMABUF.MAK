CFLAGS     = -DWIN32 -DCON -Di386 -D_X86_ -D_NTWIN -W3 -Gs -D_DEBUG -Zi
CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG
LFLAGS     = -machine:i386 -debug:notmapped,full -debugtype:cv -subsystem:console kernel32.lib 
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: dmabuf.vxd

dmabuf.obj: dmabuf.c
        cl $(CVXDFLAGS) -Fo$@ %s

dmaddb.obj: dmaddb.asm
        ml $(AFLAGS) -Fo$@ %s

dmabuf.vxd: dmaddb.obj dmabuf.obj ..\..\wrappers\vxdcall.obj ..\..\wrappers\wrappers.clb dmabuf.def 
        echo >NUL @<<dmabuf.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:dmabuf.def -OUT:dmabuf.vxd -MAP:dmabuf.map
-VXD vxdwraps.clb wrappers.clb vxdcall.obj dmaddb.obj dmabuf.obj 
<<
        link @dmabuf.crf
        mapsym dmabuf


