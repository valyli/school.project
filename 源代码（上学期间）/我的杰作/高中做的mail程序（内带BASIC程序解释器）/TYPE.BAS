10
CLS
COLOR 9
LOCATE 13, 25: PRINT "1.Ð¡Ð´×ÖÄ¸"
LOCATE 14, 25: PRINT "2.´óÐ¡Ð´×ÖÄ¸"
LOCATE 15, 25: PRINT "3.´óÐ¡Ð´×ÖÄ¸ÓëÊý×Ö"
LOCATE 16, 25: PRINT "4.ËùÓÐ·ûºÅ¼ü"
11
LOCATE 11, 20: INPUT "ÇëÊäÈë´ò×Ö·¶Î§: ", howmanyword$
howmanyword = VAL(howmanyword$)
IF howmanyword < 1 OR howmanyword > 4 THEN GOTO 11 ELSE
IF howmanyword$ = "1" THEN
 downland1 = 26
 topland1 = 97
 downland2 = 0
 topland2 = 96
 downland3 = 123
 topland3 = 255
ELSE
END IF
IF howmanyword$ = "2" THEN
 downland1 = 58
 topland1 = 65
 downland2 = 91
 topland2 = 96
 downland3 = 91
 topland3 = 96
ELSE
END IF
IF howmanyword$ = "3" THEN
 downland1 = 75
 topland1 = 48
 downland2 = 58
 topland2 = 64
 downland3 = 91
 topland3 = 96
ELSE
END IF
IF howmanyword$ = "4" THEN
 downland1 = 94
 topland1 = 33
 downland2 = 0
 topland2 = 32
 downland2 = 127
 topland2 = 255
ELSE
END IF
12
CLS
LOCATE 15, 30: INPUT "´ò×ÖËÙ¶È (1-9):", speed$
speed = VAL(speed$)
IF speed < 1 OR speed > 9 THEN GOTO 12
speed = (10 - speed) * 2500
winno = 0: wordno = 0
usetime1 = TIMER
CLS
COLOR 6
LOCATE 19, 30: PRINT "**************"
LOCATE 20, 30: PRINT "*  ´ò×ÖÓÎÏ·  *"
LOCATE 21, 30: PRINT "**************"
LOCATE 3, 1: PRINT "_______________________________________________________________________________"
LOCATE 16, 1: PRINT "_______________________________________________________________________________"
COLOR 7
LOCATE 1, 30: PRINT "ÃüÖÐ: 0 ¸ö"
20
VIEW PRINT 4 TO 15
CLS                         '2#->1#
RANDOMIZE TIMER
21
a = INT(RND * downland1 + topland1)
IF a >= downland2 AND a <= topland2 THEN GOTO 21 ELSE
IF a >= downland3 AND a <= topland3 THEN GOTO 21 ELSE

a$ = CHR$(a)
x = INT(RND * 77 + 3)
wordno = wordno + 1
FOR y = 5 TO 14 STEP 1         '4->5
CLS
LOCATE y, x: PRINT a$
 usetime2 = TIMER - usetime1
 VIEW PRINT 1 TO 2
 CLS
 LOCATE 1, 35: PRINT "ÃüÖÐ: "; winno; "¸ö"
 LOCATE 1, 65: PRINT "Ê±¼ä: "; INT(10 * usetime2) / 10; "Ãë"
 LOCATE 1, 1: PRINT "×ÜµÄÏÂÂä×Ö·ûÊý: "; wordno; "¸ö"
 VIEW PRINT 4 TO 15
FOR n = 1 TO speed
 play$ = INKEY$
 IF play$ = a$ THEN GOTO 22
 IF play$ = CHR$(27) THEN GOTO 100
NEXT n
NEXT y
GOTO 20
22
COLOR 14
FOR killy = 14 TO y STEP -1
LOCATE killy, x: PRINT "|"
FOR z = 1 TO 200
NEXT z
NEXT killy
COLOR 15
LOCATE killy, x + 1: PRINT "Û"
LOCATE killy, x: PRINT "Û"
LOCATE killy, x - 1: PRINT "Û"
COLOR 7
FOR t = 1 TO 2500
NEXT t
SOUND 6000, .1
SOUND 5500, .1
SOUND 5000, .1
SOUND 4500, .1
SOUND 4000, .1
winno = winno + 1
VIEW PRINT 1 TO 2
CLS
LOCATE 1, 35: PRINT "ÃüÖÐ: "; winno; "¸ö"
GOTO 20
100
CLS
LOCATE 13, 25: PRINT "ÃüÖÐÂÊ: "; INT(10000 * winno / wordno) / 100; "%"
LOCATE 14, 25: PRINT "´ò×ÖËÙ¶È (Ö»ËãÃüÖÐµÄ): "; FIX(winno * 60 / usetime2); "¸ö/·Ö"
LOCATE 15, 25: PRINT "´ò×Ö³É¼¨ :"; FIX((((10000 * winno / wordno) / 100) * (winno * 60 / usetime2)) / 100); "·Ö"
END

