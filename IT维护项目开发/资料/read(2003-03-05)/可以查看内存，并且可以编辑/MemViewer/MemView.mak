# Microsoft Developer Studio Generated NMAKE File, Based on MemView.dsp
!IF "$(CFG)" == ""
CFG=MemView - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MemView - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MemView - Win32 Release" && "$(CFG)" != "MemView - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MemView.mak" CFG="MemView - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MemView - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MemView - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MemView - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\MemViewer.exe"


CLEAN :
	-@erase "$(INTDIR)\BEdit.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MemView.obj"
	-@erase "$(INTDIR)\MemView.pch"
	-@erase "$(INTDIR)\MemView.res"
	-@erase "$(INTDIR)\MemViewDoc.obj"
	-@erase "$(INTDIR)\MemViewView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase ".\MemViewer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MemView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x1009 /fo"$(INTDIR)\MemView.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MemView.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\MemViewer.pdb" /machine:I386 /out:"MemViewer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\BEdit.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MemView.obj" \
	"$(INTDIR)\MemViewDoc.obj" \
	"$(INTDIR)\MemViewView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MemView.res"

".\MemViewer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MemView - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MemView.exe" "$(OUTDIR)\MemView.bsc"


CLEAN :
	-@erase "$(INTDIR)\BEdit.obj"
	-@erase "$(INTDIR)\BEdit.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MemView.obj"
	-@erase "$(INTDIR)\MemView.pch"
	-@erase "$(INTDIR)\MemView.res"
	-@erase "$(INTDIR)\MemView.sbr"
	-@erase "$(INTDIR)\MemViewDoc.obj"
	-@erase "$(INTDIR)\MemViewDoc.sbr"
	-@erase "$(INTDIR)\MemViewView.obj"
	-@erase "$(INTDIR)\MemViewView.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MemView.bsc"
	-@erase "$(OUTDIR)\MemView.exe"
	-@erase "$(OUTDIR)\MemView.ilk"
	-@erase "$(OUTDIR)\MemView.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MemView.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x1009 /fo"$(INTDIR)\MemView.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MemView.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BEdit.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MemView.sbr" \
	"$(INTDIR)\MemViewDoc.sbr" \
	"$(INTDIR)\MemViewView.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\MemView.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\MemView.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MemView.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BEdit.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MemView.obj" \
	"$(INTDIR)\MemViewDoc.obj" \
	"$(INTDIR)\MemViewView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\MemView.res"

"$(OUTDIR)\MemView.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MemView.dep")
!INCLUDE "MemView.dep"
!ELSE 
!MESSAGE Warning: cannot find "MemView.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MemView - Win32 Release" || "$(CFG)" == "MemView - Win32 Debug"
SOURCE=.\BEdit.cpp

!IF  "$(CFG)" == "MemView - Win32 Release"


"$(INTDIR)\BEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ELSEIF  "$(CFG)" == "MemView - Win32 Debug"


"$(INTDIR)\BEdit.obj"	"$(INTDIR)\BEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "MemView - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ELSEIF  "$(CFG)" == "MemView - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ENDIF 

SOURCE=.\MemView.cpp

!IF  "$(CFG)" == "MemView - Win32 Release"


"$(INTDIR)\MemView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ELSEIF  "$(CFG)" == "MemView - Win32 Debug"


"$(INTDIR)\MemView.obj"	"$(INTDIR)\MemView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ENDIF 

SOURCE=.\MemView.rc

"$(INTDIR)\MemView.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\MemViewDoc.cpp

!IF  "$(CFG)" == "MemView - Win32 Release"


"$(INTDIR)\MemViewDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ELSEIF  "$(CFG)" == "MemView - Win32 Debug"


"$(INTDIR)\MemViewDoc.obj"	"$(INTDIR)\MemViewDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ENDIF 

SOURCE=.\MemViewView.cpp

!IF  "$(CFG)" == "MemView - Win32 Release"


"$(INTDIR)\MemViewView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ELSEIF  "$(CFG)" == "MemView - Win32 Debug"


"$(INTDIR)\MemViewView.obj"	"$(INTDIR)\MemViewView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\MemView.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "MemView - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\MemView.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\MemView.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "MemView - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MemView.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\MemView.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

