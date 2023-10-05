document.write("<!-- saved from url=(0022)http://internet.e-mail -->");
document.write("<html>");
document.write("<head>");
document.write("<title>无限情缘</title>");
document.write("<meta http-equiv='Content-Type' content='text/html; charset=gb2312'>");
document.write("</head>");
document.write("");
document.write("<body bgcolor='#FFFFFF' >");
document.write("<form name=\"form89\" id='form89' method='post' onsubmit='return false'>");
document.write("<table width='168' border='0' cellspacing='0' cellpadding='0' align='center' height='250'>");
document.write("  <tr> ");
document.write("    <td height='193'><img src='http://usmsad.tom.com/usmsweb/images/qtz_dh.gif' width='168' height='193'></td>");
document.write("  </tr>");
document.write("  <tr> ");
document.write("    <td background='http://usmsad.tom.com/usmsweb/images/qtz_bj.gif'>");
document.write("      <table width='90%' border='0' cellspacing='0' cellpadding='0' align='center'>");
document.write("        <tr> ");
document.write("          <td><font color='#000000' style=\"font-size: 12px\" face=\"宋体\">手机参与：</font></td>");
document.write("          <td><font color='135D5D'> ");
document.write("            <input type='text' name='user' size='10' class=input>");
document.write("            </font></td>");
document.write("        </tr>");
document.write("        <tr> ");
document.write("          <td><font color='#FF0000' style=\"font-size: 12px\" face=\"宋体\">做好准备：</font></td>");
document.write("          <td><font color='135D5D'><input type='image' src='http://usmsad.tom.com/usmsweb/images/ksyh.gif' width='70' height='20' onclick='tom_check_form2_qtz()'></font></td>");
document.write("        </tr>");
document.write("                                    <!--所传的参数-->");
document.write("					<input type='hidden' name='subscribe_1' value='4838'>");
document.write("					<input name='confirm' type='hidden' value='1'>");
document.write("					<input name='num' type='hidden' value='1'>");
document.write("					 <input name='vgirl_9yuan' type='hidden' value='1'>");
document.write("					 <input name='user_id' type='hidden' value=''>");
document.write(" 					 <input name='code_id' type='hidden' value='72'>");
document.write("					 <input name='type' type='hidden' value='48'>");
document.write("					 <input name='inc' type='hidden' value='4'>");
document.write("					 <input name='id' type='hidden' value='100'>");
document.write("					 <input name='mobile' type='hidden' value='' >");
document.write("					 ");
document.write("					 <input name='from' type='hidden' value='tom'>");
document.write("      </table>");
document.write("    </td></form>");
document.write("  </tr>");
document.write("</table>");
document.write("</body>");
document.write("</html>");

function tom_check_form2_qtz()
{
	mobile=form89.user.value ;

	//alert(mobile.length) ;
	if(mobile.length!=11)
	{
		alert("请输入正确的手机号码！") ;
		return false ;
	}	

	mobile_head=mobile.substring(0,3) ;
	if( mobile_head=="131" || mobile_head=="132" || mobile_head=="133")
	{
		alert("本服务暂时不对联通用户开放。") ;
		//alert(mobile_head) ;
		return false ;
	}	

	/*
	vgirl.mobile.value=mobile ;	//将mobile参数带到下一页。
	if(mobile=="")
	{
		alert("请输入手机号码！") ;
		return false ;
	}
	*/
	
	p=document.scripts.length ;
	for(i=0;i<p;i++)
	{
		x=document.scripts[i].src ;
		
		if(x.indexOf("qtz")!="-1")		
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
	form89.user_id.value=user_id ;
	//alert(user_id) ;
	
	url="http://sms.tom.com/fast_subscribe_wxqy_new.php?user=" + mobile +  "&subscribe_1=4838&confirm=1&num=1&vgirl_9yuan=js&code_id=72&type=48&inc=4&id=100&mobile=" + mobile + "&user_id=" + user_id ;	
	//alert(url) ;
	window.open(url,'TOM_Vgirl','width=300,height=300,location=no') ;
	
}
