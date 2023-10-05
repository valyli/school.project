CLS : z = 0               'Don't carry out!
DIM a(4), b(4)
FOR a = 10000 TO 99999
 a$ = STR$(a)
 a0$ = LEFT$(a$, 1)
 a1$ = MID$(a$, 2, 1)
 a2$ = MID$(a$, 3, 1)
 a3$ = MID$(a$, 4, 1)
 a4$ = RIGHT$(a$, 1)
 a(0) = VAL(a0$)
 a(1) = VAL(a1$)
 a(2) = VAL(a2$)
 a(3) = VAL(a3$)
 a(4) = VAL(a4$)
 GOSUB 20
10 NEXT a
END
20 FOR z = 0 TO 4
 a$ = STR$(a(z))
 FOR t = 1 TO 4
  IF z + t <= 4 AND z + t >= 0 THEN
   c = z + t
   c$ = STR$(a(c))
   a$ = a$ + c$
  END IF
  IF z + t > 4 THEN
   c = z + t - 5
   c$ = STR$(a(c))
   a$ = a$ + c$
  END IF
 NEXT t
 GOSUB 30
 n = n + 1
 IF n = 2 THEN GOTO 40
NEXT z
e = 4
FOR i = 0 TO 4
 b(e) = a(i)
 e = e - 1
NEXT i
e = 0
FOR i = 0 TO 4
 a(i) = b(e)
 e = e + 1
NEXT i
GOTO 20
30 a1 = VAL(a$)
FOR p = 1 TO 1: NEXT p
FOR i = 2 TO a1 - 1
 IF a1 MOD i = 0 THEN GOTO 10
NEXT i
RETURN
40 PRINT a
END
'GOTO 10

