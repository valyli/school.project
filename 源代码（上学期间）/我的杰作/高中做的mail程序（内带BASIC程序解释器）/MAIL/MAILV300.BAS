ON KEY(1) GOSUB 1000
ON TIMER(2) GOSUB 2000
KEY 15, CHR$(0) + CHR$(29)
ON KEY(15) GOSUB 100015
KEY(15) ON
KEY 16, CHR$(12) + CHR$(83)
ON KEY(16) GOSUB 100016
KEY(16) ON
KEY 17, CHR$(1) + CHR$(40)
KEY 18, CHR$(2) + CHR$(40)
ON KEY(17) GOSUB 100017
KEY(17) ON
ON KEY(18) GOSUB 100017
KEY(18) ON
CLS
COLOR 15
LOCATE 7, 21: PRINT "©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©·"
LOCATE 8, 21: PRINT "©§                                  ©§"
LOCATE 9, 21: PRINT "©§        »¶Ó­Ê¹ÓÃMAILµÄÕ¾µã        ©§"
LOCATE 10, 21: PRINT "©§                                  ©§"
LOCATE 11, 21: PRINT "©§                                  ©§"
LOCATE 12, 21: PRINT "©§              MAIL                ©§"
LOCATE 13, 21: PRINT "©§           Version 3.0            ©§"
LOCATE 14, 21: PRINT "©§        96½ìºêÖ¾°à   Àî¼Ñ         ©§"
LOCATE 15, 21: PRINT "©§             1998.9               ©§"
LOCATE 16, 21: PRINT "©§                                  ©§"
LOCATE 17, 21: PRINT "©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿"
DO
LOOP UNTIL INKEY$ <> ""
path1$ = "m:\ÿÿÿÿ\"
path2$ = "m:\ÿÿÿÿ\mailbox\"
path3$ = "m:\ÿÿÿÿ\stuff\"
GOSUB 3000
OPEN path1$ + "caleno.dat" FOR INPUT AS #1
INPUT #1, Caleno
CLOSE #1
Caleno = Caleno + 1
OPEN path1$ + "caleno.dat" FOR OUTPUT AS #1
WRITE #1, Caleno
CLOSE #1
10 SCREEN 0: COLOR 14: VIEW PRINT: CLS
KEY(1) ON
LOCATE 23, 60: PRINT "[ ¼ÆÊýÆ÷: "; Caleno + 1; "]"
LOCATE 9, 27: PRINT "|                        |"
LOCATE 10, 27: PRINT "|    <1>   µç×ÓÓÊ¼þ      |"
LOCATE 11, 27: PRINT "|------------------------|"
LOCATE 12, 27: PRINT "|    <2>   µç×Ó¹«¸æÅÆ    |"
LOCATE 13, 27: PRINT "|------------------------|"
LOCATE 14, 27: PRINT "|    <3>   ÁÄÌìÊÒ        |"
LOCATE 15, 27: PRINT "|------------------------|"
LOCATE 16, 27: PRINT "|    <4>   ´ò×ÖÓÎÏ·      |"
LOCATE 17, 27: PRINT "|------------------------|"
LOCATE 18, 27: PRINT "|   <ESC>  ÍË³ö          |"
LOCATE 8, 27: PRINT "**************************"
LOCATE 19, 27: PRINT "**************************"
LOCATE 21, 28: PRINT "* <F1> ±¾Õ¾µãÊ¹ÓÃ°ïÖú *"
TIMER ON
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
IF choose$ = CHR$(52) THEN
 TIMER OFF: KEY(1) OFF
 GOSUB 3010
 END IF
IF choose$ = CHR$(27) THEN
 COLOR 0
 SYSTEM
END IF
LOCATE 1, 73: PRINT TIME$
LOOP
20
CLS : COLOR 2: CLS
LOCATE 9, 26: PRINT "************************"
LOCATE 10, 26: PRINT "*                      *"
LOCATE 11, 26: PRINT "*  <1> ÐÅ¼þä¯ÀÀÓë·¢ËÍ  *"
LOCATE 12, 26: PRINT "*                      *"
LOCATE 13, 26: PRINT "*  <2> ÐÂÓÃ»§×¢²áÐÅÏä  *"
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
COLOR 8: LOCATE 14, 23: LINE INPUT "±¾Õ¾×¢²áÃû:", tryname$
LOCATE 15, 29: LINE INPUT "ÃÜÂë:", trypassword$
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
LOCATE 21, 2: PRINT "!! ¾¯¸æ: ÃÜÂë»ò×¢²áÃû´íÎó!"
LOCATE 22, 2: COLOR 7: INPUT "?? ÊÇ·ñÖØÊÔ(Y/N)", answere$: COLOR 8
IF answere$ = "y" OR answere$ = "Y" THEN GOTO 30
IF answere$ = "n" OR answere$ = "N" THEN GOTO 10
GOTO 30
40
VIEW PRINT
CLS :  COLOR 2
LOCATE 11, 30: PRINT "***************"
LOCATE 12, 30: PRINT "*             *"
LOCATE 13, 30: PRINT "*  <1> ¿´ÐÅ   *"
LOCATE 14, 30: PRINT "*             *"
LOCATE 15, 30: PRINT "*  <2> ·¢ÐÅ   *"
LOCATE 16, 30: PRINT "*             *"
LOCATE 17, 30: PRINT "***************"
DO
choose$ = INKEY$
IF choose$ = CHR$(49) THEN GOSUB 50
IF choose$ = CHR$(50) THEN GOSUB 55
IF choose$ = CHR$(27) THEN GOSUB 10
LOOP
50
OPEN path2$ + LTRIM$(mailno$) FOR INPUT AS #1
DO
INPUT #1, letter$
LOOP UNTIL EOF(1) = -1
lettersize = SEEK(1)
CLOSE #1
VIEW PRINT
CLS
COLOR 2
LOCATE 1, 33: PRINT " MAILÐÅÏä "
LOCATE 2, 29: PRINT "__________________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 21, 1: PRINT ">> °´ÈÎÒâ¼ü×Ô¶¯·­Ò³,<ESC>ÍË³ö"
LOCATE 22, 1: PRINT "!! °´<Backspace>½«É¾³ýËùÓÐÐÅ¼þ"
LOCATE 23, 1: PRINT ">> ÐÅÏäÖÐÒÑ±»Õ¼ÓÃ ["; lettersize - 637; "×Ö½Ú]"; "             !!×¢ÒâÄúµÄÐÅÏäÖ»ÓÐ50KB(51200B)´óÐ¡"
IF lettersize > 50000 AND lettersize < 51835 THEN
 LOCATE 24, 1: PRINT "!! ½¨ÒéÄúÏÖÔÚÊÖ¶¯Çå¿ÕÐÅÏä"
