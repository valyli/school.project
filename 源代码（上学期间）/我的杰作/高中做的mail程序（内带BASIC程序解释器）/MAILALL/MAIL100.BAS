ON KEY(1) GOSUB 1000
ON TIMER(2) GOSUB 2000
ON TIMER(1) GOSUB 2500
path1$ = "m:\����\": path2$ = "m:\����\mailbox\"
CLS
COLOR 15
LOCATE 8, 21: PRINT "*************************************"
LOCATE 9, 21: PRINT "|                                   |"
LOCATE 11, 21: PRINT "|                                   |"
LOCATE 13, 21: PRINT "|                                   |"
LOCATE 15, 21: PRINT "|                                   |"
LOCATE 17, 21: PRINT "|                                   |"
LOCATE 10, 21: PRINT "|               MAIL                |"
LOCATE 12, 21: PRINT "|           Version 1.00            |"
LOCATE 14, 21: PRINT "|         96���־��  ���          |"
LOCATE 16, 21: PRINT "|              1998.8               |"
LOCATE 18, 21: PRINT "*************************************"
DO
LOOP UNTIL INKEY$ <> ""
OPEN path1$ + "caleno.dat" FOR INPUT AS #1
INPUT #1, Caleno
CLOSE #1
OPEN path1$ + "caleno.dat" FOR OUTPUT AS #1
WRITE #1, Caleno + 1
CLOSE #1
10 CLS : COLOR 14
TIMER ON: KEY(1) ON: LOCATE 23, 63: PRINT "[ ������: "; Caleno; "]"
LOCATE 9, 27: PRINT "|                        |"
LOCATE 10, 27: PRINT "|    <1>   �����ʼ�      |"
LOCATE 11, 27: PRINT "|------------------------|"
LOCATE 12, 27: PRINT "|    <2>   ���ӹ�����    |"
LOCATE 13, 27: PRINT "|------------------------|"
LOCATE 14, 27: PRINT "|    <3>   ������        |"
LOCATE 15, 27: PRINT "|------------------------|"
LOCATE 16, 27: PRINT "|   <ESC>  �˳�          |"
LOCATE 17, 27: PRINT "|                        |"
LOCATE 8, 27: PRINT "**************************"
LOCATE 18, 27: PRINT "**************************"
LOCATE 21, 28: PRINT "* <F1> ������ʹ�ð��� *"
DO
choose$ = INKEY$
IF choose$ = CHR$(49) THEN
 TIMER OFF: KEY(1) OFF
 GOSUB 20
 END IF
IF choose$ = CHR$(50) THEN
 TIMER OFF: KEY(1) OFF
 GOSUB 200
 END IF
IF choose$ = CHR$(51) THEN
 TIMER OFF: KEY(1) OFF
 GOSUB 300
 END IF
IF choose$ = CHR$(27) THEN
 COLOR 0
 SYSTEM
END IF
LOOP
20
CLS : COLOR 2: CLS
LOCATE 9, 26: PRINT "************************"
LOCATE 10, 26: PRINT "*                      *"
LOCATE 11, 26: PRINT "*  <1> �ż�����뷢��  *"
LOCATE 12, 26: PRINT "*                      *"
LOCATE 13, 26: PRINT "*  <2> ���û�ע������  *"
LOCATE 14, 26: PRINT "*                      *"
LOCATE 15, 26: PRINT "************************"
DO
choose$ = INKEY$
IF choose$ = CHR$(49) THEN GOSUB 30
IF choose$ = CHR$(50) THEN GOSUB 90
IF choose$ = CHR$(27) THEN GOTO 10
LOOP
30
CLS
n = 1
COLOR 15: LOCATE 13, 21: PRINT "-----------------------------------"
LOCATE 16, 21: PRINT "-----------------------------------"
LOCATE 14, 21: PRINT "|                                 |"
LOCATE 15, 21: PRINT "|                                 |"
COLOR 8: LOCATE 14, 23: LINE INPUT "��վע����:", tryname$
LOCATE 15, 29: LINE INPUT "����:", trypassword$
OPEN path1$ + "mailname.dat" FOR INPUT AS #1
DO
INPUT #1, name$
INPUT #1, password$
INPUT #1, mailno$
IF tryname$ = name$ AND trypassword$ = password$ THEN
 CLOSE #1
 GOTO 40
