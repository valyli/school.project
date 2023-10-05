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

SCREEN 12
PAINT (1, 1), 7
LINE (140, 80)-(490, 320), 7, BF
LINE (140, 80)-(490, 82), 8, BF
LINE (140, 80)-(138, 322), 8, BF
LINE (141, 322)-(490, 320), 15, BF
LINE (490, 83)-(488, 320), 15, BF
COLOR 14
LOCATE 7, 21: PRINT "┏━━━━━━━━━━━━━━━━━┓"
LOCATE 8, 21: PRINT "┃                                  ┃"
LOCATE 9, 21: PRINT "┃        欢迎使用MAIL的站点        ┃"
LOCATE 10, 21: PRINT "┃                                  ┃"
LOCATE 11, 21: PRINT "┃                                  ┃"
LOCATE 12, 21: PRINT "┃              MAIL                ┃"
LOCATE 13, 21: PRINT "┃           Version 3.0            ┃"
LOCATE 14, 21: PRINT "┃        96届宏志班   李佳         ┃"
LOCATE 15, 21: PRINT "┃             1998.9               ┃"
LOCATE 16, 21: PRINT "┃                                  ┃"
LOCATE 17, 21: PRINT "┗━━━━━━━━━━━━━━━━━┛"

DO
LOOP UNTIL INKEY$ <> ""
CLS
GOSUB 3000
OPEN "caleno.dat" FOR INPUT AS #1
INPUT #1, Caleno
CLOSE #1
Caleno = Caleno + 1
OPEN "caleno.dat" FOR OUTPUT AS #1
WRITE #1, Caleno
CLOSE #1
10 SCREEN 0: COLOR 14: VIEW PRINT: CLS
KEY(1) ON
LOCATE 23, 60: PRINT "[ 计数器: "; Caleno + 1; "]"
LOCATE 9, 27: PRINT "|                        |"
LOCATE 10, 27: PRINT "|    <1>   电子邮件      |"
LOCATE 11, 27: PRINT "|------------------------|"
LOCATE 12, 27: PRINT "|    <2>   电子公告牌    |"
LOCATE 13, 27: PRINT "|------------------------|"
LOCATE 14, 27: PRINT "|    <3>   聊天室        |"
LOCATE 15, 27: PRINT "|------------------------|"
LOCATE 16, 27: PRINT "|    <4>   打字游戏      |"
LOCATE 17, 27: PRINT "|------------------------|"
LOCATE 18, 27: PRINT "|   <ESC>  退出          |"
LOCATE 8, 27: PRINT "**************************"
LOCATE 19, 27: PRINT "**************************"
LOCATE 21, 28: PRINT "* <F1> 本站点使用帮助 *"
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
LOCATE 11, 26: PRINT "*  <1> 信件浏览与发送  *"
LOCATE 12, 26: PRINT "*                      *"
LOCATE 13, 26: PRINT "*  <2> 新用户注册信箱  *"
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
COLOR 8: LOCATE 14, 23: LINE INPUT "本站注册名:", tryname$
LOCATE 15, 29: LINE INPUT "密码:", trypassword$
OPEN "mailname.dat" FOR INPUT AS #1
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
LOCATE 21, 2: PRINT "!! 警告: 密码或注册名错误!"
LOCATE 22, 2: COLOR 7: INPUT "?? 是否重试(Y/N)", answere$: COLOR 8
IF answere$ = "y" OR answere$ = "Y" THEN GOTO 30
IF answere$ = "n" OR answere$ = "N" THEN GOTO 10
GOTO 30
40
VIEW PRINT
CLS :  COLOR 2
LOCATE 11, 30: PRINT "***************"
LOCATE 12, 30: PRINT "*             *"
LOCATE 13, 30: PRINT "*  <1> 看信   *"
LOCATE 14, 30: PRINT "*             *"
LOCATE 15, 30: PRINT "*  <2> 发信   *"
LOCATE 16, 30: PRINT "*             *"
LOCATE 17, 30: PRINT "***************"
DO
choose$ = INKEY$
IF choose$ = CHR$(49) THEN GOSUB 50
IF choose$ = CHR$(50) THEN GOSUB 55
IF choose$ = CHR$(27) THEN GOSUB 10
LOOP
50
OPEN LTRIM$(mailno$) FOR INPUT AS #1
DO
INPUT #1, letter$
LOOP UNTIL EOF(1) = -1
lettersize = SEEK(1)
CLOSE #1
VIEW PRINT
CLS
COLOR 2
LOCATE 1, 33: PRINT " MAIL信箱 "
LOCATE 2, 29: PRINT "__________________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 21, 1: PRINT ">> 按任意键自动翻页,<ESC>退出"
LOCATE 22, 1: PRINT "!! 按<Backspace>将删除所有信件"
LOCATE 23, 1: PRINT ">> 信箱中已被占用 ["; lettersize - 637; "字节]"; "             !!注意您的信箱只有50KB(51200B)大小"
IF lettersize > 50000 AND lettersize < 51835 THEN
 LOCATE 24, 1: PRINT "!! 建议您现在手动清空信箱"
