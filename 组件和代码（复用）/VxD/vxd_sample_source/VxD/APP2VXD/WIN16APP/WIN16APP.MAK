all: win16app.exe

win16app.obj: win16app.c 
   cl -W3 -c -AS -Gsw2 -I..\vxd win16app.c

win16app.exe: win16app.def win16app.obj 
   link win16app.obj,win16app.exe,win16app.map /MAP /CO,slibcew libw /nod,win16app.def


