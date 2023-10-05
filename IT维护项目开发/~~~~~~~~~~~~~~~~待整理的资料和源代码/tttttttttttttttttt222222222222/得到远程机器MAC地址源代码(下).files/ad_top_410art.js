var ad= new Array(2);
ad[0]="<a href='/pcjob/rs/graduate/index.html'target='_blank'> <img src='/images/2002/pconline/gra550.gif' border=0 width='550' height='80' ></a>";
ad[1]="<a href='http://guide.pconline.com.cn/pcguide/rooms.jsp'target='_blank'> <img src='/images/2002/pconline/aq550x80.gif' border=0 width='550' height='80' ></a>";
ad_now = new Date();
ad_id= ad_now.getSeconds() %2;
document.write(ad[ad_id]);