ELSE
END IF
IF lettersize >= 51835 THEN
 LOCATE 24, 1: PRINT "!! ÓÉÓÚÄúµÄÐÅÏä³¬´ó,±¾´ÎÍË³öºó½«±»Ç¿ÐÐÇå¿Õ"
ELSE
END IF
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
   IF lettersize > 51835 THEN
    SHELL "copy " + path1$ + "publis.dat " + path2$ + LTRIM$(mailno$)
    CLS
    VIEW PRINT
    LOCATE 13, 20: COLOR 12: PRINT "!! ÓÉÓÚÄúµÄÐÅÏäÒÑ³¬¹ý¹æ¶¨´óÐ¡,ÐÅÏä½«±»Çå¿Õ": COLOR 2
    DO
    LOOP UNTIL INKEY$ <> ""
    GOTO 40
   ELSE
    GOTO 40
   END IF
  END IF
  IF a$ = CHR$(8) THEN
   VIEW PRINT 21 TO 23
   CLS
   LOCATE 21, 2: COLOR 12: PRINT "!! ¾¯¸æ: Äã½«É¾³ýÐÅÏäÖÐËùÓÐÐÅ¼þ!"
   LOCATE 22, 2: COLOR 7: INPUT "?? ÕæµÄÒªÉ¾³ýÂð (Y/N)", answere$: COLOR 2
   IF answere$ = "y" OR answere$ = "Y" THEN
    CLOSE #1
    SHELL "del " + path2$ + LTRIM$(mailno$)
    SHELL "copy " + path1$ + "publis.dat " + path2$ + LTRIM$(mailno$)
    CLS
    VIEW PRINT 4 TO 19
    CLS
    LOCATE 13, 27: PRINT " ÒÑÉ¾³ýÍê±Ï,°´ÈÎÒâ¼ü¼ÌÐø"
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
55
VIEW PRINT
CLS
LOCATE 11, 28: PRINT "************************"
LOCATE 12, 28: PRINT "*                      *"
LOCATE 13, 28: PRINT "*  <1> Ð´ÐÅ²¢·¢ËÍ      *"
LOCATE 14, 28: PRINT "*                      *"
LOCATE 15, 28: PRINT "*  <2> ·¢ËÍÒÑÓÐµÄÎÄ¼þ  *"
LOCATE 16, 28: PRINT "*                      *"
LOCATE 17, 28: PRINT "************************"
LOCATE 23, 2: PRINT ">> µ±ÄúÒª·¢ËÍµÄÐÅ¼þÒÑ´æÔÚ´ÅÅÌÉÏÇÒÎª´¿ÎÄ±¾(.TXT)ÎÄ¼þ£¬ÇëÑ¡Ôñ¹¦ÄÜ<2>¡£"
DO
choose$ = INKEY$
IF choose$ = CHR$(49) THEN GOSUB 60
IF choose$ = CHR$(50) THEN GOSUB 85
IF choose$ = CHR$(27) THEN GOSUB 40
LOOP
60
CLS
LOCATE 1, 32: PRINT "MAILÐÅÖ½"
LOCATE 2, 29: PRINT "______________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
VIEW PRINT 4 TO 19
LINE INPUT " <Ö÷ÒªÄÚÈÝ>  ", mainabout$
61
LINE INPUT " <ÕýÎÄ>  ", mainletter$
IF mainletter$ = "" THEN
 VIEW PRINT 23 TO 24
 LOCATE 23, 2: INPUT ">> Ã»ÓÐÕýÎÄ£¬·¢Ê²Ã´Ñ½£¿ »¹Ïë·¢ÐÅÂð£¿(Y/N)", answere$
 IF answere$ = "n" OR answere$ = "N" THEN
  GOTO 40
 ELSE
  CLS
  VIEW PRINT 4 TO 19
  CLS
  GOTO 61
 END IF
ELSE
END IF
70
CLS
LOCATE 19, 1: LINE INPUT " <ÊÕÐÅÈË>  ", riceveaddress$
IF riceveaddress$ = "" THEN
 VIEW PRINT 21 TO 22
 LOCATE 21, 2: PRINT "Ã»ÓÐµØÖ·!"
 LOCATE 22, 2: INPUT "ÊÇ·ñ·ÅÆú·¢ËÍÕâ·âÐÅ¼þ? (Y/N)", answere$
 IF answere$ = "y" OR answere$ = "Y" THEN GOTO 40
 IF answere$ = "n" OR answere$ = "N" THEN
  CLS
  VIEW PRINT 4 TO 19
  CLS
  GOTO 70
 END IF
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAILµÄ×ÊÁÏÄ¿Â¼" THEN
 stuffbox$ = "stuff"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAILµÄ×ÊÁÏ-1-1" THEN
 stuffbox$ = "stuff11"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAILµÄ×ÊÁÏ-1-2" THEN
 stuffbox$ = "stuff12"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAILµÄ×ÊÁÏ-1-3" THEN
 stuffbox$ = "stuff13"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAILµÄ×ÊÁÏ-2-1" THEN
 stuffbox$ = "stuff21"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAILµÄ×ÊÁÏ-2-2" THEN
 stuffbox$ = "stuff22"
 GOTO 71
