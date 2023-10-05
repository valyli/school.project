IF chessmove < .125 THEN
 chessmovex = 1
 chessmovey = 1
 GOTO 21
ELSE
END IF
IF chessmove >= .125 AND chessmove < .25 THEN
 chessmovex = 1
 chessmovey = 0
 GOTO 21
ELSE
END IF
IF chessmove >= .25 AND chessmove < .375 THEN
 chessmovex = 0
 chessmovey = 1
 GOTO 21
ELSE
END IF
IF chessmove >= .375 AND chessmove < .5 THEN
 chessmovex = 1
 chessmovey = -1
 GOTO 21
ELSE
END IF
IF chessmove >= .5 AND chessmove < .625 THEN
 chessmovex = -1
 chessmovey = 1
 GOTO 21
ELSE
END IF
IF chessmove >= .625 AND chessmove < .75 THEN
 chessmovex = 0
 chessmovey = -1
 GOTO 21
ELSE
END IF
IF chessmove >= .75 AND chessmove < .875 THEN
 chessmovex = -1
 chessmovey = 0
 GOTO 21
ELSE
END IF
IF chessmove >= .875 AND chessmove < 1 THEN
 chessmovex = -1
 chessmovey = -1
 GOTO 21
ELSE
END IF

