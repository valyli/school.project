for (i=0;i<document.scripts.length;i++)
{
	if (null != document.scripts[i].src)	
	{
		user_id = document.scripts[i].src.substr(document.scripts[i].src.indexOf("?tom_user_id=") + 13);
		if (0 < user_id)
		{
			break;
		}	
	}
}

document.write("<style>");
document.write(".input {");
document.write("	BACKGROUND: #E5F2FF; BORDER-BOTTOM: rgb(56,121,187) 1px solid; BORDER-LEFT: rgb(56,121,187) 1px solid; BORDER-RIGHT: rgb(56,121,187) 1px solid; BORDER-TOP: rgb(56,121,187) 1px solid; COLOR: #003333; font-size: 9pt;");
document.write("	}");
document.write("</style>");
document.write("<table width=\"115\" border=\"0\" cellspacing=\"0\" cellpadding=\"2\" align=\"center\">");
document.write("    <form name=\"form2\" method=\"get\" target=\"_blank\" action=\"http://usms.tom.com/smslist/smsearch.php\"><tr> ");
document.write("      <td colspan=\"2\"> ");
document.write("        <p> ");
document.write("		<select name=\"inc\" class=input>");
document.write("		  <option value=\"3\" selected> ÷ª˙¡Â…˘ ");
document.write("		  <option value=\"2\"> ÷ª˙Õº∆¨ ");
document.write("		  <option value=\"1\">—‘”Ô¥´«È ");
document.write("		</select>");
document.write("        </p>");
document.write("      </td>");
document.write("    </tr>");
document.write("    <tr> ");
document.write("      <td> ");
document.write("        <input type=\"text\" name=\"keyword\" value=\"«Î ‰»Îπÿº¸◊÷\" size=\"12\" class=input onMouseOver=\"javascript: if (this.value=='«Î ‰»Îπÿº¸◊÷’“¡Â…˘')this.value='';this.select()\" onMouseOut=\"javascript: if (this.value==''){this.value='«Î ‰»Îπÿº¸◊÷’“¡Â…˘';this.blur();}\">");
document.write("        <input type=hidden name=user_id value=\""+user_id+"\">");
document.write("      </td>");
document.write("      <td width=\"20\" valign=\"bottom\"><input type=\"image\" src=\"http://usmsad.tom.com/usmsweb/images/enter.gif\"></td>");
document.write("    </tr></form>");
document.write("</table>");