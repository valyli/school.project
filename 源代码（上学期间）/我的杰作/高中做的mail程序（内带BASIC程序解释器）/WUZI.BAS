DIM gbiao(256)
bchessx = 1: bchessy = 1
ON KEY(11) GOSUB 210
ON KEY(12) GOSUB 220
ON KEY(13) GOSUB 230
ON KEY(14) GOSUB 240
KEY(11) ON
KEY(12) ON
KEY(13) ON
KEY(14) ON
CLS
SCREEN 12
LINE (0, 0)-(16, 16), 1, B
GET (0, 0)-(16, 16), gbiao
CLS
LINE (5, 5)-(435, 435), 6, B
PAINT (10, 10), 6
FOR i = 20 TO 420 STEP 22
 LINE (i, 20)-(i, 415), 8
NEXT i
FOR i = 20 TO 420 STEP 22
 LINE (20, i)-(415, i), 8
NEXT i
CIRCLE (218, 218), 3, 8
PAINT (218 - 1, 218 - 1), 8
PAINT (218 + 1, 218 - 1), 8
PAINT (218 + 1, 218 + 1), 8
PAINT (218 - 1, 218 + 1), 8
CIRCLE (86, 86), 3, 8
PAINT (86 - 1, 86 - 1), 8
PAINT (86 + 1, 86 - 1), 8
PAINT (86 + 1, 86 + 1), 8
PAINT (86 - 1, 86 + 1), 8
CIRCLE (350, 350), 3, 8
PAINT (350 - 1, 350 - 1), 8
PAINT (350 + 1, 350 - 1), 8
PAINT (350 + 1, 350 + 1), 8
PAINT (350 - 1, 350 + 1), 8
CIRCLE (86, 350), 3, 8
PAINT (86 - 1, 350 - 1), 8
PAINT (86 + 1, 350 - 1), 8
PAINT (86 + 1, 350 + 1), 8
PAINT (86 - 1, 350 + 1), 8
CIRCLE (350, 86), 3, 8
PAINT (350 - 1, 86 - 1), 8
PAINT (350 + 1, 86 - 1), 8
PAINT (350 + 1, 86 + 1), 8
PAINT (350 - 1, 86 + 1), 8
DIM chess(18, 18)
PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
10
DO
choose$ = INKEY$
IF choose$ = CHR$(27) THEN END
LOOP UNTIL choose$ = CHR$(32)
IF chess(bchessx - 1, bchessy - 1) = 0 THEN
 chess(bchessx - 1, bchessy - 1) = 1
 PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
 CIRCLE ((bchessx - 1) * 22 + 21, (bchessy - 1) * 22 + 19), 7, 0
 PAINT ((bchessx - 1) * 22 + 20, (bchessy - 1) * 22 + 20), 0
 PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
ELSE
 GOTO 10
END IF
chessno = 1: chessnox = bchessx - 1: chessnoy = bchessy - 1
GOSUB 100
20
RANDOMIZE TIMER
chessmove = INT((RND * 1000) + 1)
SELECT CASE chessmove
CASE IS >= 875
 chessmovex = 1
 chessmovey = 1
 GOTO 21
CASE 750 TO 875
 chessmovex = 1
 chessmovey = 0
 GOTO 21
CASE 625 TO 750
 chessmovex = 1
 chessmovey = -1
 GOTO 21
CASE 500 TO 625
 chessmovex = 0
 chessmovey = -1
 GOTO 21
CASE 375 TO 500
 chessmovex = -1
 chessmovey = -1
 GOTO 21
CASE 250 TO 375
 chessmovex = -1
 chessmovey = 0
 GOTO 21
CASE 125 TO 250
 chessmovex = -1
 chessmovey = 1
 GOTO 21
CASE ELSE
 chessmovex = 0
 chessmovey = 1
 GOTO 21
END SELECT
21
wchessx = bchessx + chessmovex: wchessy = bchessy + chessmovey
IF wchessx > 19 OR wchessx < 1 THEN GOTO 20 ELSE
IF wchessy > 19 OR wchessy < 1 THEN GOTO 20 ELSE
IF chess(wchessx - 1, wchessy - 1) = 0 THEN
 chess(wchessx - 1, wchessy - 1) = -1
 CIRCLE ((wchessx - 1) * 22 + 21, (wchessy - 1) * 22 + 19), 7, 7
 PAINT ((wchessx - 1) * 22 + 20, (wchessy - 1) * 22 + 20), 7
ELSE
 GOTO 20
END IF
chessno = -1: chessnox = wchessx - 1: chessnoy = wchessy - 1
GOSUB 100
GOTO 10
100
n = 1

