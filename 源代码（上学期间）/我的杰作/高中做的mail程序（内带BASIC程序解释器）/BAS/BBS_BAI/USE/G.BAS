CLS : num$ = "g"
   
    PRINT : PRINT : PRINT : PRINT : PRINT
    PRINT "*****************************************************************************"
    PRINT "**********            欢迎使用此网络系统                          ***********"
    PRINT "**********                                                        ***********"
    PRINT "**********                           制做者:高二(1)班 白光        ***********"
    PRINT "**********                                                        ***********"
    PRINT "**********                       于1998年5月17日编写完成          ***********"
    PRINT "**********                                                        ***********"
    PRINT "*****************************************************************************"
  LOCATE 16, 20
  INPUT "请输入您的姓名,然后按回车:", name$
   CLS
   GOTO 20
   DO
   VIEW PRINT 1 TO 25
   LOCATE 1, 1: PRINT "***********************网络联接程序********************************************"
   LOCATE 13, 1: PRINT "**********************您的网络名是" + name$ + "  **************************************"
   LOCATE 24, 1
   PRINT "       打 exit 退出       打 cls 清屏      打 help 看帮助信息"
   VIEW PRINT 2 TO 12
10 LOCATE 12, 1
   INPUT "请输入:", a$
   IF a$ = "help" OR a$ = "HELP" THEN GOSUB 250
   IF a$ = "exit" OR a$ = "EXIT" THEN GOTO 200
   IF a$ = "cls" OR a$ = "CLS" THEN CLS : GOTO 10
   IF a$ = "" THEN GOTO 30
20 OPEN "m:\bbs\dat\" + num$ + ".dat" FOR OUTPUT AS #1
   WRITE #1, name$ + "->" + a$
   CLOSE #1
   OPEN "m:\bbs\dat\text.dat" FOR APPEND AS #1
   PRINT #1, name$ + "->" + a$ + "        " + DATE$ + TIME$
   CLOSE #1
30 VIEW PRINT 15 TO 23
   FOR i = 97 TO 122
   B$ = "m:\bbs\dat\" + CHR$(i) + ".dat"
   OPEN B$ FOR INPUT AS #1
   INPUT #1, c$
   CLOSE #1
   LOCATE 23, 1
   IF c$ <> " " THEN PRINT c$
   NEXT i
   LOOP
200 VIEW PRINT 1 TO 25
    CLS
    FOR i = 97 TO 122
    m$ = "m:\bbs\dat\" + CHR$(i) + ".dat"
    OPEN m$ FOR OUTPUT AS #1
    WRITE #1, " "
    CLOSE
    NEXT i
    PRINT : PRINT : PRINT : PRINT : PRINT
    PRINT "*****************************************************************************"
    PRINT "**********            欢迎使用此网络系统                          ***********"
    PRINT "**********                                                        ***********"
    PRINT "**********                           制做者:高二(1)班 白光        ***********"
    PRINT "**********                                                        ***********"
    PRINT "**********                       于1998年5月17日编写完成          ***********"
    PRINT "**********                                                        ***********"
    PRINT "*****************************************************************************"
    SYSTEM
250 PRINT "                       帮助信息                   "
    PRINT "         本软件是由九六届宏志班的学生白光于1998年5月17日编写完成,   "
    PRINT "     其中也有李佳等人参与编写,希望用户爱护此软件."
    PRINT "         这是个网络聊天程序,最多可以十个人同时使用,以便互相对话,"
    PRINT "     只要在光标后输入字符或汉字,按回车后其他人即会马上看到"
    PRINT "         进入系统的方法是:只要在任何机器的M:\盘DOS下输入BBS并"
    PRINT "     按回车即可."
    PRINT "                         按ESC键退出帮助"
    DO WHILE INKEY$ <> CHR$(27): LOOP
    CLS
    RETURN

