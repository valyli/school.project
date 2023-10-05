SCREEN 2: CLS : KEY OFF
PI = 3.1415926#: D = 100
FOR A = 0 TO 2 * PI STEP PI / 360
E = D * (1 + 1 / 4 * SIN(12 * A))
F = E * (1 + SIN(4 * A))
X1 = 320 + F * COS(A)
X2 = 320 + F * COS(A + PI / 5)
Y1 = 100 + F * SIN(A) / 2
Y2 = 100 + F * SIN(A + PI / 5) / 2
LINE (X1, Y1)-(X2, Y2)
NEXT A
END

