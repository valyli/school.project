CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG -DWANTVXDWRAPS
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: reflect.vxd

reflect.obj: reflect.c
        cl $(CVXDFLAGS) -Fo$@ %s

reflddb.obj: reflddb.asm
        ml $(AFLAGS) -Fo$@ %s

reflect.vxd: reflddb.obj reflect.obj ..\wrappers\vxdcall.obj reflect.def 
        echo >NUL @<<reflect.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:reflect.def -OUT:reflect.vxd -MAP:reflect.map
-VXD vxdwraps.clb wrappers.clb reflddb.obj reflect.obj vxdcall.obj
<<KEEP
        link @reflect.crf
        mapsym reflect


