all: polled.dll 

# DRIVER DLL 

polled.obj: polled.c driver.h 
  cl -c -W3 -ASw -Gsw2 -Oi $*.c

polled.dll: polled.def polled.obj 
  link polled,polled.dll,polled.map /CO /MAP, \
     sdllcew libw /nod/noe,polled.def
  implib driver.lib polled.dll
  copy polled.dll \windows\driver.dll
