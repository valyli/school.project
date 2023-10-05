CLS
FOR i = 97 TO 100
 FOR j = 1 TO 12
  t$ = CHR$(i) + STR$(j)
  SHELL "c:\ÿmailall\ÿÿÿÿ\login " + t$
  SHELL "c:\ÿmailall\ÿÿÿÿ\deltree/y m:\wps.bat"
  SHELL "copy c:\ÿmailall\ÿÿÿÿ\manager\wps.bat m:\wps.bat"
 NEXT j
NEXT i
CLS
LOCATE 15, 30: PRINT "¹«¸æÕÅÌùÍê±Ï!"

