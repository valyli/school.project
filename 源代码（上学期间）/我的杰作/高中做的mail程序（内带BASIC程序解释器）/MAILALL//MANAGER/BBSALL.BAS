CLS
FOR i = 97 TO 100
 FOR j = 1 TO 12
  t$ = CHR$(i) + STR$(j)
  SHELL "c:\�mailall\����\login " + t$
  SHELL "c:\�mailall\����\deltree/y m:\wps.bat"
  SHELL "copy c:\�mailall\����\manager\wps.bat m:\wps.bat"
 NEXT j
NEXT i
CLS
LOCATE 15, 30: PRINT "�����������!"

