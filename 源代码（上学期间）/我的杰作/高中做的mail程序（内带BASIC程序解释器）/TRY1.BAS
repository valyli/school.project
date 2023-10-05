REM zz.bas
x = 15999
DIM cb(1 TO x)
SCREEN 12
LINE (53, 70)-(365, 300), 2, BF
PRINT CHR$(14); "[{-150|130@22,22=2(1)2欢迎您使用}]"
PRINT CHR$(14); "[{-60|180@35,35=3(9)质量管理工具软件}]"
PRINT CHR$(14); "[{-170|230@20,20=3(4)张和据 1995.6}]"
GET (55, 100)-(362, 270), cb
DEF SEG = VARSEG(cb(1))
BSAVE "tx.grh", VARPTR(cb(1)), 15000 * 2
DEF SEG
CLS
REM dy.bas
x = 15999
REDIM cb(1 TO x): tm = TIMER: qw = 15 + TIMER
SCREEN 12
DIM row$(1 TO 4)
row$(1) = CHR$(&HC3) + CHR$(&H3C) + CHR$(&HFF) + CHR$(&H3C)
row$(2) = row$(1)
row$(3) = CHR$(&H3C) + CHR$(&H3C) + CHR$(&HFF) + CHR$(&HC3)
row$(4) = row$(3)
FOR i = 1 TO 4
tile$ = tile$ + row$(i)
NEXT i
LINE (0, 0)-(639, 449), b
PAINT (10, 20), tile$
LINE (160, 40)-(550, 290), 11, BF
LINE (401, 354)-(514, 384), 7, BF
LINE (403, 356)-(510, 382), 8, BF
LINE (405, 360)-(510, 382), 15, BF
LINE (405, 359)-(508, 380), 7, BF
DEF SEG = VARSEG(cb(1))
BLOAD "tx.grh", VARPTR(cb(1))
DEF SEG
PUT (200, 80), cb
LINE (206, 251)-(516, 258), 8, BF
LINE (508, 86)-(516, 257), 8, BF
k$ = INKEY$
DO WHILE k$ = ""
k$ = INKEY$
IF qm = 0 THEN qn = TIMER
qc = INT((qw - TIMER) * 100) / 100
qm = qm + 1
IF TIMER >= qn + 1 THEN
ke = ke + 1
LINE (430, 367)-(440, 375), ke, BF: qm = 0
LINE (456, 367)-(466, 375), ke + 1, BF
LINE (476, 367)-(486, 375), ke + 2, BF
END IF
IF ke >= 16 THEN ke = 0
IF qc <= 0 THEN SCREEN 0: CLS : END
LOOP