END IF
GOTO 72
71
OPEN path3$ + stuffbox$ + ".dat" FOR INPUT AS #1
OPEN path2$ + LTRIM$(mailno$) FOR APPEND AS #2
WRITE #2, " <Ö÷ÒªÄÚÈÝ>  ÓÐ¹ØMAIL×ÊÁÏµÄ»Ø¸´"
WRITE #2, " <·¢ÐÅÈËµØÖ·>  MAIL"
WRITE #2, " <ÕýÎÄ>  "
DO
LINE INPUT #1, stuff$
WRITE #2, stuff$
LOOP UNTIL EOF(1) = -1
WRITE #2, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
WRITE #2, "  ****************************************************************************"
CLOSE #1, #2
GOTO 81
72
OPEN path1$ + "mailname.dat" FOR INPUT AS #1
DO
INPUT #1, hopename$
IF riceveaddress$ = hopename$ THEN GOTO 80
INPUT #1, nothing$
INPUT #1, nothing$
LOOP UNTIL EOF(1) = -1
VIEW PRINT 21 TO 22
LOCATE 21, 2: PRINT ">> Ã»ÓÐÕâ¸öµØÖ·! °´ÈÎÒâ¼üÊäÈëÕýÈ·µØÖ·"
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
WRITE #1, " <Ö÷ÒªÄÚÈÝ>  " + mainabout$
WRITE #1, " <·¢ÐÅÈËµØÖ·>  " + name$
WRITE #1, " <ÕýÎÄ>  " + mainletter$
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
WRITE #1, "  ****************************************************************************"
CLOSE #1
81
CLS
VIEW PRINT
LOCATE 12, 27: PRINT " ÇëÉÔºò! ÕýÔÚ·¢ËÍ........"
FOR l = 1 TO 50000: NEXT l
LOCATE 12, 27: PRINT " ÒÑ·¢ËÍÍê±Ï  °´ÈÎÒâ¼ü¼ÌÐø"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 40
RETURN
85
CLS
VIEW PRINT
LOCATE 1, 30: PRINT "MAILÎÄ±¾ÎÄ¼þ´«ÊäÆ÷"
LOCATE 2, 27: PRINT "________________________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 21, 2: PRINT "!! ×¢Òâ: Ö»ÄÜ´«ÊäÒÑ´æÔÚ´ÅÅÌÉÏ(³ýC:\Íâ)µÄÇÒÎª´¿ÎÄ±¾(.TXT)µÄÎÄ¼þ"
LOCATE 22, 2: PRINT ">> ÄúµÄÎÄ¼þ²»ÒË¹ý³¤¡£"
VIEW PRINT 4 TO 19
CLS
LOCATE 12, 2: INPUT "<ÒÑÓÐÎÄ¼þËùÔÚÂ·¾¶¼°ÎÄ¼þÃû> ", letterpath$
IF LCASE$(LEFT$(letterpath$, 1)) = "m" THEN
VIEW PRINT 21 TO 23
CLS
LOCATE 21, 2: PRINT "!! ×¢Òâ²»Òª°ÑÒª·¢ËÍµÄÎÄ¼þ´æ·ÅÔÚ M:\"
LOCATE 22, 2: PRINT ">> °´ÈÎÒâ¼üÖØÐÂÊäÈë, <ESC>¼üÍË³ö"
DO
choose$ = INKEY$
IF choose$ = CHR$(27) THEN GOTO 55 ELSE
LOOP UNTIL choose$ <> ""
GOTO 85
ELSE
END IF
IF letterpath$ = "" THEN
VIEW PRINT 21 TO 23
CLS
LOCATE 21, 2: PRINT "!! ÇëÕýÈ·ÊäÈëÎÄ¼þËùÔÚµÄ¾ø¶ÔÂ·¾¶"
LOCATE 22, 2: PRINT ">> °´ÈÎÒâ¼üÖØÐÂÊäÈë, <ESC>¼üÍË³ö"
DO
choose$ = INKEY$
IF choose$ = CHR$(27) THEN GOTO 55 ELSE
LOOP UNTIL choose$ <> ""
GOTO 85
ELSE
END IF

