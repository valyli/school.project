OPEN "cmos.dat" FOR INPUT AS #1
FOR i% = 0 TO 127
 OUT &H70, i%
 INPUT #1, a%
 OUT &H71, a%
NEXT i%
CLOSE #1
END

