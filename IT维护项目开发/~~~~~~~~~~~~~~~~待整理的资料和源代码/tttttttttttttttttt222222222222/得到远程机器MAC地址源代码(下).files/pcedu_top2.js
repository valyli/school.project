var menus=new Array(15)
menus[0]='<a href="http://www.pconline.com.cn"><font color="#FFffff">首　　页</font></a>'
menus[1]='<a href="http://www.pconline.com.cn/digital/"><font color="#FFffff">数码世界</font></a>'
menus[2]='<a href="http://www.pconline.com.cn/mobile/"><font color="#FFffff">手机通讯</font></a>'
menus[3]='<a href="http://www.pconline.com.cn/pchardware/"><font color="#FFffff">硬件资讯</font></a>'
menus[4]='<a href="http://www.pconline.com.cn/pcjob/"><font color="#FFffff">招聘与培训</font></a>'
menus[5]='<a href="http://www.pconline.com.cn/games/"><font color="#FFffff">游戏天下</font></a>'
menus[6]='<a href="http://www.pconline.com.cn/pcedu/"><font color="#FFcc00">网络学院</font></a>'
menus[7]='<a href="http://www8.pconline.com.cn/download/"><font color="#FFffff">下载中心</font></a>'
menus[8]='<a href="http://www.pconline.com.cn/yp/"><font color="#FFffff">商家查询</font></a>'
menus[9]='<a href="http://www.pconline.com.cn/news/"><font color="#FFffff">科技动态</font></a>'
menus[10]='<a href="http://www.pconline.com.cn/notebook/"><font color="#FFffff">笔 记 本</font></a>'
menus[11]='<a href="http://www.pconline.com.cn/pchardware/salon/"><font color="#FFffff">教你买电脑</font></a>'
menus[12]='<a href="http://www.pconline.com.cn/tpylab/"><font color="#FFffff">评 测 室</font></a>'
menus[13]='<a href="http://www.pconline.com.cn/sms/"><font color="#FFffff">短信中心</font></a>'
menus[14]='<a href="http://www.pcauto.com.cn/" target=_blank><IMG SRC=http://www.pconline.com.cn/images/2002/pconline/pcauto_5014.gif WIDTH=50 HEIGHT=14 BORDER=0 HSPACE="0" VSPACE="0"></a>'
var ad_0='<a href="http://www.pcauto.com.cn/" target="_blank"><img src="http://www.pconline.com.cn/images/2002/pconline/pcauto20.gif" vspace=5 width="151" height="20" border=0></a>'

document.write ('</td></tr></table></td></tr></table></div><table width="760" border="0" cellspacing="0" cellpadding="0" align="center" bgcolor="#FFa200"><tr><td bgcolor="#FFDDA2" rowspan="3" width="1"><img src="http://www.pconline.com.cn/images/blank.gif" width="1" height="1"></td><td bgcolor="FFDDA2" height="1" colspan="2"></td><td rowspan="3" align="right" width="576" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0"><tr><td width="44" valign="top"><img src="http://www.pconline.com.cn/images/menu_left.gif" width="44" height="39"></td><td valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0" height="39"><tr>');
document.write ('<td bgcolor="A2A5A7" height="1"></td></tr><tr><td height="37" bgcolor="5D6367" style="LINE-HEIGHT: 18px">');
for (var i=0; i<7;i++ ){
 document.write(menus[i]+"<font color=#FFFFFF> | </font>");}
document.write(menus[7]);
document.write ('<TABLE WIDTH="100%" BORDER="0" CELLSPACING="0" CELLPADDING="0"><TR><TD WIDTH="90%">');
document.write ('<a href="###"  onMouseOver="MM_showHideLayers(\'price\',\'\',\'show\')" onMouseOut="MM_showHideLayers(\'price\',\'\',\'hide\')" ><font color="#FFffff">今日报价</font></a>');

for (var ii=8; ii<14;ii++ ){
 document.write("<font color=#FFFFFF> | </font>"+menus[ii]);}

document.write("<font color=#FFFFFF> | </font></td><td>"+menus[14]+"</td></tr></table>");

document.write ('</td></tr><tr><td bgcolor="FFDDA2" height="1"></td></tr></table></td>');
document.write ('<td width="6" align="right"><img src="http://www.pconline.com.cn/images/menu_right.gif" width="6" height="39"></td></tr></table><table width="100%" border="0" cellspacing="0" cellpadding="0" height="0" align="left" class="dingwei" bgcolor="ffa200"><tr><td  width="39"></td><td  width="536">');


document.write (' <div id=price onMouseOver="MM_showHideLayers(\'price\',\'\',\'show\')" style="Z-INDEX:10; VISIBILITY: hidden; WIDTH: 58px; POSITION: absolute; HEIGHT: 55px; top: -19" onMouseOut=myout()> ');
document.write ('<table   onMouseOut=myout() onMouseOver="MM_showHideLayers(\'price\',\'\',\'show\')" cellspacing=0 cellpadding=0 width="100%" border=0><tr><td  onMouseOver=myin() onMouseOut=myout()  align=center><table cellspacing=0 cellpadding=0 width="100%" border=0><tr> ');
document.write ('<td bgcolor=#ffffcc  onMouseOver=myin() onMouseOut=myout() > ');

document.write ('<table   cellspacing=1 cellpadding=0 width="100%" bgcolor=#5D6367 border=0><tr><td align=center><font color="#FFffff">今日报价</font></td></tr><tr><td bgcolor=#ffffcc align=center class=sfont> ');
document.write ('<a onMouseOver=myin() onMouseOut=myout() href="http://www.pconline.com.cn/market/bj/">北京报价</a><br>');
document.write ('<a onMouseOver=myin() onMouseOut=myout() href="http://www.pconline.com.cn/market/sh/">上海报价</a><br>');
document.write ('<a onMouseOver=myin() onMouseOut=myout() href="http://www.pconline.com.cn/market/gz/">广州报价</a><br>');
document.write ('<a onMouseOver=myin() onMouseOut=myout() href="http://www.pconline.com.cn/market/sz/">深圳报价</a><br><a onMouseOver=myin() onMouseOut=myout() href="http://www.pconline.com.cn/market/nn/">南宁报价</a> ');

document.write ('</td> </tr></table></td> </tr></table></table></div>');
document.write ('</td><td height="7" align="right" width="1" bgcolor="FFDDA2"></td></tr></table></td></tr><tr>');
document.write ('<td align="center"  height=40  width="185" bgcolor="ffa200">');
document.write (ad_0);
document.write ('</td></tr></table><center>');