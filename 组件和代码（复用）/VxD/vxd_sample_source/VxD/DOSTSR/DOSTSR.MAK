all: dostsr.dll 

# DRIVER DLL 

dostsr.obj: dostsr.c dostsr.h 
  cl -c -W3 -ASw -Gsw2 -Oi $*.c

dostsr.dll: dostsr.def dostsr.obj 
  link dostsr,dostsr.dll,dostsr.map /CO /MAP,sdllcew libw /nod/noe,dostsr.def
  implib driver.lib dostsr.dll
  copy dostsr.dll \windows\driver.dll
