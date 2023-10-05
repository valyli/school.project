//Modified by LM 02-9-25 15:02
//改变函数名称，防止与sohu、netease的广告冲突。

function tomgetuser(src)
{
	var I = src.substr(src.indexOf("?tomuserid=") + 11).length;
	
	if (0 >= I) return -1;
	if (I == src.length) return -1;
	return src.substr(src.indexOf("?tomuserid=") + 11,src.indexOf("&tomusername=") - src.indexOf("?tomuserid=") - 11);
}

function tomgetuname(src)
{
	var I = src.substr(src.indexOf("&tomusername=") + 13).length;
	var T = src.indexOf("&tomusername=");
	if (0 >= T) return "";
	if (I == src.length) return -1;
	return src.substr(src.indexOf("&tomusername=") + 13);
}

function tomgourl(urls, Height, Width)
{
	var I,i;

	for (i=0;i<document.scripts.length;i++)
	{
		if (null != document.scripts[i].src)	
		{
			I = tomgetuser(document.scripts[i].src);
			if (0 < I)
			{
				break;
			}	
		}
	}
	
	if (0 >= I)
	{
		window.open(urls,'','height=' + Height + ' ,width=' + Width + ',resizable=no,location=yes');
	}
	else
	{
		urls= urls + "&user_id=" + I;
		window.open(urls,'','height=' + Height + ' ,width=' + Width + ',resizable=no,location=yes');
	}

}

function tomgo(urls)
{
	var I,i;

	for (i=0;i<document.scripts.length;i++)
	{
		if (null != document.scripts[i].src)	
		{
			I = tomgetuser(document.scripts[i].src);
			if (0 < I)
			{
				break;
			}	
		}
	}
	
	if (0 >= I)
	{
		window.open(urls);
	}
	else
	{
		urls= urls + "&user_id=" + I;
		window.open(urls);
	}

}

function tomgologin(urls, Height, Width)
{
	var I,i;

	for (i=0;i<document.scripts.length;i++)
	{
		if (null != document.scripts[i].src)	
		{
			I = tomgetuname(document.scripts[i].src);
			if (0 < I.length)
			{
				break;
			}	
		}
	}

	urls= urls + "?up_line=" + I;
	open(urls,'','height=' + Height + ' ,width=' + Width + ',location=yes,scrollbars=yes');
}

function tom_sms_goto(order,inc,type,cata,page)
{
	var bt="",special_flag=1;
	var I,i;

	for (i=0;i<document.scripts.length;i++)
	{
		if (null != document.scripts[i].src)	
		{
			I = tomgetuser(document.scripts[i].src);
			if (0 < I)
			{
				break;
			}	
		}
	}
	
	if ((type==45)||(type==46)||(type==39)||(type==43)||(type==44)||(type==41)||(type==42)||(type==52)||(type==53)||(type==54)||(type==55)||(type==56)){bt="color_pic";};
	if ((type==47)||(type==40)||(type==50)||(type==51)||(type==57)||(type==59)){bt="hexuan";};
	if ((type==51)||(type==55)||(type==56)||(type==54)||(type==53)){special_flag=2;};
	urls="sms_" + order + "_" + inc + "_" + type + "_" + cata + "_" + page + ".htm?user_id="+I + "&bt=" +bt+'&special_flag='+special_flag;
	fu_urls="http://usms.tom.com/smslist/"+urls;
	open(fu_urls,'_blank','');
}