86
VIEW PRINT 4 TO 16
CLS
LOCATE 12, 2: INPUT "<ÊÕÐÅÈË>", riceveaddress$
OPEN path1$ + "mailname.dat" FOR INPUT AS #1
DO
INPUT #1, hopename$
IF riceveaddress$ = hopename$ THEN GOTO 87
INPUT #1, nothing$
INPUT #1, nothing$
LOOP UNTIL EOF(1) = -1
CLS
VIEW PRINT 21 TO 23
CLS
LOCATE 21, 2: PRINT ">> Ã»ÓÐÕâ¸öµØÖ·! °´ÈÎÒâ¼üÊäÈëÕýÈ·µØÖ·, <ESC> ¼üÍË³ö"
CLOSE #1
DO
choose$ = INKEY$
IF choose$ = CHR$(27) THEN GOTO 55 ELSE
LOOP UNTIL choose$ <> ""
CLS
GOTO 86
87
INPUT #1, nothing$
INPUT #1, riceveno$
CLOSE #1
CLS
SHELL "copy " + letterpath$ + " con"
INPUT "?? ÊÇ·ñ·¢ËÍÒÔÉÏµÄÐÅ¼þ (Y/N)", answere$
IF answere$ = "y" OR answere$ = "Y" THEN GOTO 88 ELSE GOTO 40
88
OPEN path1$ + "usename.tmp" FOR OUTPUT AS #1
WRITE #1, "<·¢ÐÅÈËµØÖ·> " + name$
WRITE #1, "  "
CLOSE #1
OPEN path1$ + "timedate.tmp" FOR OUTPUT AS #1
WRITE #1, ""
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
CLOSE #1
SHELL "copy " + path2$ + LTRIM$(riceveno$) + "+" + path1$ + "usename.tmp" + "+" + letterpath$ + "+" + path1$ + "timedate.tmp" + "+" + path1$ + "fengefu.dat" + " " + path2$ + LTRIM$(riceveno$)
CLS
VIEW PRINT
LOCATE 12, 27: PRINT " ÇëÉÔºò! ÕýÔÚ·¢ËÍ........"
FOR l = 1 TO 50000: NEXT l
LOCATE 12, 27: PRINT " ÒÑ·¢ËÍÍê±Ï  °´ÈÎÒâ¼ü¼ÌÐø"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 40
RETURN
90
CLS
VIEW PRINT 1 TO 20
PRINT
LINE INPUT " <ÐÕÃû> ", realname$
LINE INPUT " <ÐÔ±ð> ", sex$
LINE INPUT " <Ãñ×å> ", nation$
LINE INPUT " <ÄêÁä> ", age$
LINE INPUT " <°®ºÃ> ", like$
LINE INPUT " <¹¤×÷µ¥Î»¼°Ö°Òµ> ", work$
LINE INPUT " <×¡Ö·> ", address$
LINE INPUT " <ÓÊ±à> ", youbian$
LINE INPUT " <ÁªÏµµç»°> ", phone$
100
LINE INPUT " <×¢²áÃû> ", firstname$
LINE INPUT " <ÃÜÂë> ", firstpassword$
CLS
VIEW PRINT 21 TO 23
IF firstname$ = "" OR firstpassword$ = "" THEN
 LOCATE 21, 2: COLOR 15: PRINT ">> Ã»Ð´<×¢²áÃû>»ò<ÃÜÂë>¾ÍÉêÇë²»µ½ÓÊÏä!"
 LOCATE 22, 2: COLOR 2: INPUT "?? ÊÇ·ñÖØÐÂÌîÐ´ÒÔÉÏÁ½Ïî (Y/N)", answere$
 IF answere$ = "y" OR answere$ = "Y" THEN
  CLS
  VIEW PRINT
  LOCATE 1, 1
  GOTO 100
 END IF
 IF answere$ = "n" OR answere$ = "N" THEN
  VIEW PRINT
  GOTO 10
 ELSE
  CLS
  VIEW PRINT
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
IF firstpassword$ = oldpassword$ OR firstname$ = oldname$ THEN
 LOCATE 21, 2: PRINT ">> ×¢²áÃû»òÃÜÂëÒÑ±»Õ¼ÓÃ!Çë¸Ä»»"
 CLOSE #1
 VIEW PRINT
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
SHELL "copy " + path1$ + "publis.dat " + path2$ + LTRIM$(firstmailno$)
OPEN path1$ + "aboutuse.dat" FOR APPEND AS #1
WRITE #1, "<×¢²áÃû> " + firstname$
WRITE #1, "<ÃÜÂë> " + firstpassword$
WRITE #1, "<ÐÕÃû> " + realname$
WRITE #1, "<ÐÔ±ð> " + sex$
WRITE #1, "<Ãñ×å> " + nation$
WRITE #1, "<ÄêÁä> " + age$
WRITE #1, "<°®ºÃ> " + like$
WRITE #1, "<Ö°Òµ¼°¹¤×÷> " + work$
WRITE #1, "<×¡Ö·> " + address$
WRITE #1, "<ÓÊ±à> " + youbian$
WRITE #1, "<ÁªÏµµç»°> " + phone$
WRITE #1, "<ÐÅÏäºÅ> " + firstmailno$
WRITE #1, "  ***************************************************************************"
CLOSE #1
CLS
COLOR 15
VIEW PRINT
LOCATE 12, 25: PRINT "<×¢²áÃû>  " + firstname$
LOCATE 13, 25: PRINT "<ÃÜÂë>  " + firstpassword$
LOCATE 15, 25: PRINT "Çë½«×¢²áÃûºÍÃÜÂë¼ÇÏÂ,Îð¶ª!"
LOCATE 16, 24: PRINT "(ÒòÎª½ñºóÐÅÏäÖ»ÈÏÃÜÂë,²»ÈÏÈË)"
LOCATE 19, 28: PRINT "°´ÈÎÒâ¼ü¼ÌÐø"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 20
200
VIEW PRINT
CLS
COLOR 7
LOCATE 9, 26: PRINT "************************"
LOCATE 10, 26: PRINT "*                      *"
LOCATE 11, 26: PRINT "*    <1> ä¯ÀÀ¹«¸æ      *"
LOCATE 12, 26: PRINT "*                      *"
LOCATE 13, 26: PRINT "*    <2> ÕÅÌù¹«¸æ      *"
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
LOCATE 1, 30: PRINT "MAILµç×Ó¹«¸æÅÆ"
LOCATE 2, 28: PRINT "__________________"
LOCATE 3, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "-------------------------------------------------------------------------------"
VIEW PRINT 4 TO 19
LINE INPUT " <ÄúµÄµØÖ·> (¿ÉÒÔ²»Áô,Ö±½Ó°´»Ø³µ¼ü) ", bbsname$
LINE INPUT " <Ö÷Ìâ> (¿ÉÒÔ²»Áô,Ö±½Ó°´»Ø³µ¼ü) ", bbsabout$
210
LOCATE 6, 1: LINE INPUT " <ÇëÊäÈëËùÒª¹«²¼µÄÄÚÈÝ> ", bbsmain$
IF bbsmain$ = "" THEN
 CLS : VIEW PRINT 21 TO 22: LOCATE 21, 2: PRINT ">> Ã»ÓÐÒª¹«²¼µÄÄÚÈÝ¾Í²»ÄÜ½øÐÐÕÅÌù!"
 LOCATE 22, 2: INPUT ">> ÊÇ·ñ»¹ÒªÊäÈë¹«²¼µÄÄÚÈÝ? (Y/N)", answere$
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
LOCATE 7, 1: LINE INPUT " <¸ÃÈçºÎ³ÆºôÄú> ", babyname$
IF babyname$ = "" THEN
 CLS : VIEW PRINT 21 TO 22: CLS : LOCATE 21, 2: PRINT "?? Ã»ÓÐÒ»¸öÃû×Ö?"
 LOCATE 22, 2: INPUT "?? Èç¹ûÏë¹«²¼ÐÅÏ¢¾Í±ØÐëÊäÈëÒ»¸öÃû×Ö. ¿ÉÒÔÂð?(Y/N):", answere$
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
IF bbsname$ = "" THEN bbsname$ = "ÔÝÊ±±£ÃÜ"
OPEN path1$ + "bbs.dat" FOR APPEND AS #1
IF bbsabout$ <> "" THEN WRITE #1, ">> " + bbsabout$ + " <<" ELSE
WRITE #1, " " + bbsmain$
WRITE #1, "                                     ----- " + babyname$
WRITE #1, "                             ÁªÏµµØÖ·: " + bbsname$
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
WRITE #1, "  ****************************************************************************"
CLOSE #1
VIEW PRINT
CLS
LOCATE 21, 2: PRINT ">> ÒÑÕÅÌùÍê±Ï! Çë°´ÈÎÒâ¼ü¼ÌÐø"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 200
RETURN
220
CLS
OPEN path1$ + "bbs.dat" FOR INPUT AS #1
DO
INPUT #1, toseebbs$
LOOP UNTIL EOF(1) = -1
bbssize = SEEK(1)
CLOSE #1
IF bbssize > 1048000 THEN
 SHELL "copy " + path1$ + "bbsold.dat " + path1$ + "bbs.dat"
