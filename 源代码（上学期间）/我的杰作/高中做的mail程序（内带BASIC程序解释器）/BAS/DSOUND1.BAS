SCREEN 11, 2, 0
1 FOR i% = 440 TO 1000 STEP 10
p1: j = INT(SIN(i% / 100) * 200) + 200
PSET (i% - 439, 400 - j), 1
SOUND i%, i% / 1000
FOR delay% = 1 TO 100: NEXT delay%
NEXT i%
END



