document.write("<!-- saved from url=(0022)http://internet.e-mail -->");
document.write("<html>");
document.write("<head>");
document.write("<title>������Ե</title>");
document.write("<meta http-equiv='Content-Type' content='text/html; charset=gb2312'>");
document.write("</head>");
document.write("");
document.write("<body bgcolor='#FFFFFF' >");
document.write("<form name=\"form3\" id='wxqy_subscribe_new_flash' method='post' onsubmit='return false'>");
document.write("<table width='300' border='0' cellspacing='0' cellpadding='0' height='300' bgcolor='#000000' align='center'>");
document.write("  <tr>");
document.write("    <td>");
document.write("      <table width='298' border='0' cellspacing='0' cellpadding='0' align='center'>");
document.write("        <tr> ");
document.write("          <td><object classid='clsid:D27CDB6E-AE6D-11cf-96B8-444553540000' codebase='http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=5,0,0,0' width='298' height='248'>");
document.write("              <param name=movie value='http://usmsad.tom.com/usmsweb/images/sms.swf'>");
document.write("              <param name=quality value=high>");
document.write("              <embed src='http://usmsad.tom.com/usmsweb/images/sms.swf' quality=high pluginspage='http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash' type='application/x-shockwave-flash' width='298' height='248'>");
document.write("              </embed> ");
document.write("            </object></td>");
document.write("        </tr>");
document.write("        <tr> ");
document.write("          <td height='50' bgcolor='#FFFFFF'> ");
document.write("            <table width='85%' border='0' cellspacing='0' cellpadding='4' align='center'>");
document.write("              <tr> ");
document.write("                <td><font color='#000000' style=\"font-size: 12px\" face=\"����\">�ֻ����룺</font></td>");
document.write("                <td><font color='135D5D'> ");
document.write("                  <input type='text' name='user' size='10' class=input>");
document.write("                  </font></td>");
document.write("                <td><input type='image' src='http://usmsad.tom.com/usmsweb/images/ksyh.gif' width='70' height='20' onclick='tom_check_form2_flash()'></td>");
document.write("              </tr>");
document.write("            </table>");
document.write("          </td>");
document.write("        </tr>");
document.write("                      <!--�����Ĳ���-->");
document.write("					<input type='hidden' name='subscribe_1' value='4838'>");
document.write("					<input name='confirm' type='hidden' value='1'>");
document.write("					<input name='num' type='hidden' value='1'>");
document.write("					 <input name='vgirl_9yuan' type='hidden' value='1'>");
document.write("					 <input name='user_id' type='hidden' value=''>");
document.write(" 					 <input name='code_id' type='hidden' value='74'>");
document.write("					 <input name='type' type='hidden' value='48'>");
document.write("					 <input name='inc' type='hidden' value='4'>");
document.write("					 <input name='id' type='hidden' value='100'>");
document.write("					 <input name='mobile' type='hidden' value='' >");
document.write("					 ");
document.write("					 <input name='from' type='hidden' value='tom'>");
document.write("      </table>");
document.write("    </td>");
document.write("  </tr></form>");
document.write("</table>");
document.write("</body>");
document.write("</html>");

function tom_check_form2_flash()
{
	mobile=form3.user.value ;

	//alert(mobile.length) ;
	if(mobile.length!=11)
	{
		alert("��������ȷ���ֻ����룡") ;
		return false ;
	}	

	mobile_head=mobile.substring(0,3) ;
	if( mobile_head=="131" || mobile_head=="132" || mobile_head=="133")
	{
		alert("��������ʱ������ͨ�û����š�") ;
		//alert(mobile_head) ;
		return false ;
	}	

	/*
	vgirl.mobile.value=mobile ;	//��mobile����������һҳ��
	if(mobile=="")
	{
		alert("�������ֻ����룡") ;
		return false ;
	}
	*/
	
	p=document.scripts.length ;
	for(i=0;i<p;i++)
	{
		x=document.scripts[i].src ;
		
		if(x.indexOf("wxqy_subscribe_new_flash")!="-1")		
		{
			tom_script=document.scripts[i].src ;
			break ;
		}
	}	

	temp=tom_script.substr(tom_script.indexOf("user_id"));
	if (temp==""){temp=tom_script.substr(tom_script.indexOf("tomuserid"));};
	url1=temp.split("&") ;
	//alert(url1[0]) ;
	url2=url1[0].split("=") ;
	user_id=url2[1] ;
	form3.user_id.value=user_id ;
	//alert(user_id) ;
	
	url="http://sms.tom.com/fast_subscribe_wxqy_new.php?user=" + mobile +  "&subscribe_1=4838&confirm=1&num=1&vgirl_9yuan=js&code_id=74&type=48&inc=4&id=100&mobile=" + mobile + "&user_id=" + user_id ;	
	//alert(url) ;
	window.open(url,'TOM_Vgirl','width=300,height=300,location=no') ;
	
}


