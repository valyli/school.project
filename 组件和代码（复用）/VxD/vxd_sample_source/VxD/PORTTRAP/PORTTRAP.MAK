CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG -DWANTVXDWRAPS
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: porttrap.vxd

porttrap.obj: porttrap.c
        cl $(CVXDFLAGS) -Fo$@ %s

portddb.obj: portddb.asm
        ml $(AFLAGS) -Fo$@ %s

porttrap.vxd: portddb.obj porttrap.obj ..\wrappers\vxdcall.obj porttrap.def 
        echo >NUL @<<porttrap.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:porttrap.def -OUT:porttrap.vxd -MAP:porttrap.map
-VXD vxdwraps.clb wrappers.clb portddb.obj porttrap.obj vxdcall.obj
<<
        link @porttrap.crf
        mapsym porttrap


