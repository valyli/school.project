CLS
INPUT "a,b,c="; a, b, c
LET p = (a + b + c) / 2
LET s = SQR(p * (p - a) * (p - b) * (p - c))
PRINT "s="; s
END