ELSE
END IF
IF lettersize >= 51835 THEN
 LOCATE 24, 1: PRINT "!! 由于您的信箱超大,本次退出后将被强行清空"
ELSE
END IF
VIEW PRINT 4 TO 19
DO
OPEN LTRIM$(mailno$) FOR INPUT AS #1
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
    SHELL "copy publis.dat " + LTRIM$(mailno$)
    CLS
    VIEW PRINT
    LOCATE 13, 20: COLOR 12: PRINT "!! 由于您的信箱已超过规定大小,信箱将被清空": COLOR 2
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
   LOCATE 21, 2: COLOR 12: PRINT "!! 警告: 你将删除信箱中所有信件!"
   LOCATE 22, 2: COLOR 7: INPUT "?? 真的要删除吗 (Y/N)", answere$: COLOR 2
   IF answere$ = "y" OR answere$ = "Y" THEN
    CLOSE #1
    SHELL "del " + LTRIM$(mailno$)
    SHELL "copy publis.dat " + LTRIM$(mailno$)
    CLS
    VIEW PRINT 4 TO 19
    CLS
    LOCATE 13, 27: PRINT " 已删除完毕,按任意键继续"
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
LOCATE 13, 28: PRINT "*  <1> 写信并发送      *"
LOCATE 14, 28: PRINT "*                      *"
LOCATE 15, 28: PRINT "*  <2> 发送已有的文件  *"
LOCATE 16, 28: PRINT "*                      *"
LOCATE 17, 28: PRINT "************************"
LOCATE 23, 2: PRINT ">> 当您要发送的信件已存在磁盘上且为纯文本(.TXT)文件，请选择功能<2>。"
DO
choose$ = INKEY$
IF choose$ = CHR$(49) THEN GOSUB 60
IF choose$ = CHR$(50) THEN GOSUB 85
IF choose$ = CHR$(27) THEN GOSUB 40
LOOP
60
CLS
LOCATE 1, 32: PRINT "MAIL信纸"
LOCATE 2, 29: PRINT "______________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
VIEW PRINT 4 TO 19
LINE INPUT " <主要内容>  ", mainabout$
61
LINE INPUT " <正文>  ", mainletter$
IF mainletter$ = "" THEN
 VIEW PRINT 23 TO 24
 LOCATE 23, 2: INPUT ">> 没有正文，发什么呀？ 还想发信吗？(Y/N)", answere$
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
LOCATE 19, 1: LINE INPUT " <收信人>  ", riceveaddress$
IF riceveaddress$ = "" THEN
 VIEW PRINT 21 TO 22
 LOCATE 21, 2: PRINT "没有地址!"
 LOCATE 22, 2: INPUT "是否放弃发送这封信件? (Y/N)", answere$
 IF answere$ = "y" OR answere$ = "Y" THEN GOTO 40
 IF answere$ = "n" OR answere$ = "N" THEN
  CLS
  VIEW PRINT 4 TO 19
  CLS
  GOTO 70
 END IF
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAIL的资料目录" THEN
 stuffbox$ = "stuff"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAIL的资料-1-1" THEN
 stuffbox$ = "stuff11"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAIL的资料-1-2" THEN
 stuffbox$ = "stuff12"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAIL的资料-1-3" THEN
 stuffbox$ = "stuff13"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAIL的资料-2-1" THEN
 stuffbox$ = "stuff21"
 GOTO 71
