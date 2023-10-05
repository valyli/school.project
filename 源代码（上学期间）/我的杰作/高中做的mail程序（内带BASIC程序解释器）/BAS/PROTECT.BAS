DIM c(5120): RANDOMIZE TIMER: a = 1: b = 1: a1 = 1: b1 = 1: ON TIMER(1) GOSUB 300: TIMER ON
10 SCREEN 12: COLOR 10: l1 = 1: l2 = 3: l3 = 4
PRINT " I want to sleep !"
PRINT "I must to sleep now !"
GET (0, 0)-(165, 32), c
CLS
LOCATE 15, 29: PRINT "I'm ready to sleep !"
GOSUB 400
CLS
20 O = 0: q = 8: w = 8: e = 8
DO WHILE INKEY$ = ""
    O = O + 1
    x = FIX(RND * 640) + 1
    y = FIX(RND * 480) + 1
    CIRCLE (x + 50, y + 5), q, l1: PAINT (x + 50, y + 5), l1
    CIRCLE (x - 29, y + 56), w, l2: PAINT (x - 29, y + 56), l2
    CIRCLE (x + 12, y - 30), e, l3: PAINT (x + 12, y - 30), l3
    GOSUB 100
    IF O > 600 THEN
    O = 0
    CLS
    END IF
LOOP
GOSUB 200
50 SYSTEM
100
a = a + a1: b = b + b1
IF a <= 0 OR a >= 469 THEN a1 = -a1
IF b <= 0 OR b >= 419 THEN b1 = -b1
PUT (a, b), c, XOR
FOR i = 1 TO 500
NEXT i
PUT (a, b), c, XOR
RETURN
200
COLOR 14
LOCATE 14, 27: PRINT "************************"
PRINT
LOCATE 15, 27: PRINT "* I am waking up now ! *"
PRINT
LOCATE 16, 27: PRINT "************************"
LOCATE 28, 1: PRINT "If you want let me work , please ---"
RETURN
300
COLOR 15
LOCATE 1, 73
ti = TIMER
IF INT(ti / 3600) = ti / 3600 THEN GOSUB 400 ELSE
a$ = TIME$
PRINT a$
COLOR 11
RETURN
400
FOR i = 1 TO 3
SOUND 800, 10: SLEEP 1
FOR j = 1 TO 10000
NEXT j
NEXT i
SOUND 1500, 10
RETURN