101
chessfindx = 1: chessfindy = 1
IF chessnox + n * chessfindx = -1 OR chessnoy + n * chessfindy = 19 THEN GOTO 102
IF chessnoy + n * chessfindy = -1 OR chessnox + n * chessfindx = 19 THEN GOTO 102
IF chessno = chess(chessnox + n * chessfindx, chessnoy + n * chessfindy) THEN
 n = n + 1
 IF n = 5 THEN PRINT "You win!" ELSE
 GOTO 101
ELSE
n = 1
END IF

102
chessfindx = 1: chessfindy = 0
IF chessnox + n * chessfindx = -1 OR chessnoy + n * chessfindy = 19 THEN GOTO 103
IF chessnoy + n * chessfindy = -1 OR chessnox + n * chessfindx = 19 THEN GOTO 103
IF chessno = chess(chessnox + n * chessfindx, chessnoy + n * chessfindy) THEN
 n = n + 1
 IF n = 5 THEN PRINT "You win!" ELSE
 GOTO 102
ELSE
n = 1
END IF

103
chessfindx = 1: chessfindy = -1
IF chessnox + n * chessfindx = -1 OR chessnoy + n * chessfindy = 19 THEN GOTO 104
IF chessnoy + n * chessfindy = -1 OR chessnox + n * chessfindx = 19 THEN GOTO 104
IF chessno = chess(chessnox + n * chessfindx, chessnoy + n * chessfindy) THEN
 n = n + 1
 IF n = 5 THEN PRINT "You win!" ELSE
 GOTO 103
ELSE
n = 1
END IF

104
chessfindx = 0: chessfindy = -1
IF chessnox + n * chessfindx = -1 OR chessnoy + n * chessfindy = 19 THEN GOTO 105
IF chessnoy + n * chessfindy = -1 OR chessnox + n * chessfindx = 19 THEN GOTO 105
IF chessno = chess(chessnox + n * chessfindx, chessnoy + n * chessfindy) THEN
 n = n + 1
 IF n = 5 THEN PRINT "You win!" ELSE
 GOTO 104
ELSE
n = 1
END IF

105
chessfindx = -1: chessfindy = -1
IF chessnoy + n * chessfindy = -1 OR chessnox + n * chessfindx = 19 THEN GOTO 106
IF chessnox + n * chessfindx = -1 OR chessnoy + n * chessfindy = 19 THEN GOTO 106
IF chessno = chess(chessnox + n * chessfindx, chessnoy + n * chessfindy) THEN
 n = n + 1
 IF n = 5 THEN PRINT "You win!" ELSE
 GOTO 105
ELSE
n = 1
END IF

106
chessfindx = -1: chessfindy = 0
IF chessnox + n * chessfindx = -1 OR chessnoy + n * chessfindy = 19 THEN GOTO 107
IF chessnoy + n * chessfindy = -1 OR chessnox + n * chessfindx = 19 THEN GOTO 107
IF chessno = chess(chessnox + n * chessfindx, chessnoy + n * chessfindy) THEN
 n = n + 1
 IF n = 5 THEN PRINT "You win!" ELSE
 GOTO 106
ELSE
n = 1
END IF

107
chessfindx = -1: chessfindy = 1
IF chessnox + n * chessfindx = -1 OR chessnoy + n * chessfindy = 19 THEN GOTO 108
IF chessnoy + n * chessfindy = -1 OR chessnox + n * chessfindx = 19 THEN GOTO 108
IF chessno = chess(chessnox + n * chessfindx, chessnoy + n * chessfindy) THEN
 n = n + 1
 IF n = 5 THEN PRINT "You win!" ELSE
 GOTO 107
ELSE
n = 1
END IF

108
chessfindx = 0: chessfindy = 1
IF chessnox + n * chessfindx = -1 OR chessnoy + n * chessfindy = 19 THEN RETURN
IF chessnoy + n * chessfindy = -1 OR chessnox + n * chessfindx = 19 THEN RETURN
IF chessno = chess(chessnox + n * chessfindx, chessnoy + n * chessfindy) THEN
 n = n + 1
 IF n = 5 THEN PRINT "You win!" ELSE
 GOTO 108
ELSE
n = 1
END IF
RETURN
210
PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
bchessy = bchessy - 1
IF bchessy = 0 THEN bchessy = 1
PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
RETURN
220
PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
bchessx = bchessx - 1
IF bchessx = 0 THEN bchessx = 1
PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
RETURN
230
PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
bchessx = bchessx + 1
IF bchessx = 20 THEN bchessx = 19
PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
RETURN
240
PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
bchessy = bchessy + 1
IF bchessy = 20 THEN bchessy = 19
PUT ((bchessx - 1) * 22 + 13, (bchessy - 1) * 22 + 11), gbiao, XOR
RETURN

