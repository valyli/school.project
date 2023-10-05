10 REM ECP mode interface
20     REM PC to 8255 PPI
30     REM Reserve space for one 1-character string
40     STRING 3,1
50    SIZE=31
60     DIM A(SIZE)
70     DIM B(SIZE)
80    B(0)=ASC(S)
81    B(1)=ASC(A)
82    B(2)=ASC(M)
83    B(3)=ASC(P)
84    B(4)=ASC(L)
85    B(5)=ASC(E)
86    B(6)=20H
87    B(7)=ASC(T)
88    B(8)=ASC(E)
89    B(9)=ASC(S)
90    B(0AH)=ASC(T)
91    B(0BH)=20H
92    B(0CH)=ASC(#)
93    B(0DH)=ASC(1)
94    B(0EH)=20H
95    B(0FH)=20H
96    B(10H)=ASC(S)
97    B(11H)=ASC(A)
98    B(12H)=ASC(M)
99    B(13H)=ASC(P)
100   B(14H)=ASC(L)
101   B(15H)=ASC(E)
102   B(16H)=20H
103   B(17H)=ASC(T)
104   B(18H)=ASC(E)
105   B(19H)=ASC(S)
106   B(1AH)=ASC(T)
107   B(1BH)=20H
108   B(1CH)=ASC(#)
109   B(1DH)=ASC(2)
110   B(1EH)=20H
111   B(1FH)=20H
240   C=0
250    REM Addresses of PPI Ports A, B, C:
260   PA=0FC00H
270   PB=PA+1
280   PC=PA+2
290    REM Address of PPI's configuration port
300   PX=PA+3
310    REM Configure the 8255:
320    REM Port A = mode 0, input
330    REM Port B = mode 0, output
340    REM Port C, upper and lower, input
350   XBY(PX)=099H
360    REM Initialize the status bits:
370   S3=0
380   S4=1
390   S5=1
400   S6=1
410   S7=0
420    REM B0 is direction-control
430    REM initial direction is PC to peripheral
440   B0=1
450    GOSUB 800
460    REM read the control bits
470    GOSUB 900
480    GOSUB 1600
490    REM watch for c0=0 or c2=0
500    PRINT "waiting for data..."
510    DO 
520    GOSUB 900
530    IF C2=0 THEN  GOSUB 1000
540    IF C0=0 THEN  GOSUB 2000
550    WHILE 1=1
560    END 
800    REM Set Status Bits, direction
810   DB=B0+S3*8+S4*10H+S5*20H+S6*40H+S7*80H
820   XBY(PB)=DB
830    RETURN 
900    REM Read Control Bits
910   DC=XBY(PC)
920   C0=DC.AND.1
930   C1=(DC.AND.2)/2
940   C2=(DC.AND.4)/4
950   C3=(DC.AND.8)/8
960    RETURN 
1000   REM switch direction to peripheral-to-PC
1010   REM S7 is -command/data select
1020  S3=0
1030  S6=0
1040  S7=1
1050  B0=0
1060   GOSUB 800
1070   REM port A is output
1080  XBY(PX)=89H
1090   CLOCK 0
1100   REM write bytes
1110   DO 
1120   REM write a byte to the PC
1130   REM restart program if transfer takes > 5  seconds
1140  TIME=0
1150   REM clock 1
1160   REM ontime 5,10
1170   DO 
1180   REM get the byte to write to Port A
1190  D=B(C)
1200  XBY(PA)=D
1210  S6=0
1220  S7=1
1230   GOSUB 800
1240   REM Display the byte written
1250   PH0. XBY(C),C
1260   REM complete the handshake
1270  C=C+1
1280   DO 
1290   GOSUB 900
1300   UNTIL C1=1
1310  S6=1
1320   GOSUB 800
1330   DO 
1340   GOSUB 900
1350   UNTIL C1=0
1360  TIME=0
1370   UNTIL (C=SIZE+1).OR.(C2=1)
1380  C=0
1390   PRINT "end"
1400   REM when C2=1, switch back to PC-to-peripheral
1410   DO 
1420   GOSUB 900
1430   UNTIL C2=1
1440   GOSUB 1600
1450   RETURN 
1600   CLOCK 0
1610   REM Port A is input
1620  XBY(PX)=99H
1630  S7=0
1640  S6=1
1650  S3=1
1660  B0=1
1670   GOSUB 800
1680   RETURN 
2000   REM on C0=0, read data at Port A
2010  S7=1
2020   GOSUB 800
2030   DO 
2040   GOSUB 900
2050   UNTIL C0=1
2060   REM read the data
2070  D=XBY(PA)
2080   PRINT CHR(D),
2090  A(C)=D
2100  C=C+1
2110   IF C=SIZE+1 THEN  PRINT  :  PRINT "End" : C=0
2120  S7=0
2130   GOSUB 800
2140   RETURN 
