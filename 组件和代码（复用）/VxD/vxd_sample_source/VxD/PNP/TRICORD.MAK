CFLAGS     = -DWIN32 -DCON -Di386 -D_X86_ -D_NTWIN -W3 -Gs -D_DEBUG -Zi
CVXDFLAGS  = -Zdp -Gs -c -DIS_32 -Zl -DDEBLEVEL=1 -DDEBUG
LFLAGS     = -machine:i386 -debug:notmapped,full -debugtype:cv -subsystem:console kernel32.lib 
AFLAGS     = -coff -DBLD_COFF -DIS_32 -W2 -Zd -c -Cx -DMASM6 -DDEBLEVEL=1 -DDEBUG

all: tricord.vxd

pnp.obj: pnp.c
        cl $(CVXDFLAGS) -Fo$@ %s 

tricord.obj: tricord.asm
        ml $(AFLAGS) -Fo$@ %s

tricord.vxd: tricord.obj pnp.obj ..\wrappers\vxdcall.obj tricord.def
        echo >NUL @<<tricord.crf
-MACHINE:i386 -DEBUG -DEBUGTYPE:MAP -PDB:NONE 
-DEF:tricord.def -OUT:tricord.vxd -MAP:tricord.map
-VXD vxdwraps.clb wrappers.clb vxdcall.obj tricord.obj pnp.obj
<<KEEP
        link @tricord.crf
        mapsym tricord


