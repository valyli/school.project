'Lockfile
INPUT "Filename"; f$
OPEN f$ FOR RANDOM AS #1 LEN = 1
FIELD #1, 1 AS a$
bot = LOF(1)
FOR i = 1 TO bot
GET #1, i
LSET a$ = CHR$(ASC(a$) + 1)
PUT #1, i
NEXT i
CLOSE #1
END