END IF
IF riceveaddress$ = "MAIL" AND mainabout$ = "MAIL的资料-2-2" THEN
 stuffbox$ = "stuff22"
 GOTO 71
END IF
GOTO 72
71
OPEN stuffbox$ + ".dat" FOR INPUT AS #1
OPEN LTRIM$(mailno$) FOR APPEND AS #2
WRITE #2, " <主要内容>  有关MAIL资料的回复"
WRITE #2, " <发信人地址>  MAIL"
WRITE #2, " <正文>  "
DO
LINE INPUT #1, stuff$
WRITE #2, stuff$
LOOP UNTIL EOF(1) = -1
WRITE #2, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
WRITE #2, "  ****************************************************************************"
CLOSE #1, #2
GOTO 81
72
OPEN "mailname.dat" FOR INPUT AS #1
DO
INPUT #1, hopename$
IF riceveaddress$ = hopename$ THEN GOTO 80
INPUT #1, nothing$
INPUT #1, nothing$
LOOP UNTIL EOF(1) = -1
VIEW PRINT 21 TO 22
LOCATE 21, 2: PRINT ">> 没有这个地址! 按任意键输入正确地址"
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
OPEN LTRIM$(riceveno$) FOR APPEND AS #1
WRITE #1, " <主要内容>  " + mainabout$
WRITE #1, " <发信人地址>  " + name$
WRITE #1, " <正文>  " + mainletter$
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
WRITE #1, "  ****************************************************************************"
CLOSE #1
81
CLS
VIEW PRINT
LOCATE 12, 27: PRINT " 请稍候! 正在发送........"
FOR l = 1 TO 50000: NEXT l
LOCATE 12, 27: PRINT " 已发送完毕  按任意键继续"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 40
RETURN
85
CLS
VIEW PRINT
LOCATE 1, 30: PRINT "MAIL文本文件传输器"
LOCATE 2, 27: PRINT "________________________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 21, 2: PRINT "!! 注意: 只能传输已存在磁盘上(除C:\外)的且为纯文本(.TXT)的文件"
LOCATE 22, 2: PRINT ">> 您的文件不宜过长。"
VIEW PRINT 4 TO 19
CLS
LOCATE 12, 2: INPUT "<已有文件所在路径及文件名> ", letterpath$
IF LCASE$(LEFT$(letterpath$, 1)) = "m" THEN
VIEW PRINT 21 TO 23
CLS
LOCATE 21, 2: PRINT "!! 注意不要把要发送的文件存放在 M:\"
LOCATE 22, 2: PRINT ">> 按任意键重新输入, <ESC>键退出"
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
LOCATE 21, 2: PRINT "!! 请正确输入文件所在的绝对路径"
LOCATE 22, 2: PRINT ">> 按任意键重新输入, <ESC>键退出"
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
LOCATE 12, 2: INPUT "<收信人>", riceveaddress$
OPEN "mailname.dat" FOR INPUT AS #1
DO
INPUT #1, hopename$
IF riceveaddress$ = hopename$ THEN GOTO 87
INPUT #1, nothing$
INPUT #1, nothing$
LOOP UNTIL EOF(1) = -1
CLS
VIEW PRINT 21 TO 23
CLS
LOCATE 21, 2: PRINT ">> 没有这个地址! 按任意键输入正确地址, <ESC> 键退出"
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
INPUT "?? 是否发送以上的信件 (Y/N)", answere$
IF answere$ = "y" OR answere$ = "Y" THEN GOTO 88 ELSE GOTO 40
88
OPEN "usename.tmp" FOR OUTPUT AS #1
WRITE #1, "<发信人地址> " + name$
WRITE #1, "  "
CLOSE #1
OPEN "timedate.tmp" FOR OUTPUT AS #1
WRITE #1, ""
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
CLOSE #1
SHELL "copy " + LTRIM$(riceveno$) + "+" + "usename.tmp" + "+" + letterpath$ + "+" + "timedate.tmp" + "+" + "fengefu.dat" + " " + LTRIM$(riceveno$)
CLS
VIEW PRINT
LOCATE 12, 27: PRINT " 请稍候! 正在发送........"
FOR l = 1 TO 50000: NEXT l
LOCATE 12, 27: PRINT " 已发送完毕  按任意键继续"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 40
RETURN
90
CLS
VIEW PRINT 1 TO 20
PRINT
LINE INPUT " <姓名> ", realname$
LINE INPUT " <性别> ", sex$
LINE INPUT " <民族> ", nation$
LINE INPUT " <年龄> ", age$
LINE INPUT " <爱好> ", like$
LINE INPUT " <工作单位及职业> ", work$
LINE INPUT " <住址> ", address$
LINE INPUT " <邮编> ", youbian$
LINE INPUT " <联系电话> ", phone$
100
LINE INPUT " <注册名> ", firstname$
LINE INPUT " <密码> ", firstpassword$
CLS
VIEW PRINT 21 TO 23
IF firstname$ = "" OR firstpassword$ = "" THEN
 LOCATE 21, 2: COLOR 15: PRINT ">> 没写<注册名>或<密码>就申请不到邮箱!"
 LOCATE 22, 2: COLOR 2: INPUT "?? 是否重新填写以上两项 (Y/N)", answere$
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
OPEN "mailname.dat" FOR INPUT AS #1
DO
INPUT #1, oldname$
INPUT #1, oldpassword$
INPUT #1, nothing$
IF firstpassword$ = oldpassword$ OR firstname$ = oldname$ THEN
 LOCATE 21, 2: PRINT ">> 注册名或密码已被占用!请改换"
 CLOSE #1
 VIEW PRINT
 LOCATE 1, 1
 GOTO 100
