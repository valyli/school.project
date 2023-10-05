function search1()
{
var dat1=""
si=document.formecon.econDateIndex.selectedIndex;
htmasp1=document.formecon.econDateIndex.options[si].value
if (htmasp1 > 20000229)
	{dat1 = 'c.asp'}
if (htmasp1 < 20000229)
	{dat1 = 'c.htm'}
url='http://www.netmay.com/newfile/'+htmasp1+dat1;
if (document.formecon.econDateIndex.options[0].selected)
{javascript:void(null);}
else
{
parent.rightdown.location=url;
return true;
}
}
function search2()
{
var dat2=""
si=document.formtech.techDateIndex.selectedIndex;
htmasp2=document.formtech.techDateIndex.options[si].value
if (htmasp2 > 20000229)
	{dat2 = 't.asp'}
if (htmasp2 < 20000229)
	{dat2 = 't.htm'}


url='http://www.netmay.com/newtech/'+htmasp2+dat2;
if (document.formtech.techDateIndex.options[0].selected)
{javascript:void(null);}
else
{
parent.rightdown.location=url;
return true;
}
}

function search3()
{
si=document.formneteco.netecoDateIndex.selectedIndex;
ne1=document.formneteco.netecoDateIndex.options[si].value

url3="http://www.netmay.com/wmag/wmag"+ne1+".htm";
if (document.formneteco.netecoDateIndex.options[0].selected)
{javascript:void(null);}
else
{
parent.rightdown.location=url3;
return true;
}
}

function search4()
{
si=document.formecohot.ecohotDateIndex.selectedIndex;
ne2=document.formecohot.ecohotDateIndex.options[si].value

url4="http://www.netmay.com/hoteco/hoteco"+ne2+".htm";
if (document.formecohot.ecohotDateIndex.options[0].selected)
{javascript:void(null);}
else
{
parent.rightdown.location=url4;
return true;
}
}

function search5()
{
si5=document.formtongxin.tongxinDateIndex.selectedIndex;
ne3=document.formtongxin.tongxinDateIndex.options[si5].value

url5="http://www.netmay.com/tele/tongxin/tongxin"+ne3+".htm";
if (document.formtongxin.tongxinDateIndex.options[0].selected)
{javascript:void(null);}
else
{
parent.rightdown.location=url5;
return true;
}
}
lstart=70  //设置起始位置；
loop=true   //设置是否循环.true表示循环显示；
speed=30   //滚动速度；
pr_step=1   //滚动的步幅；

function makeObj(obj,nest){
    nest=(!nest) ? '':'document.'+nest+'.'
    this.css=(document.layers) ? eval(nest+'document.'+obj):eval(obj+'.style')
	this.scrollHeight=document.layers?this.css.document.height:eval(obj+'.offsetHeight')
	this.up=goUp
    this.obj = obj + "Object"
    eval(this.obj + "=this")
    return this
}
function goUp(speed){
	if(parseInt(this.css.top)>-this.scrollHeight){
		this.css.top=parseInt(this.css.top)-pr_step
		setTimeout(this.obj+".up("+speed+")",speed)
	}else if(loop) {
		this.css.top=lstart
		eval(this.obj+".up("+speed+")")
	  }
}
function slideInit(){
	oSlide=makeObj('divNews','divCont')
	oSlide.css.top=lstart
	oSlide.up(speed)
}
