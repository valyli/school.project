all: intbasic.dll             

# DRIVER DLL 
         
intbasic.obj: intbasic.c intbasic.h 
  cl -c -W3 -ASw -GD2s -Zi -Oi $*.c

isr.obj: isr.c intbasic.h 
  cl -c -W3 -ASw -GD2s -Zi -Oi $*.c

intbasic.dll: intbasic.def intbasic.obj isr.obj
  link intbasic+isr,intbasic.dll,intbasic.map /CO /MAP, \
      sdllcew libw /nod/noe,intbasic.def
  implib intbasic.lib intbasic.dll intbasic.def
  copy intbasic.dll \windows\driver.dll

