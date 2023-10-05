//打开新窗口
function lbsong()
{
window.open("about:blank","lbsong","toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=no,resizable=yes,copyhistory=yes,top=10,left=10,width=250,height=100");
}

function open_window(url,windowname,size)
{
window.open(url,windowname,"toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=no,resizable=yes,copyhistory=yes,top=10,left=10,"+ size);
}

function checkOthers(form)
{
for (var i=0;i<form.elements.length;i++)
{
var e = form.elements[i];
//		if (e.name != 'chkall')
if (e.checked==false)
{
e.checked = true;// form.chkall.checked;
}
else
{
e.checked = false;
}
}
}

function checkAll(form)
{
for (var i=0;i<form.elements.length;i++)
{
var e = form.elements[i];
//		if (e.name != 'chkall')
e.checked = true// form.chkall.checked;
}
}