<!--
var maxswf = 1 ;
var slump = Math.random();
var talet = Math.round(slump * (maxswf-1))+1;
var seed=1;

function create() {
        this.src = ''
}

c = new Array()

for(var i=1; i<=maxswf; i++) { c[i] = new create() }
c[1].src    = "http://btn.pchome.net/kingston/kingston_360x300.swf"
//c[1].src    = "http://btn.pchome.net/huaqi/huaqi_360x300_mini.swf"
//c[2].src    = "http://btn.pchome.net/huaqi/huaqi_360x300_0618.swf"
//c[1].src    = "http://casting6.allyes.com/main/adfshow?user=CP_benq_dvd1650p|CG_pip360300|C_pchome&db=casting6"

function postswf (i) {
if (i+talet >maxswf) {seed=i+talet-maxswf;}
else  {seed=i+talet;}
//document.write('<IFRAME MARGINHEIGHT=0 MARGINWIDTH=0 FRAMEBORDER=0 WIDTH=360 HEIGHT=300 SCROLLING=NO SRC=http://casting6.allyes.com/main/adfshow?user=CP_benq_qdesk1225|CG_button|C_pchome_120180&db=casting6&border=0&local=yes><SCRIPT LANGUAGE="JavaScript1.1" SRC="http://casting6.allyes.com/main/adfshow?user=CP_benq_qdesk1225|CG_button|C_pchome_120180&db=casting6&local=yes&js=on"></SCRIPT><NOSCRIPT><A HREF=http://casting6.allyes.com/main/adfclick?user=CP_benq_qdesk1225|CG_button|C_pchome_120180&db=casting6><IMG SRC=http://casting6.allyes.com/main/adfshow?user=CP_benq_qdesk1225|CG_button|C_pchome_120180&db=casting6 WIDTH=360 HEIGHT=300 BORDER=0></a></NOSCRIPT></IFRAME>')
document.write('<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=5,0,0,0" width="360" height="300">');
document.write('<param name=movie value="'+c[seed].src+'">');
document.write('<param name=quality value=high>');
document.write('<embed src="'+c[seed].src+'" quality=high pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash" type="application/x-shockwave-flash" width="360" height="300">');
document.write('</embed></object>');
}

function postadhead () {

var x=Math.random();   
var i=Math.round(x*8-0.5);   
if (i==0) {
document.write ('<a href="http://www.pchome.net/from.php?userid=16" target="_blank"><img src=http://btn.pchome.net/pchome/eshop_new_760x90.gif border=0 width=745 height=90></a>\r\n');
}   
if (i==1 || i==2) {
document.write ('<a href="http://antivirus.pchome.net/" target="_blank"><img src="http://btn.pchome.net/download/antivirus760_90.jpg" border=0 width=745></a>\r\n');
}   
if (i==3 || i==4) {
document.write ('<noindex><OBJECT CLASSID="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" CODEBASE="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=5,0,0,0" WIDTH="745" HEIGHT="90"><PARAM NAME=movie VALUE="http://btn.pchome.net/pchome/19monitor_760x90.swf"><PARAM NAME=quality VALUE=high><PARAM NAME="salign" VALUE="TL"><PARAM NAME="menu" VALUE="false"><EMBED SRC="http://btn.pchome.net/pchome/19monitor_760x90.swf" QUALITY=high PLUGINSPAGE="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash" TYPE="application/x-shockwave-flash" WIDTH="745" HEIGHT="90" SALIGN="TL" MENU="false"></EMBED></OBJECT></noindex>');
}  
if ( i==5 )
{
document.write ('<a href=http://www.pchome.net/from.php?userid=375 target=_blank><img src=http://btn.pchome.net/pchome/pricewar_760x90.gif border=0 width=745 height=90></a>');
}
if ( i>5 ){
// LG add for  03/03-03/06  03/13-03/14  03/17-03/20
document.write ('<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" width="745"  height="90"><param name=movie value="http://btn.pchome.net/lg/lg_top_745x90.swf"><param name=quality value=high><embed src="http://btn.pchome.net/lg/lg_top_745x90.swf" quality=high pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash" type="application/x-shockwave-flash" width="745" height="90"></embed></object>');
}
}