ELSE
END IF
LOCATE 1, 30: PRINT " MAILµç×Ó¹«¸æÅÆ "
LOCATE 2, 27: PRINT "_______________________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 21, 2: PRINT ">> °´ÈÎÒâ¼ü×Ô¶¯·­Ò³,<ESC>ÍË³ö"
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
OPEN path1$ + "talkcont.dat" FOR INPUT AS #1
INPUT #1, talkcont
CLOSE #1
talkcont = talkcont + 1
OPEN path1$ + "talkcont.dat" FOR OUTPUT AS #1
WRITE #1, talkcont
CLOSE #1
IF talkcont = 1 THEN
 SHELL "del " + path1$ + "talk.dat"
 SHELL "copy " + path1$ + "talkold.dat " + path1$ + "talk.dat"
 CLS
 LOCATE 15, 20: PRINT ">> ÏÖÔÚÁÄÌìÊÒÖÐ¿ÕÎÞÒ»ÈË"
 LOCATE 16, 20: PRINT "?? ÄãÏÖÔÚÏë½øÈë²¢ÇÒµÈ´ýÆäËûÈËµÄ½øÈëÂð(Y/N)"
 DO
 answere$ = INKEY$
 LOOP UNTIL answere$ <> ""
 IF answere$ = "n" OR answere$ = "N" THEN GOTO 320 ELSE
ELSE
END IF
KEY(1) OFF
CLS : COLOR 2
LOCATE 1, 32: PRINT "MAIL ÁÄÌìÊÒ"
LOCATE 2, 30: PRINT "_______________"
LOCATE 3, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 17, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 22, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 23, 2: PRINT ">> ÇëÊäÈëÒ»¸ö´ú³Æ"
301
COLOR 14
VIEW PRINT 18 TO 21
302
CLS
INPUT " <ÇëÊäÈëÄãµÄÃû×Ö> ", talkname$
CLS
IF talkname$ = "" THEN
 VIEW PRINT 23 TO 25
 PRINT ">> Ò»¶¨ÒªÓÐÒ»¸öÃû×Ö²ÅÄÜ½øÈëÁÄÌìÊÒ"
 PRINT "?? Ïë½øÈëÁÄÌìÊÒÂð?(Y/N):"
 DO
 answere$ = INKEY$
 LOOP UNTIL answere$ <> ""
 IF answere$ = "n" OR answere$ = "N" THEN
  VIEW PRINT
  GOTO 320
 ELSE
 END IF
 IF answere$ = "y" OR answere$ = "Y" THEN
  CLS
  GOTO 301
 ELSE
  CLS
  GOTO 301
 END IF
END IF
VIEW PRINT 23 TO 25
COLOR 2
LOCATE 23, 2: PRINT ">> ÔÚ<ÇëÊäÈë>ÖÐÊäÈëÄãÏëËµµÄ»°"
LOCATE 24, 2: PRINT "!! ÏëÒªÍË³öÊ±Çë¼üÈë exit"
COLOR 14
talkletterno = 0
310
VIEW PRINT 4 TO 16
CLS
OPEN path1$ + "talk.dat" FOR INPUT AS #1
DO
INPUT #1, talkload$
PRINT talkload$
talkletterno = talkletterno + 1
IF INKEY$ = CHR$(27) THEN GOTO 320
LOOP UNTIL EOF(1) = -1
CLOSE #1
IF talkletterno >= 66666 THEN
 SHELL "del " + path1 + "talk.dat"
 SHELL "copy " + path1$ + "talkold.dat " + path1$ + "talk.dat"
 talkletterno = 0
 OPEN path1$ + "talkcont.dat" FOR OUTPUT AS #1
 WRITE #1, 0
 CLOSE #1
 CLS
 OPEN path1$ + "talk.dat" FOR INPUT AS #1
 DO
 INPUT #1, talkload$
 PRINT talkload$
 talkletterno = talkletterno + 1
 IF INKEY$ = CHR$(27) THEN GOTO 320
 LOOP UNTIL EOF(1) = -1
 CLOSE #1
