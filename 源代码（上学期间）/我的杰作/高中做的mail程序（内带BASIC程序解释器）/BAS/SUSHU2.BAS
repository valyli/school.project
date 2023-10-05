'求1到100中的素数
CLS
FOR x = 1 TO 100
 FOR i = 2 TO x - 1
  IF x MOD i = 0 THEN GOTO 10
 NEXT i
 PRINT x,
10 NEXT x