END IF
LOOP UNTIL EOF(1) = -1
CLOSE #1
COLOR 12
LOCATE 21, 2: PRINT "!! ����: �����ע��������!"
LOCATE 22, 2: COLOR 7: INPUT "?? �Ƿ�����(Y/N)", answere$: COLOR 8
IF answere$ = "y" OR answere$ = "Y" THEN GOTO 30
IF answere$ = "n" OR answere$ = "N" THEN GOTO 10
GOTO 30
40
VIEW PRINT
CLS :  COLOR 2
LOCATE 11, 30: PRINT "***************"
LOCATE 12, 30: PRINT "*             *"
LOCATE 13, 30: PRINT "*  <1> ����   *"
LOCATE 14, 30: PRINT "*             *"
LOCATE 15, 30: PRINT "*  <2> ����   *"
LOCATE 16, 30: PRINT "*             *"
LOCATE 17, 30: PRINT "***************"
DO
choose$ = INKEY$
IF choose$ = CHR$(49) THEN GOSUB 50
IF choose$ = CHR$(50) THEN GOSUB 60
IF choose$ = CHR$(27) THEN GOSUB 10
LOOP
50
VIEW PRINT
CLS
COLOR 2
LOCATE 1, 33: PRINT " MAIL���� "
LOCATE 2, 29: PRINT "__________________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 22, 1: PRINT ">> ��������Զ���ҳ,<ESC>�˳�"
LOCATE 23, 1: PRINT "!! ��<Backspace>��ɾ�������ż�"
VIEW PRINT 4 TO 19
DO
OPEN path2$ + LTRIM$(mailno$) FOR INPUT AS #1
DO
INPUT #1, letter$
PRINT letter$
IF letter$ = "  ****************************************************************************" THEN
DO
 a$ = INKEY$
 FOR i = 1 TO 100
  IF a$ = CHR$(27) THEN
   CLOSE #1
   VIEW PRINT
   GOTO 40
  END IF
  IF a$ = CHR$(8) THEN
   VIEW PRINT 21 TO 23
   CLS
   LOCATE 21, 2: COLOR 12: PRINT "!! ����: �㽫ɾ�������������ż�!"
   LOCATE 22, 2: COLOR 7: INPUT "?? ���Ҫɾ���� (Y/N)", answere$: COLOR 2
   IF answere$ = "y" OR answere$ = "Y" THEN
    CLOSE #1
    SHELL "del " + path2$ + LTRIM$(mailno$)
    SHELL "copy publis.dat " + path2$ + LTRIM$(mailno$)
    CLS
    VIEW PRINT 4 TO 19
    CLS
    LOCATE 15, 27: PRINT " ��ɾ�����,�����������"
    DO
    LOOP UNTIL INKEY$ <> ""
    GOTO 40
   ELSE
    CLOSE #1
    GOTO 50
   END IF
  END IF
 NEXT i
LOOP UNTIL a$ <> "" AND a$ <> CHR$(27)
END IF
LOOP UNTIL EOF(1) = -1
CLOSE #1
LOOP
RETURN
60
CLS
LOCATE 1, 32: PRINT "MAIL��ֽ"
LOCATE 2, 29: PRINT "______________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
VIEW PRINT 4 TO 19
LINE INPUT " <��Ҫ����>  ", mainabout$
LINE INPUT " <����>  ", mainletter$
70
CLS
LOCATE 19, 1: LINE INPUT " <������>  ", riceveaddress$
IF riceveaddress$ = "" THEN
 VIEW PRINT 21 TO 22
 LOCATE 21, 2: PRINT "û�е�ַ!"
 LOCATE 22, 2: INPUT "�Ƿ������������ż�? (Y/N)", answere$
 IF answere$ = "y" OR answere$ = "Y" THEN GOTO 40
 IF answere$ = "n" OR answere$ = "N" THEN
  CLS
  VIEW PRINT 4 TO 19
  CLS
  GOTO 70
 END IF