END IF
LOOP UNTIL EOF(1) = -1
CLOSE #1
OPEN "mailname.dat" FOR APPEND AS #1
WRITE #1, firstname$
WRITE #1, firstpassword$
firstmailno$ = STR$(SEEK(1))
WRITE #1, firstmailno$
CLOSE #1
SHELL "copy publis.dat " + LTRIM$(firstmailno$)
OPEN "aboutuse.dat" FOR APPEND AS #1
WRITE #1, "<注册名> " + firstname$
WRITE #1, "<密码> " + firstpassword$
WRITE #1, "<姓名> " + realname$
WRITE #1, "<性别> " + sex$
WRITE #1, "<民族> " + nation$
WRITE #1, "<年龄> " + age$
WRITE #1, "<爱好> " + like$
WRITE #1, "<职业及工作> " + work$
WRITE #1, "<住址> " + address$
WRITE #1, "<邮编> " + youbian$
WRITE #1, "<联系电话> " + phone$
WRITE #1, "<信箱号> " + firstmailno$
WRITE #1, "  ***************************************************************************"
CLOSE #1
CLS
COLOR 15
VIEW PRINT
LOCATE 12, 25: PRINT "<注册名>  " + firstname$
LOCATE 13, 25: PRINT "<密码>  " + firstpassword$
LOCATE 15, 25: PRINT "请将注册名和密码记下,勿丢!"
LOCATE 16, 24: PRINT "(因为今后信箱只认密码,不认人)"
LOCATE 19, 28: PRINT "按任意键继续"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 20
200
VIEW PRINT
CLS
COLOR 7
LOCATE 9, 26: PRINT "************************"
LOCATE 10, 26: PRINT "*                      *"
LOCATE 11, 26: PRINT "*    <1> 浏览公告      *"
LOCATE 12, 26: PRINT "*                      *"
LOCATE 13, 26: PRINT "*    <2> 张贴公告      *"
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
LOCATE 1, 30: PRINT "MAIL电子公告牌"
LOCATE 2, 28: PRINT "__________________"
LOCATE 3, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "-------------------------------------------------------------------------------"
VIEW PRINT 4 TO 19
LINE INPUT " <您的地址> (可以不留,直接按回车键) ", bbsname$
LINE INPUT " <主题> (可以不留,直接按回车键) ", bbsabout$
210
LOCATE 6, 1: LINE INPUT " <请输入所要公布的内容> ", bbsmain$
IF bbsmain$ = "" THEN
 CLS : VIEW PRINT 21 TO 22: LOCATE 21, 2: PRINT ">> 没有要公布的内容就不能进行张贴!"
 LOCATE 22, 2: INPUT ">> 是否还要输入公布的内容? (Y/N)", answere$
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
LOCATE 7, 1: LINE INPUT " <该如何称呼您> ", babyname$
IF babyname$ = "" THEN
 CLS : VIEW PRINT 21 TO 22: CLS : LOCATE 21, 2: PRINT "?? 没有一个名字?"
 LOCATE 22, 2: INPUT "?? 如果想公布信息就必须输入一个名字. 可以吗?(Y/N):", answere$
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
IF bbsname$ = "" THEN bbsname$ = "暂时保密"
OPEN "bbs.dat" FOR APPEND AS #1
IF bbsabout$ <> "" THEN WRITE #1, ">> " + bbsabout$ + " <<" ELSE
WRITE #1, " " + bbsmain$
WRITE #1, "                                     ----- " + babyname$
WRITE #1, "                             联系地址: " + bbsname$
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
WRITE #1, "  ****************************************************************************"
CLOSE #1
VIEW PRINT
CLS
LOCATE 21, 2: PRINT ">> 已张贴完毕! 请按任意键继续"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 200
RETURN
220
CLS
OPEN "bbs.dat" FOR INPUT AS #1
DO
INPUT #1, toseebbs$
LOOP UNTIL EOF(1) = -1
bbssize = SEEK(1)
CLOSE #1
IF bbssize > 1048000 THEN
 SHELL "copy bbsold.dat bbs.dat"