function postadfoot () {
document.write ('<a href=http://www.pchome.net/from.php?userid=462 target=_blank><img src=http://btn.pchome.net/pchome/new_745x90.gif border=0 width=745 height=90></a>');
}

//var Words ="%3CSCRIPT%20LANGUAGE%3D%22JavaScript1.1%22%20SRC%3D%22http%3A//casting8.allyes.com/main/adfshow%3Fuser%3DAdForward_For_Publisher_6%7Cshmc%7Ctextlink%26db%3Dcasting8%26border%3D0%26local%3Dyes%26js%3Die%22%3E%3C/script%3E%3C/div%3E" //put your cripto code there
//var Words =""
function OutWord()
{
var NewWords;
NewWords = unescape(Words);
document.write(''+NewWords+'');
} 

function postadmid() {

//不得超过12个中文字
document.write ('<br>-<a target="_blank" href="http://www.pchome.net/from.php?userid=473"><font color="#000000">亮晶彩　纯平超值送活力</font></a>');
document.write ('<br>-<a href="http://www.pchome.net/from.php?userid=430" target="_blank"><font color="#FF0000"><u>拨打800-858-2336，尽享DELL高达2000元优惠！</u></font></a>');
document.write ('<br>-<a href="http://ad.cn.doubleclick.net/clk;4852303;7326928;n?http://pchome.eachnet.com/fu/co/rd.php?http://pages.eachnet.com/st/page/landing/impage/computer.htm" target="_blank"><font color="#006600">花最少的钱来升级你的电脑!</font></a>');
//OutWord();
}

function postadleft() {
document.write ('<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=5,0,0,0" width="150"  height="240">');
document.write ('<param name=movie value="http://btn.pchome.net/the9/the9_150x240.swf"><param name=quality value=high>');
document.write ('<embed src="http://btn.pchome.net/the9/the9_150x240.swf" quality=high pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash" type="application/x-shockwave-flash" width="150" height="240"></embed></object>');
}

function postadright() {

//document.write ('<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=5,0,0,0" width="150"  height="240">');
//document.write ('<param name=movie value="http://btn.pchome.net/ft2/ft2_150x240.swf"><param name=quality value=high>');
//document.write ('<embed src="http://btn.pchome.net/ft2/ft2_150x240.swf" quality=high pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash" type="application/x-shockwave-flash" width="150" height="240"></embed></object>');

//document.write ('<br><br>');
//document.write ('<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=5,0,0,0" width="150"  height="240">');
//document.write ('<param name=movie value="http://btn.pchome.net/ctx/ctx_150x240.swf"><param name=quality value=high>');
//document.write ('<embed src="http://btn.pchome.net/ctx/ctx_150x240.swf" quality=high pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash" type="application/x-shockwave-flash" width="150" height="240"></embed></object>');
}
function postadtop () {
var x=Math.random();
var i=Math.round(x*6-0.5);
if (i<5) {
document.write ('<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" width="580"  height="60"><param name=movie value="http://btn.pchome.net/pchome/2002_580x60.swf"><param name=quality value=high><embed src="http://btn.pchome.net/pchome/2002_580x60.swf" quality=high pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash" type="application/x-shockwave-flash" width="580" height="60"></embed></object>');
}

if (i==5) {
document.write ('<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,0,0" width="580"  height="60"><param name=movie value="http://btn.pchome.net/pchome/2002_580x60.swf"><param name=quality value=high><embed src="http://btn.pchome.net/pchome/2002_580x60.swf" quality=high pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash" type="application/x-shockwave-flash" width="580" height="60"></embed></object>');
//document.write('<SCRIPT LANGUAGE="JavaScript1.1" SRC="http://casting8.allyes.com/main/adfshow?user=AdForward_For_Publisher_6|shmc|floating&db=casting8&border=0&local=yes&js=ie"></SCRIPT>');
}}
//window.open("http://shadf.allyes.com/banner/shmc2.html","","toolbar=0,location=0,directories=0,status=0,menubar=0,scrollbars=0,resizable=0,copyhistory=0,width=250,height=250,left=50,top=50");


//--->