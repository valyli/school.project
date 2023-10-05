# Microsoft Developer Studio Generated NMAKE File, Based on ProcessKiller.dsp
!IF "$(CFG)" == ""
CFG=ProcessKiller - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ProcessKiller - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ProcessKiller - Win32 Release" && "$(CFG)" != "ProcessKiller - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProcessKiller.mak" CFG="ProcessKiller - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProcessKiller - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ProcessKiller - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProcessKiller - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ProcessKiller.exe"


CLEAN :
	-@erase "$(INTDIR)\ListCtrlEx.obj"
	-@erase "$(INTDIR)\ProcessFunction.obj"
	-@erase "$(INTDIR)\ProcessKiller.obj"
	-@erase "$(INTDIR)\ProcessKiller.pch"
	-@erase "$(INTDIR)\ProcessKiller.res"
	-@erase "$(INTDIR)\ProcessKillerDlg.obj"
	-@erase "$(INTDIR)\PSAPI.obj"
	-@erase "$(INTDIR)\ShowListDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ProcessKiller.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ProcessKiller.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\ProcessKiller.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ProcessKiller.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ProcessKiller.pdb" /machine:I386 /out:"$(OUTDIR)\ProcessKiller.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ListCtrlEx.obj" \
	"$(INTDIR)\ProcessFunction.obj" \
	"$(INTDIR)\ProcessKiller.obj" \
	"$(INTDIR)\ProcessKillerDlg.obj" \
	"$(INTDIR)\PSAPI.obj" \
	"$(INTDIR)\ShowListDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ProcessKiller.res"

"$(OUTDIR)\ProcessKiller.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ProcessKiller - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ProcessKiller.exe"


CLEAN :
	-@erase "$(INTDIR)\ListCtrlEx.obj"
	-@erase "$(INTDIR)\ProcessFunction.obj"
	-@erase "$(INTDIR)\ProcessKiller.obj"
	-@erase "$(INTDIR)\ProcessKiller.pch"
	-@erase "$(INTDIR)\ProcessKiller.res"
	-@erase "$(INTDIR)\ProcessKillerDlg.obj"
	-@erase "$(INTDIR)\PSAPI.obj"
	-@erase "$(INTDIR)\ShowListDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ProcessKiller.exe"
	-@erase "$(OUTDIR)\ProcessKiller.ilk"
	-@erase "$(OUTDIR)\ProcessKiller.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\ProcessKiller.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\ProcessKiller.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ProcessKiller.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ProcessKiller.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ProcessKiller.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ListCtrlEx.obj" \
	"$(INTDIR)\ProcessFunction.obj" \
	"$(INTDIR)\ProcessKiller.obj" \
	"$(INTDIR)\ProcessKillerDlg.obj" \
	"$(INTDIR)\PSAPI.obj" \
	"$(INTDIR)\ShowListDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ProcessKiller.res"

"$(OUTDIR)\ProcessKiller.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ProcessKiller.dep")
!INCLUDE "ProcessKiller.dep"
!ELSE 
!MESSAGE Warning: cannot find "ProcessKiller.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ProcessKiller - Win32 Release" || "$(CFG)" == "ProcessKiller - Win32 Debug"
SOURCE=.\ListCtrlEx.cpp

"$(INTDIR)\ListCtrlEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ProcessKiller.pch"


SOURCE=.\ProcessFunction.cpp

"$(INTDIR)\ProcessFunction.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ProcessKiller.pch"


SOURCE=.\ProcessKiller.cpp

"$(INTDIR)\ProcessKiller.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ProcessKiller.pch"


SOURCE=.\ProcessKiller.rc

"$(INTDIR)\ProcessKiller.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ProcessKillerDlg.cpp

"$(INTDIR)\ProcessKillerDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ProcessKiller.pch"


SOURCE=.\PSAPI.cpp

"$(INTDIR)\PSAPI.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ProcessKiller.pch"


SOURCE=.\ShowListDlg.cpp

"$(INTDIR)\ShowListDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ProcessKiller.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ProcessKiller - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\ProcessKiller.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ProcessKiller.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ProcessKiller - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\ProcessKiller.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ProcessKiller.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

