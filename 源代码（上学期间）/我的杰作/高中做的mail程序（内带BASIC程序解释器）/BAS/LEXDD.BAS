CLS
SCREEN 1
COLOR 1, 4
PRINT " "
PRINT "        * -------* LEXDD *-------*"
PRINT " "
PRINT "          Welcome listening music       "
PRINT "            The music name:LEXDD"
LINE (160, 80)-(290, 180), 1, B
CIRCLE (230, 150), 45, 1, , , 1 / 3
LINE (185, 150)-(205, 105), 1
LINE (275, 150)-(255, 105), 1
CIRCLE (230, 105), 25, 1, , , 1 / 3
CIRCLE (230, 150), 15, 1, , , 3 / 1
FOR K = 1 TO 2
IF K = 1 THEN
  PRINT " "
  PRINT "Please listen me on First!"
ELSE
  PRINT " "
  PRINT "Please sing the song with me!"
END IF
PLAY " mn l8 t145 "
PLAY "o2d d b a g d4. d16 d16 d b a g e4 e"
PLAY "e o 3d o2b a e4.e o3d d c o2a b4 g d"
PLAY "D B A G D4. D D B A G E4. E"
PLAY "e o3c o2b a o3d d d d e d c o2a g4. p8"
PLAY "b b b4 b b b4 b o3d o2g. a16 b2"
PLAY "o3c c c. c16 c o2b b b16 b a a g a4 o3d4"
PLAY "o2b b b4 b b b4 b o3d o2g. a16 b2"
PLAY "o3c c c. c16 c o2b b b16 o3d d c o2a g4."
NEXT
PRINT "How is it ?"
PRINT "1.Good  2.Bad (1 or 2)"
INPUT "Answered-"; Q
FOR i = 1 TO 10
PRINT " "
NEXT i
IF Q = 1 THEN
  PRINT "Thank you for your listen!"
ELSE
  COLOR 0, F
  PRINT "You are FOOL!"
END IF
END



