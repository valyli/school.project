win32app.exe: win32app.obj
   link @<<
kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib 
shell32.lib ole32.lib oleaut32.lib uuid.lib ..\32\skel32.lib
/NOLOGO /SUBSYSTEM:console 
/INCREMENTAL:no /PDB:none /MACHINE:I386 /OUT:win32app.exe win32app.obj
<<

win32app.obj: win32app.c
   cl /c /ML /GX /YX /Od /D "WIN32" /D "NDEBUG" /D "_CONSOLE" -I..\dll32 win32app.c



