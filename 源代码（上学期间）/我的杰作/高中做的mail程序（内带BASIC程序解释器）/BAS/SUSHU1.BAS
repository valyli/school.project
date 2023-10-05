'求五位数中的素数,且正倒序都为素数
f = 0
CLS : tt1 = TIMER
FOR x1 = 10000 TO 99999
 FOR i = 2 TO x - 1
  IF x1 MOD i = 0 THEN GOTO 10
 NEXT i
 GOSUB 20
10 NEXT x1
tt2 = TIMER
 PRINT
 PRINT
 PRINT "Time:", tt2 - tt1; "s"
 PRINT "Count:", f; "Number(s)"
 PRINT "Speed:", f / (tt2 - tt1); "N/S"
END
20 x$ = STR$(x1)
x1$ = LEFT$(x$, 1)
x2$ = MID$(x$, 2, 1)
x3$ = MID$(x$, 3, 1)
x4$ = MID$(x$, 4, 1)
x5$ = RIGHT$(x$, 1)
x$ = x5$ + x4$ + x3$ + x2$ + x1$
x2 = VAL(x$)
FOR z = 2 TO x2 - 1
 IF x2 MOD z = 0 THEN RETURN
NEXT z
PRINT x1,
f = f + 1
IF INKEY$ = CHR$(27) THEN
 tt2 = TIMER
 PRINT
 PRINT
 PRINT "Time:", tt2 - tt1; "s"                '1102.297
 PRINT "Count:", f; "Number(s)"               '6111
 PRINT "Speed:", f / (tt2 - tt1); "N/S"       '5.543879
 END
END IF
RETURN

