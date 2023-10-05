1 CLS
2 SCREEN 1
3 X = 0: Y = 0: D = 2: Z = 2: P = 0: R = 1
4 X = X + Z: Y = Y + D: P = P + 1
  IF X > 319 THEN Z = -Z
  IF Y > 199 THEN D = -D
  IF X < 0 THEN Z = -Z
  IF Y < 0 THEN D = -D
  IF R > 3 OR R = 3 THEN R = 0
  CIRCLE (X, Y), 15, R: PAINT (X, Y), R
  CIRCLE (X, Y), 14, R + 1: PAINT (X, Y), R + 1
  CIRCLE (X, Y), 10, R + 2: PAINT (X, Y), R + 2
  CIRCLE (X, Y), 5, R + 1: PAINT (X, Y), R + 1
  FOR Q = 1 TO 200
  K$ = INKEY$
  IF K$ = CHR$(27) THEN END
  NEXT Q
  IF P > 4500 THEN
   CLS
   P = 0
   R = R + 1
  END IF
5 GOTO 4


















