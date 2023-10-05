CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG -DWANTVXDWRAPS
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: pagetrap.vxd

pagetrap.obj: pagetrap.c
        cl $(CVXDFLAGS) -Fo$@ %s

pageddb.obj: pageddb.asm
        ml $(AFLAGS) -Fo$@ %s

pagetrap.vxd: pageddb.obj pagetrap.obj ..\wrappers\vxdcall.obj pagetrap.def 
        echo >NUL @<<pagetrap.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:pagetrap.def -OUT:pagetrap.vxd -MAP:pagetrap.map
-VXD vxdwraps.clb wrappers.clb pageddb.obj pagetrap.obj vxdcall.obj
<<
        link @pagetrap.crf
        mapsym pagetrap


