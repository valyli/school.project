SCREEN 12: KEY OFF: CLS
KEY(3) ON
ON KEY(3) GOSUB endd
RANDOMIZE TIMER
FOR workcolor = 1 TO 25000
VIEW (70, 70)-(610, 410), 8, 1
VIEW (50, 50)-(590, 390), I, 4'workcolor,4
LOCATE 12, 26: COLOR 15: PRINT "LI JIA SHE JI"
 red = INT(RND * 63)
 green = INT(RND * 63)
 blue = INT(RND * 63)
 K = red MOD 16
 PALETTE 8, 0
 PALETTE K, 65536 * blue + 256 * green + red
 LOCATE 24, 18: COLOR 15
 PRINT "red="; red; "green="; green; "blue="; blue
 DO WHILE INKEY$ = "": LOOP
 NEXT
endd:
VIEW (50, 50)-(590, 390), 0, 4
PALETTE 0, 65535 * 10 + 256 * 41 + 50
LOCATE 8, 18: PRINT "Your sclected color is:"
LOCATE 10, 18: PRINT "red="; red; "green="; green; "blue="; blue
END