ELSE
END IF
311
VIEW PRINT 18 TO 21
CLS
LINE INPUT " <ÇëÊäÈë> ", talksent$
IF LCASE$(talksent$) = "exit" THEN GOTO 320
OPEN path1$ + "talk.dat" FOR APPEND AS #1
WRITE #1, talkname$ + ": " + talksent$
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
CLOSE #1
CLS
GOTO 310
320
CLOSE #1
talkcont = talkcont - 1
OPEN path1$ + "talkcont.dat" FOR OUTPUT AS #1
WRITE #1, talkcont
CLOSE #1
VIEW PRINT
TIMER OFF
GOTO 10
RETURN
1000
TIMER OFF
CLS
VIEW PRINT
LOCATE 1, 31: PRINT "ÓÐ¹ØMAILµÄ°ïÖú"
LOCATE 2, 29: PRINT "__________________"
PRINT " Ò».±¾Õ¾µãÌØÉ«:"
PRINT "    1.Õ¾µãÌá¹©µÄÊÇÈ«ÖÐÎÄ½çÃæ."
PRINT "    2.¶ÔÊ¹ÓÃÕßµÄ¸öÈËÐÅÏ¢ÍêÈ«±£ÃÜ.µ±ÓëËûÈËÁªÏµÊ±,Ö»ÐèÍ¸Â¶µç×ÓÓÊ¼þµØÖ·»òÒ»¸ö´ú³Æ,"
PRINT "      ¶øÎÞÐèÍ¸Â¶ÕæÊµÐÕÃû."
PRINT " ¶þ.ÆäÖÐ°üÀ¨ËÄ´ó²¿¼þ:"
PRINT "    1.µç×ÓÓÊ¼þ"
PRINT "      ·¢ËÍºÍ½ÓÊÕ¸öÈËÐÅ¼þ (ÐÂÓÃ»§ÐèÏÈ×¢²áÒ»¸öÐÅÏä)"
PRINT "    2.µç×Ó¹«¸æÅÆ"
PRINT "      ä¯ÀÀºÍÕÅÌùËùÐèµÄÐÅÏ¢ (ÀýÈç:Ñ°ÎïÆôÊÂ,½»ÓÑÐÅÏ¢µÈµÈ)"
PRINT "    3.ÁÄÌìÊÒ"
PRINT "      ¼´Ê±µÄÓëÆäËûÈËÌ¸¹ÅÂÛ½ñ,ÐÝÏÐ·ÅËÉ"
PRINT "    4.´ò×ÖÓÎÏ·"
PRINT "      ¹©ÐÝÏÐÓéÀÖÓÃ."
PRINT " Èý.¾ßÌåÊ¹ÓÃ·½·¨:"
PRINT "      ×¢Òâ×Ö·û   ÔÚ±¾Õ¾Îª·Ç·¨×Ö·û,²»µÃÊ¹ÓÃ.ÆäËüÇëËæÊ±×¢ÒâÆÁÄ»µ×ÐÐµÄÌáÊ¾ÐÅÏ¢"
PRINT "!! ×¢Òâ:Èç¹ûÏ£ÍûµÃµ½±¾Õ¾¸üÏêÏ¸µÄ×ÊÁÏ,Çë¸ø¹ÜÀíÔ±·¢Ò»¸öÓÊ¼þ,¸ñÊ½ÈçÏÂ:"
PRINT "        <Ö÷ÒªÄÚÈÝ> MAILµÄ×ÊÁÏÄ¿Â¼"
PRINT "        <ÊÕÐÅÈË> MAIL"
PRINT "    ÔÚ<ÕýÎÄ>ÖÐ¼üÈëÈÎÒâ×Ö·û,Äú¾Í»áÂíÉÏµÃµ½ÏµÍ³¸øÄúµÄ×Ô¶¯»Ø¸´."
PRINT
PRINT "                                    ----  ÏµÍ³¹ÜÀíÔ±ÓÊ¼þµØÖ·: MAIL"
LOCATE 24, 2: PRINT ">> °´ÈÎÒâ¼ü·µ»ØÖ÷²Ëµ¥......"
LOCATE 17, 16: PRINT CHR$(34)
DO
LOOP UNTIL INKEY$ <> ""
VIEW PRINT
GOTO 10
TIMER ON
2000
OPEN path1$ + "caleno.dat" FOR INPUT AS #1
INPUT #1, Caleno
CLOSE #1
LOCATE 23, 60: PRINT "[ ¼ÆÊýÆ÷: "; Caleno + 1; "]"
LOCATE 1, 73
RETURN
3000
DIM a(1024), B(1024), c(1024), d(1024), mailpicture(10240)
a1 = 9
SCREEN 12
CIRCLE (10, 10), 10, 14: PAINT (10, 10), 14
CIRCLE (31, 10), 10, 12: PAINT (31, 10), 12
CIRCLE (52, 10), 10, 15: PAINT (52, 10), 15
CIRCLE (73, 10), 10, 2: PAINT (73, 10), 2
GET (0, 0)-(20, 20), a
GET (21, 0)-(41, 20), B
GET (42, 0)-(62, 20), c
GET (63, 0)-(83, 20), d
CLS
PSET (50, 0), a1
LINE -(0, 150), a1
LINE -(25, 150), a1
LINE -(50, 75), a1
LINE -(75, 150), a1
LINE -(100, 75), a1
LINE -(125, 150), a1
LINE -(150, 150), a1
LINE -(100, 0), a1
LINE -(75, 90), a1
LINE -(50, 0), a1
PAINT (45, 75), a1
LINE (200, 0)-(150, 150), a1
LINE -(175, 150), a1
LINE -(200, 75), a1
LINE -(225, 150), a1
LINE -(250, 150), a1
LINE -(200, 0), a1
LINE (175, 110)-(225, 135), a1, B
PAINT (200, 10), a1
PAINT (180, 120), a1
PAINT (220, 130), a1
PAINT (200, 120), a1
LINE (275, 0)-(300, 150), a1, B
PAINT (280, 75), a1
LINE (325, 0)-(350, 150), a1, B
LINE (325, 125)-(395, 150), a1, B
PAINT (330, 120), a1
PAINT (330, 130), a1
PAINT (360, 130), a1
LINE (0, 180)-(395, 200), 9, B
GET (0, 0)-(395, 180), mailpicture
CLS
FOR i = 108 TO 131
a$ = INKEY$
IF a$ <> "" THEN RETURN
PUT (180 - i + 52, i), mailpicture, XOR
NEXT i
FOR i = 1 TO 50000
IF a$ <> "" THEN GOTO 10
NEXT i
x1 = 0: y1 = 0: a1 = 3: a2 = 3           '0,0,3,3
x2 = 0: y2 = 0: b1 = 2: b2 = 2        '607,0,2,2
x3 = 0: y3 = 0: c1 = 2: c2 = 3       '607,447,3,2
x4 = 0: y4 = 0: d1 = 3: d2 = 2          '0,447,2,3
DO
x1 = x1 + a1: y1 = y1 + a2
IF x1 > 607 THEN a1 = -a1
IF y1 > 447 THEN a2 = -a2
IF x1 < 2 THEN a1 = -a1
IF y1 < 2 THEN a2 = -a2
x1 = x1 + a1: y1 = y1 + a2
PUT (x1, y1), a, XOR
x2 = x2 + b1: y2 = y2 + b2
IF x2 > 607 THEN b1 = -b1
IF y2 > 447 THEN b2 = -b2
IF x2 < 2 THEN b1 = -b1
IF y2 < 2 THEN b2 = -b2
x2 = x2 + b1: y2 = y2 + b2
PUT (x2, y2), B, XOR
x3 = x3 + c1: y3 = y3 + c2
IF x3 > 607 THEN c1 = -c1
IF y3 > 447 THEN c2 = -c2
IF x3 < 2 THEN c1 = -c1
IF y3 < 2 THEN c2 = -c2
x3 = x3 + c1: y3 = y3 + c2
PUT (x3, y3), c, XOR
x4 = x4 + d1: y4 = y4 + d2
IF x4 > 607 THEN d1 = -d1
IF y4 > 447 THEN d2 = -d2
IF x4 < 2 THEN d1 = -d1
IF y4 < 2 THEN d2 = -d2
x4 = x4 + d1: y4 = y4 + d2
PUT (x4, y4), d, XOR
FOR Q = 1 TO 800
NEXT Q
PUT (x1, y1), a, XOR
PUT (x2, y2), B, XOR
PUT (x3, y3), c, XOR
PUT (x4, y4), d, XOR
LOOP UNTIL INKEY$ <> ""
RETURN
3010
CLS
COLOR 12
LOCATE 13, 30: PRINT "1.Ð¡Ð´×ÖÄ¸"
LOCATE 14, 30: PRINT "2.´óÐ¡Ð´×ÖÄ¸"
LOCATE 15, 30: PRINT "3.´óÐ¡Ð´×ÖÄ¸ÓëÊý×Ö"
LOCATE 16, 30: PRINT "4.ËùÓÐ·ûºÅ¼ü"
3011
LOCATE 11, 29: PRINT "ÇëÊäÈë´ò×Ö·¶Î§: "
DO
howmanyword$ = INKEY$
IF howmanyword$ = CHR$(27) THEN GOTO 10
LOOP UNTIL howmanyword$ <> ""
howmanyword = VAL(howmanyword$)
IF howmanyword < 1 OR howmanyword > 4 THEN GOTO 3011 ELSE
IF howmanyword$ = "1" THEN
 downland1 = 26
 topland1 = 97
 downland2 = 0
 topland2 = 96
 downland3 = 123
 topland3 = 255
