CLS
SHELL "c:\�mailall\login b8"
SHELL "c:\�mailall\����\xcopy c:\�mailall\*.* m:\/s/e"
SHELL "c:\�mailall\����\attrib m:\���� +r +s +h"
SHELL "c:\�mailall\����\attrib m:\�����.bat +r +s +h"
SHELL "c:\�mailall\����\attrib m:\����\mail.bas +r"
shell "c:\�mailall\����\attrib m:\����\publis.dat +r"  
FOR i = 97 TO 100
 FOR j = 1 TO 12
  a$ = CHR$(i)
  b$ = STR$(j)
  a$ = a$ + b$
  a$ = "c:\�mailall\����\login " + a$
  SHELL a$
  SHELL "c:\�mailall\����\deltree/y m:\mail.bat"
  SHELL "c:\�mailall\����\deltree/y m:\�����.bat"
  SHELL "copy c:\�mailall\mail.bat m:\"
  SHELL "copy c:\�mailall\�����.bat m:\"
  SHELL "c:\�mailall\����\attrib m:\�����.bat +r +s +h"
 NEXT j
NEXT i
SYSTEM

