CLS : DIM C(8192): RANDOMIZE TIMER: a = 1: B = 1: a1 = 1: b1 = 1: ON TIMER(1) GOSUB 300: TIMER ON
10 SCREEN 12: COLOR 10: l1 = 1: l2 = 3: l3 = 4
PRINT " I want to sleep !"
PRINT "I must to sleep now !"
GET (0, 0)-(165, 32), C
CLS
COLOR 6: LOCATE 15, 23: PRINT "****** I'm ready to sleep ! ******": COLOR 10
GOSUB 400
CLS
20 GOSUB 500: O = 0: q = 8: w = 8: e = 8: GOSUB 600
DO WHILE INKEY$ = ""
    O = O + 1
    x = FIX(RND * 640) + 1
    y = FIX(RND * 480) + 1
    CIRCLE (x + 50, y + 5), q, l1': PAINT (x + 50, y + 5), l1
    CIRCLE (x - 29, y + 56), w, l2': PAINT (x - 29, y + 56), l2
    CIRCLE (x + 12, y - 30), e, l3': PAINT (x + 12, y - 30), l3
    GOSUB 100
    IF O > 600 THEN
    O = 0
    CLS
    GOTO 20
    END IF
LOOP
GOSUB 200
50 PLAY OFF
   SYSTEM
100
a = a + a1: B = B + b1
IF a <= 0 OR a >= 469 THEN a1 = -a1
IF B <= 0 OR B >= 419 THEN b1 = -b1
PUT (a, B), C, XOR
FOR I = 1 TO 500
NEXT I
PUT (a, B), C, XOR
RETURN
200
COLOR 14
LOCATE 14, 27: PRINT "************************"
PRINT
LOCATE 15, 27: PRINT "* I am waking up now ! *"
PRINT
LOCATE 16, 27: PRINT "************************"
LOCATE 28, 1: PRINT "If you want let me work , please ---     "
RETURN
300
COLOR 7
LOCATE 1, 73
ti = TIMER
IF INT(ti / 3600) = ti / 3600 THEN GOSUB 400 ELSE
a$ = TIME$
PRINT a$
COLOR 11
RETURN
400
FOR I = 1 TO 3
SOUND 800, 10: SLEEP 1
FOR j = 1 TO 10000
NEXT j
NEXT I
SOUND 1500, 10
RETURN
500
COLOR 7
CLS
LOCATE 1, 1
PRINT " Volume in drive C is DISK1 Volume Serial Number is D959-269B"
PRINT " Directory of C:\UCDICT"
PRINT
PRINT ".            <DIR>       08-08-97  12:54p"
PRINT "..           <DIR>       08-08-97  12:54p"
PRINT "EC       LOG       2,215 05-30-98   6:33p"
PRINT "UCDICT   INI         377 05-30-98   6:33p"
PRINT "CALENDER EXE      11,456 09-25-96  12:13p"
PRINT "CE       DAT   1,343,488 09-25-96  12:13p"
PRINT "CE       IDX       2,528 09-25-96  12:13p"
PRINT "EC       DAT   2,723,840 09-25-96  12:13p"
PRINT "EC       IDX       6,684 09-25-96  12:13p"
PRINT "GROUP    EXE       8,224 09-25-96  12:13p"
PRINT "HISBROW  EXE      40,288 09-25-96  12:13p"
PRINT "HOOKWORD DLL       4,448 09-25-96  12:13p"
PRINT "INSTALL  INF         464 09-25-96  12:13p"
PRINT "MINE     EXE      11,056 09-25-96  12:13p"
PRINT "README   TXT       4,343 09-25-96  12:13p"
PRINT "SAVEWORD DLL      20,256 09-25-96  12:13p"
PRINT "SYSDICT  EXE      11,168 09-25-96  12:13p"
PRINT "UCDICT   EXE     111,136 09-25-96  12:13p"
PRINT "UCDICT   OVL      40,520 09-25-96  12:13p"
PRINT "UCDICT16 FNT     261,696 09-25-96  12:13p"
PRINT "USER     DIC         186 09-25-96  12:13p"
PRINT "USRDICT  EXE       5,040 09-25-96  12:13p"
PRINT "CE       LOG           0 08-19-97   6:04p"
PRINT "NF       LOG          96 09-15-97  10:48p"
PRINT "       24 file(s)    4,609,509 bytes"
PRINT "                   263,749,632 bytes free"
COLOR 10
RETURN
600
PLAY "MB MLO2G3A6O3C6D6E6G6A1A6O4C3O3A6G6E6G3A6O4C3O3A6G6E6G3A6O4C3O3A6"   'G6E6G6A6E1E6"'G3E6D6C6D3E6G3E6E6C6D3E6G3E6D6C6O2G6A6O3C1C6D3E6A6G6E6E6A6O4C3O3G6A3A6O4C4O3G3B6A3G3E12E1D6E6G6D6E3G6E3
RETURN