ELSE
END IF
IF howmanyword$ = "2" THEN
 downland1 = 58
 topland1 = 65
 downland2 = 91
 topland2 = 96
 downland3 = 91
 topland3 = 96
ELSE
END IF
IF howmanyword$ = "3" THEN
 downland1 = 75
 topland1 = 48
 downland2 = 58
 topland2 = 64
 downland3 = 91
 topland3 = 96
ELSE
END IF
IF howmanyword$ = "4" THEN
 downland1 = 94
 topland1 = 33
 downland2 = 0
 topland2 = 32
 downland2 = 127
 topland2 = 255
ELSE
END IF
3012
CLS
LOCATE 15, 30: PRINT "´ò×ÖËÙ¶È (1-9):"
DO
speed$ = INKEY$
IF speed$ = CHR$(27) THEN GOTO 10
LOOP UNTIL speed$ <> ""
speed = VAL(speed$)
IF speed < 1 OR speed > 9 THEN GOTO 3012
speed = (10 - speed) * 2500
winno = 0: wordno = 0
usetime1 = TIMER
CLS
COLOR 6
LOCATE 18, 30: PRINT "**************"
LOCATE 19, 30: PRINT "*  ´ò×ÖÓÎÏ·  *"
LOCATE 20, 30: PRINT "**************"
LOCATE 18, 55: PRINT "ËÙ¶È:"; 10 - speed / 2500
LOCATE 20, 55: PRINT "ÄÑ¶È:"; howmanyword
LOCATE 23, 2: PRINT ">> °´<ESC>¼üÍË³ö"
LOCATE 3, 1: PRINT "_______________________________________________________________________________"
LOCATE 16, 1: PRINT "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
VIEW PRINT 4 TO 15
CLS
COLOR 13
LOCATE 10, 27: PRINT "×¼±¸ºÃºó°´ÈÎÒâ¼ü¼ÌÐø......"
'LOCATE 11, 28: PRINT "__________________________"
DO
LOOP UNTIL INKEY$ <> ""
COLOR 7
VIEW PRINT
LOCATE 1, 30: PRINT "ÃüÖÐ: 0 ¸ö"
wordno = 0
3020
VIEW PRINT 4 TO 15
CLS
RANDOMIZE TIMER
3021
a = INT(RND * downland1 + topland1)
IF a >= downland2 AND a <= topland2 THEN GOTO 3021 ELSE
IF a >= downland3 AND a <= topland3 THEN GOTO 3021 ELSE
a$ = CHR$(a)
x = INT(RND * 77 + 3)
FOR y = 5 TO 14 STEP 1
 CLS
 LOCATE y, x: COLOR 15: PRINT a$: COLOR 7
 usetime2 = TIMER - usetime1
 VIEW PRINT 1 TO 2
 CLS
 LOCATE 1, 35: PRINT "ÃüÖÐ: "; winno; "¸ö"
 LOCATE 1, 65: PRINT "Ê±¼ä: "; INT(10 * usetime2) / 10; "Ãë"
 LOCATE 1, 1: PRINT "×ÜµÄÏÂÂä×Ö·ûÊý: "; wordno; "¸ö"
 VIEW PRINT 4 TO 15