function sms_send1(inc,type,id,key)           
{
	var bt="",special_flag=1;
	var I,i;

	for (i=0;i<document.scripts.length;i++)
	{
		if (null != document.scripts[i].src)	
		{
			I = tomgetuser(document.scripts[i].src);
			if (0 < I)
			{
				break;
			}	
		}
	}
	
	var bt="",pf="u_lingsheng_step0",special_flag=0;
	if ((type==45)||(type==46)||(type==39)||(type==43)||(type==44)||(type==41)||(type==42)||(type==52)||(type==53)||(type==54)||(type==55)||(type==56)){bt="color_pic";special_flag=1;};
	if ((type==47)||(type==40)||(type==50)||(type==51)||(type==57)||(type==59)){bt="hexuan";special_flag=1;};
	if ((type==51)||(type==55)||(type==56)||(type==54)||(type==53)){special_flag=2;};

	if (inc==1){pf="v7n_yanyu_step0";};
	if (inc==2){pf="v7n_tupian_step0";};
	if (inc==3){pf="v7n_lingsheng_step0";};
	window.open('http://sms.tom.com/'+pf+'.php?inc='+inc+'&type='+type+'&id='+id+'&user_id='+I+'&var='+key+'&bt='+bt+'&special_flag='+special_flag,'','height=180,width=450,resizable=no,location=yes');
	
}
document.write("<head><meta http-equiv=\'Content-Type\' content=\'text/html; charset=gb2312\'></head>");
document.write("<style type=\"text/css\">");
document.write(".px14 {  font-size: 14px}");
document.write(".sms p {line-height: 150%}");
document.write(".sms  {  font-size: 12px}");
document.write(".sms a:link {color: #003333;text-decoration:underline}");
document.write(".sms a:visited { color: #000000; text-decoration:underline}");
document.write(".sms a:hover {color:#ff0000;text-decoration:underline}");
document.write(".sms a:active {color: #003333; text-decoration:underline}");
document.write("</style>");
document.write("<table class=sms  width=\"155\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" bgcolor=\"#003333\">");
document.write("  <tr> ");
document.write("    <td width=\"84\" style=\"font-size: 12.9px; color: #ccff99\"><a href style=\"cursor: hand ; text-decoration: none\" onClick=\"tomgologin(\'http://usms.tom.com/login.php\',600,780)\"><font color=\"#ccff99\">&nbsp;SMS.TOM.COM</font></a></td>");
document.write("    <td width=\"71\" align=\"right\">");
document.write("<a href=\"#\" style=\"cursor: hand ; text-decoration: none\" onclick=\"tomgourl(\'http://usms.tom.com/wxqy_gif_js_76.php?\',300,300);\">");
document.write("<font color=\"ff9966\">无限情缘</font>");
document.write("</a>&nbsp;</td>");
document.write("  </tr>");
document.write("</table>");
document.write("<table class=sms  width=\"155\" border=\"0\" cellspacing=\"1\" cellpadding=\"0\" align=\"center\" bgcolor=\"003333\">");
document.write("  <tr bgcolor=\"#FFFFFF\"> ");
document.write("    <td>");
document.write("      <table class=sms  width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" background=\"http://usmsad.tom.com/usmsweb/images/js_pic/bg_snow.jpg\">");
document.write("        <tr> ");
document.write("          <td width=\"76\"><a href style=\"cursor: hand\" onClick=\"tom_sms_goto(0,3,6,0,1);\"><font color=red>手机铃声</font></a></td>");
document.write("          <td width=\"74\"><a href style=\"cursor: hand\" onClick=\"tom_sms_goto(0,2,3,0,1);\"><font color=red>诺基亚大图</font></a></td>");
document.write("        </tr>");
document.write("        <tr> ");
document.write("          <td colspan=4> ");
document.write("            <table class=sms  width=\"\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\">");
document.write("              <tr> ");
document.write("              <tr> ");
document.write("                <td width=\"83\" style=\"line-height:140%;padding: 0px 0px 0px 0px\" valign=\"middle\"> ");
document.write("                  <p style=\"line-height: 150%\">");
document.write("<a href style=\"cursor:hand;\" onClick=\"sms_send1(3,10,35713,\'1%26inc%3D3%26type%3D10%26code%3D7%26pid%3D3998%26id10%3D33201%26id10%3D33676%26id10%3D34151%26id3%3D35535%26id1%3D35713%26id5%3D35714%26id6%3D35715%26id7%3D35716%26id4%3D35717\');\">HappyBaby</a><br>");
document.write("<a href style=\"cursor:hand;\" onClick=\"sms_send1(3,10,34963,\'1%26inc%3D3%26type%3D10%26code%3D7%26pid%3D3998%26id3%3D34900%26id4%3D34962%26id1%3D34963%26id5%3D34964%26id7%3D34965%26id6%3D34966%26id10%3D34967\');\">一句到尾</a><br>");
document.write("<a href style=\"cursor:hand;\" onClick=\"sms_send1(3,10,34939,\'1%26inc%3D3%26type%3D10%26code%3D7%26pid%3D3998%26id3%3D34901%26id4%3D34938%26id1%3D34939%26id5%3D34940%26id7%3D34941%26id6%3D34942%26id10%3D34943%26id27%3D35666%26id12%3D35903%26id18%3D35950\');\">你最红</a><br>");
document.write("<a href style=\"cursor:hand;\" onClick=\"sms_send1(3,10,34802,\'1%26inc%3D3%26type%3D10%26code%3D7%26pid%3D3998%26id3%3D34651%26id1%3D34802%26id4%3D34803%26id5%3D34804%26id7%3D34805%26id6%3D34806%26id10%3D34807%26id2%3D34833\');\">最佳位置</a><br>");
document.write("<a href style=\"cursor:hand;\" onClick=\"sms_send1(3,10,34784,\'1%26inc%3D3%26type%3D10%26code%3D7%26pid%3D3998%26id3%3D34648%26id1%3D34784%26id4%3D34785%26id5%3D34786%26id7%3D34787%26id6%3D34788%26id10%3D34789%26id2%3D34830%26id12%3D35918%26id18%3D35965\');\">烟花(Swing)</a><br>");
document.write("<a href style=\"cursor:hand;\" onClick=\"sms_send1(3,10,35778,\'1%26inc%3D3%26type%3D10%26code%3D7%26pid%3D3998%26id2%3D0%26id1%3D336%26id3%3D1500%26id5%3D4156%26id6%3D11835%26id10%3D21486%26id15%3D26802%26id3%3D31331\');\">Your Body Is</a><br>");
document.write("<a href style=\"cursor:hand;\" onClick=\"sms_send1(3,10,35809,\'1%26inc%3D3%26type%3D10%26code%3D7%26pid%3D3998%26id10%3D33257%26id10%3D33732%26id10%3D34207%26id1%3D35809%26id5%3D35810%26id6%3D35811%26id7%3D35812%26id4%3D35813%26id3%3D35859\');\">梦的点滴</a><br>");
document.write("<a href style=\"cursor:hand;\" onClick=\"sms_send1(3,10,35319,\'1%26inc%3D3%26type%3D10%26code%3D7%26pid%3D3998%26id2%3D0%26id1%3D336%26id3%3D1500%26id5%3D4156%26id6%3D11835%26id10%3D21486%26id15%3D26802%26id3%3D31331\');\">在他乡</a><br>");
document.write("<a href style=\"cursor:hand;\" onClick=\"sms_send1(3,10,24809,\'1%26inc%3D3%26type%3D10%26code%3D7%26pid%3D3998%26id2%3D0%26id1%3D336%26id3%3D1500%26id5%3D4156%26id6%3D11835%26id10%3D21486%26id15%3D26802%26id3%3D31331\');\">花香(薰衣草)</a></p>");
document.write("                </td>");
document.write("                <td width=\"72\" valign=\"middle\">");
document.write("                        <img src=\"http://usmsad.tom.com/usmsweb/images/js_pic/155_224_pic1.gif\" width=\"74\" height=\"166\" border=\"0\"  usemap=\"#155_224_Map1\" >");
document.write("                          <map name=\"155_224_Map1\">");
document.write("                            <area shape=\"rect\" coords=\"1, 1,  74, 30 \" target=\"_self\" href=\"javascript:sms_send1(2,3,29625,\'1%26inc%3D2%26type%3D3%26code%3D7%26id%3D29625%26pid%3D4006\');\">");
document.write("                            <area shape=\"rect\" coords=\"1, 35, 74, 64 \" target=\"_self\" href=\"javascript:sms_send1(2,3,27219,\'1%26inc%3D2%26type%3D3%26code%3D7%26id%3D27219%26pid%3D4006\');\"> ");
document.write("                            <area shape=\"rect\" coords=\"1, 69, 74, 98 \" target=\"_self\" href=\"javascript:sms_send1(2,3,29627,\'1%26inc%3D2%26type%3D3%26code%3D7%26id%3D29627%26pid%3D4006\');\">");
document.write("                            <area shape=\"rect\" coords=\"1, 103,74, 132\" target=\"_self\" href=\"javascript:sms_send1(2,3,29681,\'1%26inc%3D2%26type%3D3%26code%3D7%26id%3D29681%26pid%3D4006\');\">");
document.write("                            <area shape=\"rect\" coords=\"1, 137,74, 166\" target=\"_self\" href=\"javascript:sms_send1(2,3,29679,\'1%26inc%3D2%26type%3D3%26code%3D7%26id%3D29679%26pid%3D4006\');\"> ");
document.write("                          </map>");
document.write("                </td>");
document.write("              </tr>");
document.write("            </table>");
document.write("          </td>");
document.write("        </tr>");
document.write("      </table>");
document.write("    </td>");
document.write("  </tr>");
document.write("</table>");