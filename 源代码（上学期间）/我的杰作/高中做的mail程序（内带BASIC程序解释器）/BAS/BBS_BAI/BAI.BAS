FOR i = 97 TO 122
CLOSE
n = 1
a$ = "m:\bbs\use\" + CHR$(i) + ".bas"
SHELL "copy/y c:\���\main.bas" + " m:\bbs\use\" + CHR$(i) + ".bas"
'SHELL "qbasic m:\bbs\use\" + CHR$(I) + ".bas"
OPEN "m:\bbs\use\" + CHR$(i) + ".bas" FOR INPUT AS #1
OPEN "c:\���\xu.dat" FOR OUTPUT AS #2
DO WHILE NOT EOF(1)
LINE INPUT #1, cat$
   IF n = 1 THEN
   m$ = LEFT$(cat$, 14) + CHR$(i) + RIGHT$(cat$, 1)
   n = 2
   ELSE
   m$ = cat$
END IF
PRINT #2, m$
LOOP
CLOSE
SHELL "copy/y c:\���\xu.dat m:\bbs\use\" + CHR$(i) + ".bas"
NEXT i
SYSTEM



