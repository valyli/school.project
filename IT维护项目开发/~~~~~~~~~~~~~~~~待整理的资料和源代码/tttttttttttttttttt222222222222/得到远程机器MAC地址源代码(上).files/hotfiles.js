var title_l=new Array(7)
var url_l=new Array(7)
var title_r=new Array(7)
var url_r=new Array(7)
var owin="target=_blank"
var img="<font color='#33333'>��</font>"

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
	
	
title_l[0]='[��ʵЦ��]��ʶһ������BT�͵ĵ������'
title_l[1]='��ɫ����ͽְ�֮��Virgin���군��'
title_l[2]='ATI������9800��9600��9200ϵ���Կ�'
title_l[3]='3D Mark03����ƪ'
title_l[4]='��Ů���Ķ����ѵ�����MP3 Joybee'
title_l[5]='[��������] �����DV�����׬Ǯ '
title_l[6]='[����]������ɫ�ʵ��ջ� MOTOC350����'

title_r[0]='[��������]SHARP���ᱡ�ʼǱ�'
title_r[1]='[����] ���̶�ý���ѧ��������'
title_r[2]='[���] ���ϵ�Ӱ����������'
title_r[3]='��Ѫ�Ƽ� ���⾭�䣺�����칬�껭������'
title_r[4]='[��Ϸ]��������Ӵ����ɽ�������3��'
title_r[5]='�汳���� ��ҵһ�дӻ�Լ��ʼ!'
title_r[6]='[MM��װʾ��]�ɻ���˼,�ɾͰ�����������'



document.write("<table width='98%' border='1' cellspacing='0' cellpadding='5' align='center' bordercolorlight='#000000' bordercolordark='#FFFFFF'> <tr align='center' bgcolor='#AAAA00'> <td colspan='2'><b><font color='#FFFFFF'>̫ƽ���ȵ��Ƽ�</font></b></td> </tr> <tr> <td class='sfont' background='/images/point.gif' width='50%'>");

for (var i=0; i<7;i++ ){
 document.write(img+" "+"<a href='"+url_l[i]+"' target='_blank'>"+title_l[i]+"</a><br>");}	

document.write("</td><td class='sfont' background='/images/point.gif'>");

for (var i=0; i<7;i++ ){
 document.write(img+" "+"<a href='"+url_r[i]+"' target='_blank'>"+title_r[i]+"</a><br>");
					}	

document.write("</td></tr></table>");
document.write('<br><iframe src=http://www.pconline.com.cn/sms/ad_main/ad.html SCROLLING="no" WIDTH="550" HEIGHT="280"  MARGINWIDTH="0" MARGINHEIGHT="0" FRAMEBORDER="0"  ></iframe>');
		