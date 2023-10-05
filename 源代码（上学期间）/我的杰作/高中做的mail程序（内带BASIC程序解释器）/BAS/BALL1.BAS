1 CLS
2 SCREEN 1
3 X = 0: Y = 0: D = 2: Z = 2
4 X = X + Z: Y = Y + D
  IF X > 319 THEN Z = -Z
  IF Y > 200 THEN D = -D
  IF X < 0 THEN Z = -Z
  IF Y < 0 THEN D = -D
  CIRCLE (X, Y), 10, 1: PAINT (X, Y), 1
  CIRCLE (X, Y), 8, 2: PAINT (X, Y), 2
  CIRCLE (X, Y), 6, 0: PAINT (X, Y), 0
  CIRCLE (X, Y), 4, 3: PAINT (X, Y), 3
  FOR Q = 1 TO 200
  K$ = INKEY$
  IF K$ = CHR$(27) THEN END
  NEXT Q
  CLS
5 GOTO 4


















