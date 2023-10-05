10 CLS
20 SCREEN 1
   LOCATE 5, 16: PRINT "W E I  Q I"
   LOCATE 7, 9: PRINT "  I'm a computer. Welcome to play WEIQI                                         with me. Good wishes for you!"
   LOCATE 15, 10: PRINT "Press any key to contione": SLEEP 1
   DO: LOOP WHILE INKEY$ = ""
30 CLS
40 COLOR 0, 1
50 LINE (14, 4)-(172, 164), 1, B: PAINT (15, 5), 2
60 k = 16
70 FOR i = 1 TO 20
80   LINE (k, 8)-(k, 160), 1
90   k = k + 8
100 NEXT i
110 T = 8
120 FOR z = 1 TO 20
130   LINE (16, T)-(168, T), 1
140   T = T + 8
150 NEXT z
160 PRINT " 1    5   10   15   ";
170 PRINT "20"
180 PRINT " ": PRINT " ": PRINT " ": PRINT " ": PRINT " 5": PRINT " "
190 PRINT " ": PRINT " ": PRINT " ": PRINT "10": PRINT " ": PRINT " ": PRINT " "
200 PRINT " ": PRINT "15": PRINT " ": PRINT " ": PRINT " ": PRINT " ": PRINT "20"
210 PRINT " ": LOCATE 6, 23: PRINT "INPUT 0,0 TO QUIT": LOCATE 8, 24: PRINT "BLACK IS YOURS": E = 1: F = 1
220
230 LOCATE 12, 23
240 INPUT "1 INPUT(X,Y)=", x, y
250 IF x = 0 AND y = 0 THEN END ELSE
    IF x >= 1 AND x <= 20 AND y >= 1 AND y <= 20 THEN GOTO 260 ELSE GOTO 230
260 P = x * 8 + 8
270 R = y * 8
    U = POINT(P, R)
    IF U = 0 OR U = 3 THEN GOTO 220 ELSE
280 CIRCLE (P, R), 3, 0: PAINT (P, R), 0: LOCATE 14, 24: PRINT "1-"; E: E = E + 1
290 LOCATE 12, 23
350 RANDOMIZE TIMER: SLEEP 1
360   C = RND * 10 + 1
370   D = RND * 10 + 1
380   IF C > 2.5 AND C <= 5 THEN
         P1 = P + 8: R1 = R + 8
         ELSEIF C > 5 AND C <= 7.5 THEN
         P1 = P - 8: R1 = R - 8
400   ELSEIF C <= 2.5 THEN
P1 = P + 8: R1 = R + 16
410  ELSEIF C > 7.5 THEN
P1 = P - 8: R1 = R - 16
420  ELSEIF D > 5 AND D <= 7.5 THEN
P1 = P + 16: R1 = R + 8
430  ELSEIF D > 2.5 AND D <= 5 THEN
P1 = P - 16: R1 = R + 8
440   ELSEIF D <= 2.5 THEN
P1 = P + 16: R1 = R - 8
450   ELSEIF D > 7.5 THEN
P1 = P - 16: R1 = R - 8
      ELSEIF P1 < 16 OR P1 > 168 THEN
      GOTO 360
      ELSEIF R1 < 8 OR R1 > 160 THEN
      GOTO 360
     END IF
460   U = POINT(P1, R1): IF U = 0 OR U = 3 THEN GOTO 350
470   CIRCLE (P1, R1), 3, 4: PAINT (P1, R1), 4: LOCATE 15, 24: PRINT "2-"; F: F = F + 1
490 GOTO 230

