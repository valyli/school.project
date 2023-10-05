1 CLS
2 SCREEN 1: DIM a(10000)
3 x = 10: y = 10: D = 2: Z = 2
  CIRCLE (x, y), 10, 1: PAINT (x, y), 1
  CIRCLE (x, y), 8, 2: PAINT (x, y), 2
  CIRCLE (x, y), 6, 0: PAINT (x, y), 0
  CIRCLE (x, y), 4, 3: PAINT (x, y), 3
  GET (x - 10, y - 10)-(x + 10, y + 10), a
4 x = x + Z: y = y + D
  IF x > 300 THEN Z = -Z
  IF y > 100 THEN D = -D
  IF x < 0 THEN Z = -Z
  IF y < 0 THEN D = -D
  PUT (x, y), a, XOR
  
  FOR Q = 1 TO 2000
  K$ = INKEY$
  IF K$ = CHR$(27) THEN END
  NEXT Q
  PUT (x, y), a, XOR
  'CLS
5 GOTO 4


















