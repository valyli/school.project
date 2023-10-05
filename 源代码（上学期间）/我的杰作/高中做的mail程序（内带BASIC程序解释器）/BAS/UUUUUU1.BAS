SCREEN 12
1 a = TIMER
pi = 3.1415926#
n1 = FIX(a / 3600): n2 = FIX(a / 60) - n1 * 60: n3 = a - n1 * 3600 - n2 * 60
CLS
x3 = 300 - 50 * (COS(n3 * pi / 30))
y3 = 150 + 50 * (SIN(n3 * pi / 30))
x1 = 300 - 30 * (COS(n1 * pi / 30))
y1 = 150 + 30 * (SIN(n1 * pi / 30))
x2 = 300 - 40 * (COS(n2 * pi / 30))
y2 = 150 + 30 * (SIN(n2 * pi / 30))
LINE (300, 150)-(x1, y1)
LINE (300, 150)-(x2, y2)
LINE (300, 150)-(x3, y3)
SLEEP 1
GOTO 1