END IF
OPEN path1$ + "mailname.dat" FOR INPUT AS #1
DO
INPUT #1, hopename$
IF riceveaddress$ = hopename$ THEN GOTO 80
INPUT #1, nothing$
INPUT #1, nothing$
LOOP UNTIL EOF(1) = -1
VIEW PRINT 21 TO 22
LOCATE 21, 2: PRINT ">> û�������ַ! �������������ȷ��ַ"
CLOSE #1
DO
LOOP UNTIL INKEY$ <> ""
CLS
VIEW PRINT 4 TO 19
CLS
GOTO 70
80
INPUT #1, nothing$
INPUT #1, riceveno$
CLOSE #1
OPEN path2$ + LTRIM$(riceveno$) FOR APPEND AS #1
WRITE #1, " <�����˵�ַ>  " + name$
WRITE #1, " <��Ҫ����>  " + mainabout$
WRITE #1, " <����>  " + mainletter$
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
WRITE #1, "  ****************************************************************************"
CLOSE #1
CLS
VIEW PRINT
LOCATE 12, 27: PRINT " ���Ժ�! ���ڷ���........"
FOR l = 1 TO 50000: NEXT l
LOCATE 12, 27: PRINT " �ѷ������  �����������"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 40
RETURN
90
CLS
PRINT
LINE INPUT " <����> ", realname$
LINE INPUT " <�Ա�> ", sex$
LINE INPUT " <����> ", nation$
LINE INPUT " <����> ", age$
LINE INPUT " <����> ", like$
LINE INPUT " <������λ��ְҵ> ", work$
LINE INPUT " <סַ> ", address$
LINE INPUT " <�ʱ�> ", youbian$
LINE INPUT " <��ϵ�绰> ", phone$
100
LINE INPUT " <ע����> ", firstname$
LINE INPUT " <����> ", firstpassword$
IF firstname$ = "" OR firstpassword$ = "" THEN
 LOCATE 21, 2: COLOR 15: PRINT ">> ûд<ע����>��<����>�����벻������!"
 LOCATE 22, 2: COLOR 2: INPUT "?? �Ƿ�������д�������� (Y/N)", answere$
 IF answere$ = "y" OR answere$ = "Y" THEN
  CLS
  LOCATE 1, 1
  GOTO 100
 END IF
 IF answere$ = "n" OR answere$ = "N" THEN
  GOTO 10
 ELSE
  CLS
  LOCATE 1, 1
  GOTO 100
 END IF
END IF
n = 1
OPEN path1$ + "mailname.dat" FOR INPUT AS #1
DO
INPUT #1, oldname$
INPUT #1, oldpassword$
INPUT #1, nothing$
IF firstname$ = oldname$ THEN
 LOCATE 21, 2: PRINT ">> ע��������!��Ļ�"
 CLOSE #1
 LOCATE 1, 1
 GOTO 100
END IF
IF firstpassword$ = oldpassword$ THEN
 LOCATE 21, 2: PRINT ">> ��������!��Ļ�"
 CLOSE #1
 LOCATE 1, 1
 GOTO 100
END IF
IF firstpassword$ = oldpassword$ AND firstname$ = oldname$ THEN
 LOCATE 21, 2: PRINT ">> ע���������붼�ѱ�ռ��!��Ļ�"
 CLOSE #1
 LOCATE 1, 1
 GOTO 100
