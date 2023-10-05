10 CLS
20 SCREEN 1: O = 0
30 RANDOMIZE TIMER: O = O + 1
    X = FIX(RND * 300) + 2
    Y = FIX(RND * 300) + 2
    CIRCLE (X + 50, Y + 5), 8, 2: PAINT (X + 50, Y + 5), 2
    FOR S = 1 TO 500
     E = E * 50
    NEXT S
    CIRCLE (X - 29, Y + 56), 6, 3: PAINT (X - 29, Y + 56), 3
    FOR T = 1 TO 500
     J = J * 50
    NEXT T
    CIRCLE (X + 12, Y - 30), 10, 1: PAINT (X + 12, Y - 30), 1
    FOR Z = 1 TO 500
     U = U * 50
    NEXT Z
    IF O > 250 THEN
    O = 0
    CLS
    END IF
    K$ = INKEY$: IF K$ = CHR$(27) THEN END
50 GOTO 30
60 END


