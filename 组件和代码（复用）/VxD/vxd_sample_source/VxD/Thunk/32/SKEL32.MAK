all: skel32.dll

!message
!message +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!message + To make the file dll32.dll, you will need to have the       +
!message + Microsoft Thunk compiler and the Microsoft Macro Assembler  +
!message + (ML) on the path.                                           +
!message +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
!message

skel32.obj: skel32.c skel32.h
    cl -c -W3 -Z7 -Od -DWIN32 -D_WIN32 -D_MT -D_DLL $*.c 

thk32.obj:  ..\16\skeleton.asm
  ml /DIS_32 /c /W3 /Fo thk32.obj ..\16\skeleton.asm

# Build rule for the DLL
skel32.dll: skel32.def skel32.obj thk32.obj
    link /NODEFAULTLIB /INCREMENTAL:NO /PDB:NONE /RELEASE \
    -debug:full -debugtype:cv -align:0x1000 -dll \
    -base:0x1C000000           \
    -entry:_DllMainCRTStartup@12 \
    -out:skel32.dll        \
    -implib:skel32.lib	   \
    skel32.obj thk32.obj thunk32.lib libc.lib oldnames.lib kernel32.lib



# Build rule for EXE
$(PROJ).EXE: $(BASE_OBJS) $(PROJ_OBJS) $(DLLNAME).dll
    $(link) $(linkdebug) $(guilflags4) \
    $(BASE_OBJS) $(PROJ_OBJS) $(guilibsdll) $(EXTRA_LIBS) \
    $(DLLNAME).lib \
    -out:$(PROJ).exe $(MAPFILE)



# Rules for cleaning out those old files
clean:
    del *.bak *.pdb *.obj *.res *.exp *.map *.sbr *.bsc
