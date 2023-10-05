CLS
SCREEN 12
pi = 3.1415926#
DO
CLS
CIRCLE (320, 240), 50, 1
FOR i = 1 TO 12
 y = SIN(i * pi / 6) * 40
 y = 240 - y
 x = COS(i * pi / 6) * 40
 x = 320 + x
 CIRCLE (x, y), 1, 1
NEXT i
a$ = TIME$
LOCATE 22, 15: PRINT a$
hour = VAL(LEFT$(a$, 2))
minture = VAL(MID$(a$, 4, 2))
second = VAL(RIGHT$(a$, 2))
hourx = 320 + COS(hour * pi / 60) * 30
houry = 240 + SIN(hour * pi / 60) * 30
minturex = 320 + COS(minture * pi / 60) * 30
minturey = 240 + SIN(minture * pi / 60) * 30
secondx = 320 - COS(second * pi / 60) * 30
secondy = 240 + SIN(second * pi / 60) * 30
LINE (320, 240)-(hourx, houry), 1
LINE (320, 240)-(secondx, secondy), 3
LINE (320, 240)-(minturex, minturey), 2
SLEEP 1
LOOP UNTIL INKEY$ <> ""
END

