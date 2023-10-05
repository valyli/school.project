CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG -DWANTVXDWRAPS
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: vxdisr.vxd

vxdisr.obj: vxdisr.c
        cl $(CVXDFLAGS) -Fo$@ %s

ddbisr.obj: ddbisr.asm
        ml $(AFLAGS) -Fo$@ %s

vxdisr.vxd: ddbisr.obj vxdisr.obj ..\wrappers\vxdcall.obj vxdisr.def 
        echo >NUL @<<vxdisr.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:vxdisr.def -OUT:vxdisr.vxd -MAP:vxdisr.map
-VXD vxdwraps.clb wrappers.clb ddbisr.obj vxdisr.obj vxdcall.obj
<<KEEP
        link @vxdisr.crf
        mapsym vxdisr


