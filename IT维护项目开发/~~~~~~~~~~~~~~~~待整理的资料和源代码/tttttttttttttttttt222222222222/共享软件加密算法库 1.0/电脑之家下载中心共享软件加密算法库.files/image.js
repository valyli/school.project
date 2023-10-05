document.write("")
quotes=new Array(1);
quotes[0]="<a href='http://www.eloo.com/count/header.php?site=linux' target='_blank'><b><font color='#FF0000'>点击索取Linux免费资料</font></b></a>";
index=Math.floor(Math.random()*quotes.length);
document.write(quotes[index])