END IF
LOOP UNTIL EOF(1) = -1
CLOSE #1
OPEN path1$ + "mailname.dat" FOR APPEND AS #1
WRITE #1, firstname$
WRITE #1, firstpassword$
firstmailno$ = STR$(SEEK(1))
WRITE #1, firstmailno$
CLOSE #1
SHELL "copy publis.dat " + path2$ + LTRIM$(firstmailno$)
OPEN path1$ + "aboutuse.dat" FOR APPEND AS #1
WRITE #1, "<ע����> " + firstname$
WRITE #1, "<����> " + firstpassword$
WRITE #1, "<����> " + realname$
WRITE #1, "<�Ա�> " + sex$
WRITE #1, "<����> " + nation$
WRITE #1, "<����> " + age$
WRITE #1, "<����> " + like$
WRITE #1, "<ְҵ������> " + work$
WRITE #1, "<סַ> " + address$
WRITE #1, "<�ʱ�> " + youbian$
WRITE #1, "<��ϵ�绰> " + phone$
WRITE #1, "<�����> " + firstmailno$
WRITE #1, "  ***************************************************************************"
CLOSE #1
CLS
COLOR 15
LOCATE 12, 25: PRINT "<ע����>  " + firstname$
LOCATE 13, 25: PRINT "<����>  " + firstpassword$
LOCATE 15, 25: PRINT "�뽫ע�������������,��!"
LOCATE 16, 24: PRINT "(��Ϊ�������ֻ������,������)"
LOCATE 19, 28: PRINT "�����������"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 20
200
VIEW PRINT
CLS
COLOR 7
LOCATE 9, 26: PRINT "************************"
LOCATE 10, 26: PRINT "*                      *"
LOCATE 11, 26: PRINT "*    <1> �������      *"
LOCATE 12, 26: PRINT "*                      *"
LOCATE 13, 26: PRINT "*    <2> ��������      *"
LOCATE 14, 26: PRINT "*                      *"
LOCATE 15, 26: PRINT "************************"
DO
choose$ = INKEY$
IF choose$ = CHR$(49) THEN GOSUB 220
IF choose$ = CHR$(50) THEN GOSUB 205
IF choose$ = CHR$(27) THEN GOTO 10
LOOP
205
CLS
LOCATE 1, 30: PRINT "MAIL���ӹ�����"
LOCATE 2, 28: PRINT "__________________"
LOCATE 3, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "-------------------------------------------------------------------------------"
VIEW PRINT 4 TO 19
LINE INPUT " <���ĵ�ַ> (���Բ���,ֱ�Ӱ��س���) ", bbsname$
LINE INPUT " <����> (���Բ���,ֱ�Ӱ��س���) ", bbsabout$
210
LOCATE 6, 1: LINE INPUT " <��������Ҫ����������> ", bbsmain$
IF bbsmain$ = "" THEN
 CLS : VIEW PRINT 21 TO 22: LOCATE 21, 2: PRINT ">> û��Ҫ���������ݾͲ��ܽ�������!"
 LOCATE 22, 2: INPUT ">> �Ƿ�Ҫ���빫��������? (Y/N)", answere$
 CLS
 IF answere$ = "n" OR answere$ = "N" THEN GOTO 200 ELSE
 IF answere$ = "y" OR answere$ = "Y" THEN
  VIEW PRINT 4 TO 19
  GOTO 210
 ELSE
 END IF
 VIEW PRINT 4 TO 19
 GOTO 210
END IF
211
LOCATE 7, 1: LINE INPUT " <����γƺ���> ", babyname$
IF babyname$ = "" THEN
 CLS : VIEW PRINT 21 TO 22: CLS : LOCATE 21, 2: PRINT "?? û��һ������?"
 LOCATE 22, 2: INPUT "?? ����빫����Ϣ�ͱ�������һ������. ������?(Y/N):", answere$
 CLS
 IF answere$ = "n" OR answere$ = "N" THEN GOTO 200 ELSE
 IF answere$ = "y" OR answere$ = "Y" THEN
  VIEW PRINT 4 TO 19
  GOTO 211
 ELSE
 END IF
 VIEW PRINT 4 TO 19
 GOTO 211
END IF
IF bbsname$ = "" THEN bbsname$ = "��ʱ����"
OPEN path1$ + "bbs.dat" FOR APPEND AS #1
IF bbsabout$ <> "" THEN WRITE #1, ">> " + bbsabout$ + " <<" ELSE
WRITE #1, " " + bbsmain$
WRITE #1, "                                     ----- " + babyname$
WRITE #1, "                             ��ϵ��ַ: " + bbsname$
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
WRITE #1, "  ****************************************************************************"
CLOSE #1
VIEW PRINT
CLS
LOCATE 21, 2: PRINT ">> ���������! �밴���������"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 200
RETURN
220
CLS
LOCATE 1, 30: PRINT " MAIL���ӹ����� "
LOCATE 2, 27: PRINT "_______________________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 21, 2: PRINT ">> ��������Զ���ҳ,<ESC>�˳�"
VIEW PRINT 4 TO 19
DO
OPEN path1$ + "bbs.dat" FOR INPUT AS #1
DO
INPUT #1, toseebbs$
PRINT toseebbs$
IF toseebbs$ = "  ****************************************************************************" THEN
DO
 a$ = INKEY$
 FOR i = 1 TO 100
  IF a$ = CHR$(27) THEN
   CLOSE #1
   VIEW PRINT
   GOTO 200
  END IF
 NEXT i
