all: rtctest.exe

win16app.obj: win16app.c 
   cl -W3 -c -AS -Gsw2 -Fl win16app.c

rtctest.exe: win16app.def win16app.obj 
   link win16app,rtctest,rtctest.map /MAP /CO,slibcew libw /nod,win16app.def


