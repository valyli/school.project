var title_l=new Array(7)
var url_l=new Array(7)
var title_r=new Array(7)
var url_r=new Array(7)
var owin="target=_blank"
var img="<font color='#33333'>·</font>"

url_l[0]='http://www.pconline.com.cn/news/'
url_l[1]='http://www.pconline.com.cn/news/'
url_l[2]='http://www.pconline.com.cn/pchardware/'
url_l[3]='http://www.pconline.com.cn/pchardware/'
url_l[4]='http://www.pconline.com.cn/digital/'
url_l[5]='http://www.pconline.com.cn/digital/'
url_l[6]='http://www.pconline.com.cn/mobile/'

url_r[0]='http://www.pconline.com.cn/notebook/'
url_r[1]='http://www.pconline.com.cn/pcedu/'
url_r[2]='http://www.pconline.com.cn/pcedu/'
url_r[3]='http://www.pconline.com.cn/games/'
url_r[4]='http://www.pconline.com.cn/games/'
url_r[5]='http://www.pconline.com.cn/pcjob/'
url_r[6]='http://www.pconline.com.cn/pcjob/'
	
	
title_l[0]='[真实笑话]见识一下真正BT型的电脑玩家'
title_l[1]='红色警戒和街霸之主Virgin快完蛋了'
title_l[2]='ATI发布镭9800、9600、9200系列显卡'
title_l[3]='3D Mark03测试篇'
title_l[4]='让女孩心动不已的明基MP3 Joybee'
title_l[5]='[葵花宝典] 如何用DV摄像机赚钱 '
title_l[6]='[火热]混音与色彩的诱惑 MOTOC350测评'

title_r[0]='[经典再现]SHARP超轻薄笔记本'
title_r[1]='[组网] 无盘多媒体教学网络的设计'
title_r[2]='[设计] 网上电影发布步步进'
title_r[3]='吐血推荐 国粹经典：大闹天宫年画清晰版'
title_r[4]='[游戏]超近距离接触《仙剑奇侠传3》'
title_r[5]='垫背难找 就业一切从毁约开始!'
title_r[6]='[MM着装示范]巧花心思,成就白领新鲜丽人'



document.write("<table width='98%' border='1' cellspacing='0' cellpadding='5' align='center' bordercolorlight='#000000' bordercolordark='#FFFFFF'> <tr align='center' bgcolor='#AAAA00'> <td colspan='2'><b><font color='#FFFFFF'>太平洋热点推荐</font></b></td> </tr> <tr> <td class='sfont' background='/images/point.gif' width='50%'>");

for (var i=0; i<7;i++ ){
 document.write(img+" "+"<a href='"+url_l[i]+"' target='_blank'>"+title_l[i]+"</a><br>");}	

document.write("</td><td class='sfont' background='/images/point.gif'>");

for (var i=0; i<7;i++ ){
 document.write(img+" "+"<a href='"+url_r[i]+"' target='_blank'>"+title_r[i]+"</a><br>");
					}	

document.write("</td></tr></table>");
document.write('<br><iframe src=http://www.pconline.com.cn/sms/ad_main/ad.html SCROLLING="no" WIDTH="550" HEIGHT="280"  MARGINWIDTH="0" MARGINHEIGHT="0" FRAMEBORDER="0"  ></iframe>');
		