FOR n = 1 TO speed
 play$ = INKEY$
 IF play$ = a$ THEN GOTO 3022
 IF play$ = CHR$(27) THEN GOTO 3100
NEXT n
NEXT y
wordno = wordno + 1
GOTO 3020
3022
COLOR 14
FOR killy = 15 TO y STEP -1
LOCATE killy, x: PRINT "|"
FOR z = 1 TO 200
NEXT z
NEXT killy
FOR t = 1 TO 2000
NEXT t
'SOUND 2500, .1
'SOUND 3000, .2
'SOUND 2500, .1
winno = winno + 1
wordno = wordno + 1
VIEW PRINT 1 TO 2
CLS
LOCATE 1, 35: PRINT "ÃüÖÐ: "; winno; "¸ö"
GOTO 3020
3100
CLS
VIEW PRINT
IF usetime2 < 1 THEN
 LOCATE 9, 27: PRINT "Ê±¼äÌ«¶Ì!²»¼Ç³É¼¨"
 LOCATE 11, 27: PRINT ">> °´ÈÎÒâ¼ü¼ÌÐø......"
 DO
 LOOP UNTIL INKEY$ <> ""
 GOTO 10
ELSE
END IF
IF wordno = 0 OR winno = 0 THEN
 LOCATE 9, 27: PRINT "Î´½øÐÐ´ò×Ö!²»¼Ç³É¼¨"
 LOCATE 11, 27: PRINT ">> °´ÈÎÒâ¼ü¼ÌÐø......"
 DO
 LOOP UNTIL INKEY$ <> ""
 GOTO 10
ELSE
END IF
LOCATE 10, 25: PRINT "ÃüÖÐÂÊ: "; INT(10000 * winno / wordno) / 100; "%"
LOCATE 11, 25: PRINT "´ò×ÖËÙ¶È (Ö»ËãÃüÖÐµÄ): "; FIX(winno * 60 / usetime2); "¸ö/·Ö"
LOCATE 12, 25: PRINT "´ò×Ö³É¼¨ :"; FIX(((winno / wordno + 1) * 100 * (winno * 60 / usetime2)) / 100); "·Ö"
LOCATE 14, 25: PRINT ">> °´ÈÎÒâ¼ü¼ÌÐø......"
rplay1 = FIX(((winno / wordno + 1) * 100 * (winno * 60 / usetime2)) / 100)
timedate$ = "[ " + TIME$ + "/" + DATE$ + " ]"
DO
LOOP UNTIL INKEY$ <> ""
OPEN path1$ + "rplay1.dat" FOR INPUT AS #1
INPUT #1, roldplayname$
INPUT #1, roldplay1
INPUT #1, roldtimedate$
CLOSE #1
IF roldplay1 < rplay1 THEN
 CLS
 COLOR 5
 LOCATE 5, 24: PRINT "*****************************"
 LOCATE 6, 24: PRINT "*                           *"
 LOCATE 7, 24: PRINT "* Äú´òÆÆÁËÔ­ÓÐµÄ×î¸ß¼ÇÂ¼!!! *"
 LOCATE 8, 24: PRINT "*                           *"
 LOCATE 9, 24: PRINT "*      --- ×£ºØÄú ---       *"
 LOCATE 10, 24: PRINT "*                           *"
 LOCATE 11, 24: PRINT "*****************************"
 LOCATE 17, 25: INPUT "ÇëÊäÈëÄúµÄ×ðÐÕ´óÃû£º", rplayname$
 OPEN path1$ + "rplay1.dat" FOR OUTPUT AS #1
 WRITE #1, rplayname$
 WRITE #1, rplay1
 WRITE #1, timedate$
 CLOSE #1
 roldplayname$ = rplayname$
 roldplay1 = rplay1
 roldtimedate$ = timedate$
ELSE
END IF
CLS
COLOR 11
LOCATE 10, 22: PRINT "×î¸ß¼ÇÂ¼±£³ÖÕß£º", roldplayname$
LOCATE 12, 22: PRINT "×î¸ßµÃ·Ö£º      ", roldplay1
LOCATE 14, 22: PRINT "ÆÆ¼ÇÂ¼Ê±¼ä£º    ", roldtimedate$
LOCATE 20, 25: PRINT ">> °´ÈÎÒâ¼ü¼ÌÐø......"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 10
100015
RETURN
100016
RETURN
100017
RETURN