ELSE
END IF
LOCATE 1, 30: PRINT " MAIL电子公告牌 "
LOCATE 2, 27: PRINT "_______________________"
LOCATE 3, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 20, 1: PRINT "--------------------------------------------------------------------------------"
LOCATE 21, 2: PRINT ">> 按任意键自动翻页,<ESC>退出"
VIEW PRINT 4 TO 19
DO
OPEN "bbs.dat" FOR INPUT AS #1
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
OPEN "talkcont.dat" FOR INPUT AS #1
INPUT #1, talkcont
CLOSE #1
talkcont = talkcont + 1
OPEN "talkcont.dat" FOR OUTPUT AS #1
WRITE #1, talkcont
CLOSE #1
IF talkcont = 1 THEN
 SHELL "del talk.dat"
 SHELL "copy talkold.dat talk.dat"
 CLS
 LOCATE 15, 20: PRINT ">> 现在聊天室中空无一人"
 LOCATE 16, 20: PRINT "?? 你现在想进入并且等待其他人的进入吗(Y/N)"
 DO
 answere$ = INKEY$
 LOOP UNTIL answere$ <> ""
 IF answere$ = "n" OR answere$ = "N" THEN GOTO 320 ELSE
ELSE
END IF
KEY(1) OFF
CLS : COLOR 2
LOCATE 1, 32: PRINT "MAIL 聊天室"
LOCATE 2, 30: PRINT "_______________"
LOCATE 3, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 17, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 22, 1: PRINT "-------------------------------------------------------------------------------"
LOCATE 23, 2: PRINT ">> 请输入一个代称"
301
COLOR 14
VIEW PRINT 18 TO 21
302
CLS
INPUT " <请输入你的名字> ", talkname$
CLS
IF talkname$ = "" THEN
 VIEW PRINT 23 TO 25
 PRINT ">> 一定要有一个名字才能进入聊天室"
 PRINT "?? 想进入聊天室吗?(Y/N):"
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
LOCATE 23, 2: PRINT ">> 在<请输入>中输入你想说的话"
LOCATE 24, 2: PRINT "!! 想要退出时请键入 exit"
COLOR 14
talkletterno = 0
310
VIEW PRINT 4 TO 16
CLS
OPEN "talk.dat" FOR INPUT AS #1
DO
INPUT #1, talkload$
PRINT talkload$
talkletterno = talkletterno + 1
IF INKEY$ = CHR$(27) THEN GOTO 320
LOOP UNTIL EOF(1) = -1
CLOSE #1
IF talkletterno >= 66666 THEN
 SHELL "del talk.dat"
 SHELL "copy talkold.dat talk.dat"
 talkletterno = 0
 OPEN "talkcont.dat" FOR OUTPUT AS #1
 WRITE #1, 0
 CLOSE #1
 CLS
 OPEN "talk.dat" FOR INPUT AS #1
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
LINE INPUT " <请输入> ", talksent$
IF LCASE$(talksent$) = "exit" THEN GOTO 320
OPEN "talk.dat" FOR APPEND AS #1
WRITE #1, talkname$ + ": " + talksent$
WRITE #1, "                                                     [ " + TIME$ + "/" + DATE$ + " ]"
CLOSE #1
CLS
GOTO 310
320
CLOSE #1
talkcont = talkcont - 1
OPEN "talkcont.dat" FOR OUTPUT AS #1
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
LOCATE 1, 31: PRINT "有关MAIL的帮助"
LOCATE 2, 29: PRINT "__________________"
PRINT " 一.本站点特色:"
PRINT "    1.站点提供的是全中文界面."
PRINT "    2.对使用者的个人信息完全保密.当与他人联系时,只需透露电子邮件地址或一个代称,"
PRINT "      而无需透露真实姓名."
PRINT " 二.其中包括四大部件:"
PRINT "    1.电子邮件"
PRINT "      发送和接收个人信件 (新用户需先注册一个信箱)"
PRINT "    2.电子公告牌"
PRINT "      浏览和张贴所需的信息 (例如:寻物启事,交友信息等等)"
PRINT "    3.聊天室"
PRINT "      即时的与其他人谈古论今,休闲放松"
PRINT "    4.打字游戏"
PRINT "      供休闲娱乐用."
PRINT " 三.具体使用方法:"
PRINT "      注意字符   在本站为非法字符,不得使用.其它请随时注意屏幕底行的提示信息"
PRINT "!! 注意:如果希望得到本站更详细的资料,请给管理员发一个邮件,格式如下:"
PRINT "        <主要内容> MAIL的资料目录"
PRINT "        <收信人> MAIL"
PRINT "    在<正文>中键入任意字符,您就会马上得到系统给您的自动回复."
PRINT
PRINT "                                    ----  系统管理员邮件地址: MAIL"
LOCATE 24, 2: PRINT ">> 按任意键返回主菜单......"
LOCATE 17, 16: PRINT CHR$(34)
DO
LOOP UNTIL INKEY$ <> ""
VIEW PRINT
GOTO 10
TIMER ON
2000
OPEN "caleno.dat" FOR INPUT AS #1
INPUT #1, Caleno
CLOSE #1
LOCATE 23, 60: PRINT "[ 计数器: "; Caleno + 1; "]"
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
a$ = INKEY$
IF a$ <> "" THEN RETURN
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
LOCATE 13, 30: PRINT "1.小写字母"
LOCATE 14, 30: PRINT "2.大小写字母"
LOCATE 15, 30: PRINT "3.大小写字母与数字"
LOCATE 16, 30: PRINT "4.所有符号键"
3011
LOCATE 11, 29: PRINT "请输入打字范围: "
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
LOCATE 15, 30: PRINT "打字速度 (1-9):"
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
LOCATE 19, 30: PRINT "*  打字游戏  *"
LOCATE 20, 30: PRINT "**************"
LOCATE 18, 55: PRINT "速度:"; 10 - speed / 2500
LOCATE 20, 55: PRINT "难度:"; howmanyword
LOCATE 23, 2: PRINT ">> 按<ESC>键退出"
LOCATE 3, 1: PRINT "_______________________________________________________________________________"
LOCATE 16, 1: PRINT "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
VIEW PRINT 4 TO 15
CLS
COLOR 13
LOCATE 10, 27: PRINT "准备好后按任意键继续......"
'LOCATE 11, 28: PRINT "__________________________"
DO
LOOP UNTIL INKEY$ <> ""
COLOR 7
VIEW PRINT
LOCATE 1, 30: PRINT "命中: 0 个"
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
 LOCATE 1, 35: PRINT "命中: "; winno; "个"
 LOCATE 1, 65: PRINT "时间: "; INT(10 * usetime2) / 10; "秒"
 LOCATE 1, 1: PRINT "总的下落字符数: "; wordno; "个"
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
LOCATE 1, 35: PRINT "命中: "; winno; "个"
GOTO 3020
3100
CLS
VIEW PRINT
IF usetime2 < 1 THEN
 LOCATE 9, 27: PRINT "时间太短!不记成绩"
 LOCATE 11, 27: PRINT ">> 按任意键继续......"
 DO
 LOOP UNTIL INKEY$ <> ""
 GOTO 10
