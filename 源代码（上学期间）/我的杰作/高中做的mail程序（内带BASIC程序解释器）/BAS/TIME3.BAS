SCREEN 12: COLOR 14
1 CLS
e$ = TIME$
a$ = LEFT$(e$, 2): a = VAL(a$)
b$ = MID$(e$, 4, 2): b = VAL(b$)
c$ = RIGHT$(e$, 2): c = VAL(c$)
n1 = a / 2: n2 = b: n3 = c
d = -3.1415926# / 30
x1 = 300 + 50 * (SIN(n1 * d))
y1 = 200 - 50 * (COS(n1 * d))
x2 = 300 - 70 * (SIN(n2 * d))
y2 = 200 - 70 * (COS(n2 * d))
x3 = 300 - 90 * (SIN(n3 * d))
y3 = 200 - 90 * (COS(n3 * d))
CIRCLE (300, 200), 110, 2: PAINT (300, 200), 2
LINE (300, 200)-(x1, y1)
LINE (300, 200)-(x2, y2)
LINE (300, 200)-(x3, y3)
FOR i = 1 TO 60
 a1 = 300 + 100 * (SIN(i * d))
 b1 = 200 - 100 * (COS(i * d))
 CIRCLE (a1, b1), 1
NEXT i
LOCATE 1, 1: PRINT e$
SLEEP 1: IF INKEY$ = CHR$(27) THEN END
GOTO 1







