10 REM Byte and nibble mode interface
20     REM PC to 8255 PPI
30     REM Reserve space for one 1-character string
40     STRING 3,1
50    SIZE=15
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
240   C=0
250    REM Addresses of PPI Ports A, B, C:
260   PA=0FC00H
270   PB=PA+1
280   PC=PA+2
290    REM Address of PPI's configuration port
300   PX=PA+3
310    REM Configure the 8255:
320    REM Port A = mode 1, input
330    REM Port B = mode 0, output
340    REM Extra Port C bits are inputs
350   XBY(PX)=0B9H
360    REM Initialize the status bits:
370   S3=1
380   S4=1
390   S5=1
400   S6=1
410   S7=0
420    GOSUB 800
430    REM read the control bits
440    GOSUB 900
450    REM Enable the 8255's receive-data interrupt (INTR)
460   XBY(PX)=9
470    REM Set the 8052's EX1 to level-triggered
480   TCON=TCON.AND.0FBH
490    ONEX1 2000
500    PRINT "waiting for data..."
510    DO 
520    REM watch for direction-change request, Port C, bit 1
530   C1OLD=C1
540    GOSUB 900
550    IF C1<>C1OLD THEN  GOSUB 1000
560    WHILE 1=1
570    END 
800    REM Set Status Bits
810   XBY(PX)=0AH+S7
820   DB=S3+S4*2+S5*4+S6*8
830   XBY(PB)=DB
840    RETURN 
900    REM Read Control Bits
910   DC=XBY(PC)
920   C0=(DC.AND.80H)/80H
930   C1=(DC.AND.40H)/40H
940   C2=DC.AND.1
950   C3=(DC.AND.2)/2
960    RETURN 
1000   PRINT "set direction"
1010   REM if direction = PC to peripheral, enable interrupt
1020   IF C1=1 THEN XBY(PX)=9 :  CLOCK 0 : S6=1 :  GOSUB 800
1030   REM if direction = peripheral to pc, send data
1040   IF C1=0 THEN XBY(PX)=8 :GOSUB 1200
1050   RETURN 
1200   REM write a byte in 2 nibbles to the PC
1210   REM restart program if transfer takes > 5  seconds
1220  TIME=0
1230   CLOCK 1
1240   ONTIME 5,10
1250   DO 
1260   REM get the byte to write
1270  D=B(C)
1280   REM get the first 4 bits to write to the status port
1290  S5=D.AND.1
1300  S4=(D.AND.2)/2
1310  S3=(D.AND.4)/4
1320  S7=(D.AND.8)/8
1330  S6=0
1340   GOSUB 800
1350   REM wait for PC to set C1=1
1360   DO  : gosub 900:  UNTIL C1=1
1370  S6=1
1380   GOSUB 800
1390   REM wait for PC to set C1=0
1400   DO  : gosub 900:  UNTIL C1=0
1410   REM get the second 4 bits to write to the status port
1420  S5=(D.AND.10H)/10H
1430  S4=(D.AND.20H)/20H
1440  S3=(D.AND.40H)/40H
1450  S7=(D.AND.80H)/80H
1460  S6=0
1470   GOSUB 800
1480   REM wait for PC to set C1=1
1490   DO  : gosub 900:  UNTIL C1=1
1500   REM set status bits
1510   IF C=SIZE THEN S3=1 : S5=1 : I=0 ELSE S3=0 : S5=0
1520  S6=1 : S7=0
1530   GOSUB 800
1540   REM unless it's the final byte, wait for C1=0
1550   IF S3=0 THEN  DO  : gosub 900 :  UNTIL C1=0
1560   REM Display the byte written
1570   PH0. XBY(C),C
1580  C=C+1
1590  TIME=0
1600   UNTIL C=SIZE+1
1610   PRINT "End" : C=0
1620   REM stop the clock
1630   CLOCK 0
1640   RETURN 
2000   REM on EX1, read data at Port A
2010  D=XBY(PA)
2020   PRINT CHR(D),
2030  A(C)=D
2040  C=C+1
2050   IF C=SIZE+1 THEN  PRINT  :  PRINT "End" : C=0
2060   RETI 
