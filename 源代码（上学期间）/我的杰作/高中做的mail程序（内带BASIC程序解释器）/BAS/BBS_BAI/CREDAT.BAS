FOR i = 97 TO 122
OPEN "m:\bbs\dat\" + CHR$(i) + ".dat" FOR OUTPUT AS #1
WRITE #1, " "
CLOSE
NEXT i
SYSTEM




