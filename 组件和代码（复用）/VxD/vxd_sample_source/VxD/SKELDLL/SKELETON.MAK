all: skeleton.dll

# DRIVER DLL 

skeleton.obj: skeleton.c driver.h 
  cl -c -W3 -ASw -GD2s -Oi $*.c

skeleton.dll: skeleton.def skeleton.obj 
  link skeleton,skeleton.dll,skeleton.map /MAP, sdllcew libw /nod/noe,skeleton.def
  implib driver.lib skeleton.dll
  copy skeleton.dll \windows\driver.dll


