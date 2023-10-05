10 REM Compatibility and Byte mode interface
20     REM PC to 8255 PPI
30     REM Reserve space for one 1-character string
40     STRING 3,1
50    SIZE=16
60     DIM A(SIZE)
70     DIM B(SIZE)
80    B(0)=ASC(S)
90    B(1)=ASC(A)
100   B(2)=ASC(M)
110   B(3)=ASC(P)
120   B(4)=ASC(L)
130   B(5)=ASC(E)
140   B(6)=20H
150   B(7)=ASC(T)
160   B(8)=ASC(E)
170   B(9)=ASC(S)
180   B(0AH)=ASC(T)
190   B(0BH)=20H
200   B(0CH)=ASC(D)
210   B(0DH)=ASC(A)
220   B(0EH)=ASC(T)
230   B(0FH)=ASC(A)
240    REM intitialize count
250   C=0
260    REM Addresses of PPI Ports A, B, C:
270   PA=0FC00H
280   PB=PA+1
290   PC=PA+2
300    REM Address of PPI's configuration port
310   PX=PA+3
320    REM Configure the 8255:
330    REM Port A = mode 2, bidirectional
340    REM Port B = mode 0, output
350    REM Extra Port C bits are inputs
360   XBY(PX)=0C9H
370    REM Initialize the status bits:
380   S3=1
390   S4=1
400   S5=1
410   S6=0
420   S7=0
430    REM set the status bits
440    GOSUB 1000
450    REM read the control bits
460    GOSUB 1100
470    REM Enable the 8255's receive-data interrupt (INTR)
480   XBY(PX)=9
490    REM disable the 8255's transmit-data interrupt
500   XBY(PX)=0CH
510    REM Set the 8052's EX1 to level-triggered
520   TCON=TCON.AND.0FBH
530   C3OLD=1
540    ONEX1 4000
550    PRINT "waiting for data..."
560    DO 
570    REM watch for direction-change request, Port C, bit 1
580   C3OLD=C3
590    GOSUB 1100
600    IF C3<>C3OLD THEN XBY(PX)=8 : XBY(PX)=0CH :  GOSUB 2000
610    WHILE 1=1
620    END 
1000   REM Set Status Bits
1010  XBY(PX)=0AH+S7
1020  XBY(PX)=0CH+S6
1030  DB=S3+S4*2+S5*4
1040  XBY(PB)=DB
1050   RETURN 
1100   REM Read Control Bits
1110  DC=XBY(PC)
1120  C0=(DC.AND.10H)/10H
1130  C1=(DC.AND.40H)/40H
1140  C2=DC.AND.1
1150  C3=(DC.AND.2)/2
1160   RETURN 
2000   PRINT "set direction"
2010  IE=IE.AND.0FBH
2020   REM set interrupt enables, transceiver direction
2030   REM  direction switch
2040  C=0
2050   IF C3=1 THEN  GOSUB 2100 ELSE  GOSUB 2200
2060   RETURN 
2100  XBY(PX)=0CH
2110   CLOCK 0
2120  S3=1
2130  S6=0
2140  S7=1
2150   GOSUB 1000
2160   PRINT  :  PRINT "direction = pc to ppi"
2170   ONEX1 4000
2180  XBY(PX)=9
2190   RETURN 
2200  XBY(PX)=8
2210  S3=0
2220  S6=1
2230   GOSUB 1000
2240   PRINT  :  PRINT "direction = PPI to PC"
2250   ONEX1 3000
2260  XBY(PX)=0DH
2270   RETURN 
3000   REM write a byte to the PC
3010   REM restart program if transfer takes > 5  seconds
3020  TIME=0
3030   CLOCK 1
3040   ONTIME 5,10
3060   REM write the byte
3070  XBY(PA)=B(C)
3080   REM Display the byte written
3090   PH0. C,CHR(B(C))
3100  C=C+1
3110  TIME=0
3120   REM if it's the last byte,
3130   REM disable the interrupt, set the direction
3140   IF C=SIZE-1 THEN XBY(PX)=0CH :  CLOCK 0 : S3=1 :  GOSUB 1000
3150   RETI 
4000   REM on EX1, read data at Port A
4010  D=XBY(PA)
4020   PRINT CHR(D),
4030  A(C)=D
4040  C=C+1
4050   IF C=SIZE THEN  PRINT  : C=0
4060   RETI 
