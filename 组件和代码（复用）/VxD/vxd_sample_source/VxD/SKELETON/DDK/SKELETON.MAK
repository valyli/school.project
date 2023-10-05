CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG -DWANTVXDWRAPS=1
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: skeleton.vxd

skeleton.obj: skeleton.c
        cl $(CVXDFLAGS) -Fo$@ -Fc %s

skelctrl.obj: skelctrl.asm
        ml $(AFLAGS) -Fo$@ %s

skeleton.vxd: skelctrl.obj skeleton.obj ..\..\wrappers\vxdcall.obj ..\..\wrappers\wrappers.clb skeleton.def 
        echo >NUL @<<skeleton.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:skeleton.def -OUT:skeleton.vxd -MAP:skeleton.map
-VXD vxdwraps.clb wrappers.clb skelctrl.obj skeleton.obj vxdcall.obj
<<
        link @skeleton.crf
        mapsym skeleton


