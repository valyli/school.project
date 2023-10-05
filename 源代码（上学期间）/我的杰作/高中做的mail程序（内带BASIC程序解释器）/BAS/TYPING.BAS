1 REM TYPING
2 CLS
3 SCREEN 1
4 LOCATE 10, 17: PRINT "TYPING!"
5
6 LOCATE 19, 10: PRINT "Press return to contine."
7 IF INKEY$ = CHR$(13) THEN GOTO 8 ELSE GOTO 7
8 CLS : INPUT "How many letters?", A: INPUT "how fast? (1--9)", B: INPUT "How hard? (1--4)", C
9 IF C = 1 THEN
   M = 97: N = 122
  END IF
  IF C = 2 THEN
   M = 65: N = 90
  END IF
  IF C = 3 THEN
   M = 48: N = 57
  END IF
  IF C = 4 THEN
   M = 33: N = 126
  END IF: CLS
10 FOR D = 1 TO A
   RANDOMIZE TIMER: y = 0
   A = FIX(RND * (N + 1 - M)) + M: A$ = CHR$(A)
   FOR E = 1 TO 23
    PRINT A$: FOR o = 1 TO 5000: NEXT o
    
    LINE (0, y)-(8, y - 8), 0, B
    PAINT (2, y - 4), 0
    y = y + 16
    IF INKEY$ = A$ THEN GOTO 11
   NEXT E: LOCATE 1, 1
11 NEXT D
12 INPUT "Would you like do it again? (Y/N)", Z$
   IF Z$ = "y" THEN GOTO 8 ELSE END