LOOP UNTIL a$ <> "" AND a$ <> CHR$(27)
ELSE
END IF
LOOP UNTIL EOF(1) = -1
CLOSE #1
LOOP
RETURN
300
KEY(1) OFF
CLS : COLOR 2
LOCATE 1, 32: PRINT "MAIL ������"
LOCATE 2, 30: PRINT "_______________"
LOCATE 3, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 17, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 22, 1: PRINT "-------------------------------------------------------------------------------"
301
COLOR 14
VIEW PRINT 18 TO 21
INPUT " <�������������> ", talkname$
CLS
IF talkname$ = "" THEN
 VIEW PRINT 23 TO 25
 PRINT ">> һ��Ҫ��һ�����ֲ��ܽ���������"
 INPUT "?? ����빫����Ϣ�ͱ�������һ������. ������?(Y/N):", answere$
 IF answere$ = "n" OR answere$ = "N" THEN
  VIEW PRINT
  GOTO 10
 ELSE
 END IF
 IF answere$ = "y" OR answere$ = "Y" THEN
  CLS
  GOTO 301
 END IF
END IF
VIEW PRINT 23 TO 25
COLOR 2
LOCATE 23, 2: PRINT ">> ��<������>����������˵�Ļ�"
LOCATE 24, 2: PRINT "!! ��Ҫ�˳�ʱ����� exit"
COLOR 14
310
VIEW PRINT 4 TO 16
CLS : ns = 0
OPEN path1$ + "talk.dat" FOR INPUT AS #1
DO
INPUT #1, talkload$
PRINT talkload$
FOR l = 1 TO 10
NEXT l
ns = ns + 1
IF INKEY$ = CHR$(27) THEN GOTO 320
IF ns = 200 THEN GOTO 312
LOOP UNTIL EOF(1) = -1
CLOSE #1: PRINT ns
311
VIEW PRINT 18 TO 21
LINE INPUT " <������> ", talksent$
IF talksent$ = "exit" OR talksent$ = "EXIT" THEN GOTO 320
OPEN path1$ + "talk.dat" FOR APPEND AS #1
WRITE #1, talkname$ + ": " + talksent$
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
CLOSE #1
CLS
GOTO 310
312
CLOSE #1
OPEN path1$ + "talk.dat" FOR OUTPUT AS #1
WRITE #1, "  "
CLOSE #1
GOTO 311
320
CLOSE #1
VIEW PRINT
GOTO 10
RETURN
1000
CLS
VIEW PRINT
LOCATE 1, 31: PRINT "�й�MAIL�İ���"
LOCATE 2, 29: PRINT "__________________"
PRINT
PRINT
PRINT " һ.��������ɫ:"
PRINT "   1.�����ṩ����ȫ���Ľ���."
PRINT "   2.��ʹ���ߵĸ�����Ϣ��ȫ����.����������ϵʱ,ֻ��͸¶�����ʼ���ַ��һ������,"
PRINT "     ������͸¶��ʵ����."
PRINT
PRINT " ��.���а������󲿼�:"
PRINT "   1.�����ʼ�"
PRINT "     ���ͺͽ��ո����ż� (���û�����ע��һ������)"
PRINT "   2.���ӹ�����"
PRINT "     ����������������Ϣ (����:Ѱ������,������Ϣ�ȵ�)"
PRINT "   3.������"
PRINT "     ��ʱ����������̸���۽�,���з���"
PRINT
PRINT " ��.����ʹ�÷���:"
PRINT "    ����ʱע����Ļ���е���ʾ��Ϣ"
LOCATE 22, 2: PRINT ">> ��������������˵�"
DO
LOOP UNTIL INKEY$ <> ""
VIEW PRINT
GOTO 10
2000
OPEN path1$ + "caleno.dat" FOR INPUT AS #1
INPUT #1, Caleno
CLOSE #1
LOCATE 23, 63: PRINT "[ ������: "; Caleno; "]"
RETURN
2500
LOCATE 1, 73: PRINT TIME$
RETURN


