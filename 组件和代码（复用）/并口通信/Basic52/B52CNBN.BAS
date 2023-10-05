10 REM Compatibility, nibble, and byte mode interface
20     REM with negotiating
30    TIME=0
40     CLOCK 0
50     REM PC to 8255 PPI
60     REM Reserve space for one 1-character string
70     STRING 3,1
80    SIZE=15
90     DIM A(SIZE)
100    DIM B(SIZE)
110   B(0)=ASC(S)
120   B(1)=ASC(A)
130   B(2)=ASC(M)
140   B(3)=ASC(P)
150   B(4)=ASC(L)
160   B(5)=ASC(E)
170   B(6)=20H
180   B(7)=ASC(T)
190   B(8)=ASC(E)
200   B(9)=ASC(S)
210   B(0AH)=ASC(T)
220   B(0BH)=20H
230   B(0CH)=ASC(D)
240   B(0DH)=ASC(A)
250   B(0EH)=ASC(T)
260   B(0FH)=ASC(A)
270   C=0
280    REM Addresses of PPI Ports A, B, C:
290   PA=0FC00H
300   PB=PA+1
310   PC=PA+2
320    REM Address of PPI's configuration port
330   PX=PA+3
340    REM Configure the 8255:
350    REM Port A = mode 0, input
360    REM Port B = mode 0, output
370    REM Port C upper & lower = input
380   XBY(PX)=099H
390    REM Initialize the status bits:
400   S3=1
410   S4=1
420   S5=1
430   S6=1
440   S7=0
450   PB0=1
460    GOSUB 800
470    REM read the control bits
480    GOSUB 900
490    PRINT "waiting for data..."
500    DO 
510    GOSUB 900
520    REM If C3=1, negotiate mode
530    IF C3=1 THEN  GOSUB 1000
540    REM If C0=0, data received
550    IF C0=0 THEN  GOSUB 2000
560    WHILE 1=1
570    END 
800    REM Set Status, direction bits
810   DB=PB0+S3*8+S4*10H+S5*20H+S6*40H+S7*80H
820   XBY(PB)=DB
830    RETURN 
900    REM Read Control Bits
910   DC=XBY(PC)
920   C0=(DC.AND.1)
930   C1=(DC.AND.2)/2
940   C2=(DC.AND.4)/4
950   C3=(DC.AND.8)/8
960    RETURN 
1000   PRINT "negotiating"
1010  TIME=0
1020   CLOCK 1
1030   ONTIME 5,10
1040   REM read the extensibility byte
1050  EXB=XBY(PA)
1060  S3=1
1070  S4=1
1080  S5=1
1090  S6=0
1100   GOSUB 800
1110   DO 
1120   GOSUB 900
1130   UNTIL C1=1
1140  S3=0
1150   IF EXB=0 THEN S4=0
1160  S5=0
1170  S6=1
1180   GOSUB 800
1190   IF EXB=0 THEN  GOSUB 3000
1200   IF EXB=1 THEN  GOSUB 4000
1210   CLOCK 0
1220   RETURN 
2000   REM read data at Port A
2010  TIME=0
2020   CLOCK 1
2030   ONTIME 5,10
2040   DO 
2050   DO 
2060   GOSUB 900
2070   UNTIL C0=0
2080  S7=1
2090   GOSUB 800
2100  D=XBY(PA)
2110   PRINT CHR(D),
2120   DO 
2130   GOSUB 900
2140   UNTIL C0=1
2150  S7=0
2160   GOSUB 800
2170  A(C)=D
2180  C=C+1
2190   UNTIL C=SIZE+1
2200   PRINT 
2210   PRINT "End"
2220  C=0
2230   CLOCK 0
2240   RETURN 
3000   REM write a byte in 2 nibbles to the PC
3010   REM restart program if transfer takes > 5  seconds
3020  TIME=0
3030   CLOCK 1
3040   ONTIME 5,10
3050   DO 
3060   REM get the byte to write
3070  D=B(C)
3080   REM get the first 4 bits to write to the status port
3090  S5=D.AND.1
3100  S4=(D.AND.2)/2
3110  S3=(D.AND.4)/4
3120  S7=(D.AND.8)/8
3130  S6=0
3140   GOSUB 800
3150   REM wait for PC to set C1=1
3160   DO  :  GOSUB 900 :  UNTIL C1=1
3170  S6=1
3180   GOSUB 800
3190   REM wait for PC to set C1=0
3200   DO  :  GOSUB 900 :  UNTIL C1=0
3210   REM get the second 4 bits to write to the status port
3220  S5=(D.AND.10H)/10H
3230  S4=(D.AND.20H)/20H
3240  S3=(D.AND.40H)/40H
3250  S7=(D.AND.80H)/80H
3260  S6=0
3270   GOSUB 800
3280   REM wait for PC to set C1=1
3290   DO  :  GOSUB 900 :  UNTIL C1=1
3300   REM set status bits
3310   IF C=SIZE THEN S3=1 : S5=1 : I=0 ELSE S3=0 : S5=0
3320  S7=0
3330   GOSUB 800
3340  S6=1
3350   GOSUB 800
3360   REM unless it's the final byte, wait for C1=0
3370   IF S3=0 THEN  DO  :  GOSUB 900 :  UNTIL C1=0
3380   REM Display the byte written
3390   PH0. XBY(C),C
3400  C=C+1
3410  TIME=0
3420   UNTIL C=SIZE+1
3430   PRINT "End" : C=0
3440   REM stop the clock
3450   CLOCK 0
3460   RETURN 
4000   REM write data to Port A (byte mode)
4010   PRINT "byte mode"
4020   REM enable the data outputs, change Port A to output
4030  PB0=0
4040  XBY(PX)=89H
4050   GOSUB 800
4060  C=0
4070  TIME=0
4080   CLOCK 1
4090   ONTIME 5,10
4100   DO 
4110   DO 
4120   GOSUB 900
4130   UNTIL C1=0
4140  D=B(C)
4150   PRINT D
4160  XBY(PA)=D
4170  S6=0
4180   GOSUB 800
4190   DO 
4200   GOSUB 900
4210   UNTIL C1=1
4220   IF C=SIZE THEN S3=1 : S5=1
4230   GOSUB 800
4240  S6=1
4250   GOSUB 800
4260   REM unless it's the last byte, wait for c1=0
4270   IF S3=0 THEN  DO  :  GOSUB 900 :  UNTIL C1=0
4280  C=C+1
4290  TIME=0
4300   UNTIL C=SIZE+1
4310   PRINT "End"
4320  C=0
4330  S3=1
4340   GOSUB 5000
4350   CLOCK 0
4360   RETURN 
5000   REM return direction to pc to peripheral
5010   DO 
5020   GOSUB 900
5030   UNTIL C3=0
5040  S3=1
5050  S4=1
5060  S6=0
5070  S7=1
5080   GOSUB 800
5090   DO 
5100   GOSUB 900
5110   UNTIL C1=0
5120   REM disable data outputs, switch port A to input
5130  PB0=1
5140  XBY(PX)=99H
5150  S6=1
5160   GOSUB 800
5170   DO 
5180   GOSUB 900
5190   UNTIL C1=1
5200  S7=0
5210   GOSUB 800
5220   RETURN 