ELSE
END IF
IF wordno = 0 OR winno = 0 THEN
 LOCATE 9, 27: PRINT "未进行打字!不记成绩"
 LOCATE 11, 27: PRINT ">> 按任意键继续......"
 DO
 LOOP UNTIL INKEY$ <> ""
 GOTO 10
ELSE
END IF
LOCATE 10, 25: PRINT "命中率: "; INT(10000 * winno / wordno) / 100; "%"
LOCATE 11, 25: PRINT "打字速度 (只算命中的): "; FIX(winno * 60 / usetime2); "个/分"
LOCATE 12, 25: PRINT "打字成绩 :"; FIX(((winno / wordno + 1) * 100 * (winno * 60 / usetime2)) / 100); "分"
LOCATE 14, 25: PRINT ">> 按任意键继续......"
rplay1 = FIX(((winno / wordno + 1) * 100 * (winno * 60 / usetime2)) / 100)
timedate$ = "[ " + TIME$ + "/" + DATE$ + " ]"
DO
LOOP UNTIL INKEY$ <> ""
OPEN "rplay1.dat" FOR INPUT AS #1
INPUT #1, roldplayname$
INPUT #1, roldplay1
INPUT #1, roldtimedate$
CLOSE #1
IF roldplay1 < rplay1 THEN
 CLS
 COLOR 5
 LOCATE 5, 24: PRINT "*****************************"
 LOCATE 6, 24: PRINT "*                           *"
 LOCATE 7, 24: PRINT "* 您打破了原有的最高记录!!! *"
 LOCATE 8, 24: PRINT "*                           *"
 LOCATE 9, 24: PRINT "*      --- 祝贺您 ---       *"
 LOCATE 10, 24: PRINT "*                           *"
 LOCATE 11, 24: PRINT "*****************************"
 LOCATE 17, 25: INPUT "请输入您的尊姓大名：", rplayname$
 OPEN "rplay1.dat" FOR OUTPUT AS #1
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
LOCATE 10, 22: PRINT "最高记录保持者：", roldplayname$
LOCATE 12, 22: PRINT "最高得分：      ", roldplay1
LOCATE 14, 22: PRINT "破记录时间：    ", roldtimedate$
LOCATE 20, 25: PRINT ">> 按任意键继续......"
DO
LOOP UNTIL INKEY$ <> ""
GOTO 10
100015
RETURN
100016
RETURN
100017
RETURN

