all: testdriv.exe

testdriv.res: testdriv.rc testdriv.h
   rc -r testdriv.rc

testdriv.obj: testdriv.c testdriv.h driver.h
   cl -W3 -c -AS -Gsw2 testdriv.c

testdriv.exe: testdriv.def testdriv.obj testdriv.res
   link testdriv,testdriv,testdrvi.map /MAP /CO,slibcew libw ..\skeldll\driver.lib/nod,testdriv.def
   rc testdriv


