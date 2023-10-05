/*
written by deminy on 2001/07/26
last modified by deminy on 2001/08/07

function is_only_space(str);
该函数将判断某一变量是否为空字符串
该函数将被函数is_textbox_null调用
str:被测试的字符串变量

function is_item_not_null(Item, ItemCaption);
该函数将判断表单中元素值是否为空
该函数将调用is_only_space
Item:  表单元素名称
ItemCaption:  Item的说明

function check_multiple_item (objForm , Item , ItemCaption, AllowNum);
该函数用于检验某些多选表单元素
objForm:  表单名称
Item:  将被检验的多选表单元素名称
ItemCaption:  Item的说明
AllowNum:  Item允许被选择的元素个数


function is_digital(Item, ItemCaption)
该函数用于检验某一Item是否为数字
Item: 表单中元素名称，或者变量名
isObj:确定变量Email代表一个Item对象还是一个仅仅变量，if true,Item是一个表单中元素名称，否则……
ItemCaption:仅当IsObj = ture时有效,用于出错提示

function check_length(Item, MinLength, MaxLength, ItemCaption)
该函数用于检验某一Item是否长度符合要求
Item: 表单中元素名称，或者变量名
MinLength:最短长度
MaxLength:最大长度
ItemCaption:仅当IsObj = ture时有效,用于出错提示

function backup1(objForm)
备用函数：可以限定表单元素的取值范围和长度

##############################################################################
##############################################################################
##############################################################################
以下函数直接用于表单验证
function check_email(Email)
该函数用于检验Email
Email: 表单中Email元素名称，或者Email变量名

function check_postcode(PostCode)
该函数用于检验邮政编码

function check_password(Pass1, Pass2, MinLength, MaxLength)
该函数用于检验密码

function check_idcard(IDCard)
该函数用于检验身份证

function check_text(Item, MinLength, MaxLength, ItemCaption)
该函数用于检验文本框

function check_radio(Item, ItemCaption)
该函数用于检验Radio框
Item:表单元素名，比如 objForm.username
ItemCaption:表单元素显示给用户看的文字名，比如 "用户名"
当Item元素不存在或者尚未选择相应选项的时候，将报出错提醒信息给用户。
##############################################################################
##############################################################################
##############################################################################
*/

function is_only_space(str){
	for(i=0;i<=str.length-1;i++){
		if (str.charAt(i) != " ") 
			return false;
	}
	return true;
}

function check_multiple_item (objForm , Item , ItemCaption, AllowNum)
{
	selected_num = 0;
	is_selected = false;
	if (isNaN(AllowNum))
		AllowNum = 1;

	for (i=0;i<objForm.elements.length;i++)
	{
		if (objForm.elements[i].name == Item)
		{
			if (objForm.elements[i].options[0].selected)
			{
				alert(ItemCaption + "不能选择\“请选择\”");
				objForm.elements[i].focus();
				return false;
			}

			for (j=0;j<objForm.elements[i].length;j++)
			{
				if (objForm.elements[i].options[j].selected)
				{
					selected_num++;
					is_selected = true;
				}
			}
			if (selected_num > AllowNum)
			{
				alert(ItemCaption + "选择的数目过多");
				objForm.elements[i].focus();
				return false;
			}
			if (!is_selected)
			{
				alert(ItemCaption + "不能为空");
				objForm.elements[i].focus();
				return false;
			}
			else
				return true;
		}
	}
	alert("Err, I can't find the item " + Item + ", you can kick me");
	return false;
}

function is_item_not_null(Item, ItemCaption)
{
	if ((Item.value == "") || is_only_space(Item.value))
	{
		alert(ItemCaption + "不能为空！");
		Item.focus();
		return false;
	}
	return true;
}

function check_email(Email)
{
	if (!is_item_not_null(Email, "Email地址"))
		return false;

	var pattern = /^([.a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(\.[a-zA-Z0-9_-])+/; 
	flag = pattern.test(Email.value); 
	if(!flag)
	{
		alert("您的Email地址填写不对。"); 
		Email.focus();
		return false;
	}
	else
		return true;
}

function check_name(UserName)
{
	if (!is_item_not_null(UserName, "用户名"))
		return false;

	var pattern = /^([.a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(\.[a-zA-Z0-9_-])+/; 
	flag = pattern.test(UserName.value); 
	if(!flag)
	{
		alert("您的用户名填写不对。"); 
		UserName.focus();
		return false;
	}
	else
		return true;
}


function is_digital(Item, ItemCaption)
{
	var pattern = /^([0-9])+$/;
	flag = pattern.test(Item.value); 
	if(!flag)
	{
		alert(ItemCaption + "不是数字。"); 
		Item.focus();
		return false;
	}
	else
		return true;
}

function check_length(Item, MinLength, MaxLength, ItemCaption)
{
	if ((MinLength == 0) && (MaxLength == 0))
		return true;

	if (MaxLength < MinLength)
	{
		alert("\"check_length\"函数调用错误。");
		return false;
	}

	if ((Item.value.length < MinLength) || (Item.value.length > MaxLength))
	{
		alert(ItemCaption + "长度不符合要求。"); 
		Item.focus();
		return false;
	}
	else
		return true;
}

function backup1(objForm)
{
	var pattern = /^[a-zA-Z][a-zA-Z0-9_-]{4,9}$/; 
	flag = pattern.test(objForm.text1.value); 
	if(!flag){ 
	  alert("文本不对!"); 
	  objForm.text1.focus();
	  return false;
	}
}

function check_postcode(PostCode)
{
	if (!check_length(PostCode, 6, 6, "邮政编码"))
		return false;

	if (!is_digital(PostCode, "邮政编码"))
		return false;
	return true;
}

function check_password(Pass1, Pass2, MinLength, MaxLength)
{
	if (!check_text(Pass1, MinLength, MaxLength, "密码"))
		return false;

	if (!check_text(Pass2, MinLength, MaxLength, "第二次输入的密码"))
		return false;

	if (Pass1.value != Pass2.value)
	{
		alert("两次输入的密码不一致。");
		Pass1.value = "";
		Pass2.value = "";
		Pass1.focus();
		return false;
	}
	return true;

}

function check_idcard(IDCard)
{
	if (!is_item_not_null(IDCard, "身份证号码"))
		return false;

	if (!is_digital(IDCard, "身份证号码"))
		return false;

	if ((IDCard.value.length != 15) && (IDCard.value.length != 18))
	{
		alert("身份证号码长度不对。");
		IDCard.focus();
		return false;
	}
	return true;
}

function check_text(Item, MinLength, MaxLength, ItemCaption)
{
	if (!is_item_not_null(Item, ItemCaption))
		return false;
	if (!check_length(Item, MinLength, MaxLength, ItemCaption))
		return false;
	return true;
}

function check_radio(Item, ItemCaption)
{
	if (Item)
	{
		for (i = 0; i < Item.length;i++ )
		{
			if (Item[i].checked == true)
				return true;
		}
		alert(ItemCaption + "不能为空");
		Item[0].focus();
		return false;
	}
	else
	{
		alert("表单元素\"" + ItemCaption + "\"不存在");
		return false;
	}
}

	/*手机号码判断*/
	function check_code(MobileNum)
	{ 
		var arr_num = new Array();
		arr_num = MobileNum.value.split(";");
		if(arr_num.length > 2)
		{
			alert("最多填写2个手机号码！");
			MobileNum.focus();
			return false;
		}
		for(var i=0; i<arr_num.length;i++)
		{
			var pattern = /^13([0-9]){1}([0-9]){8}/;
			flag = pattern.test(arr_num[i]); 
			if(!flag)
			{
				alert("手机号码填写不正确！"); 
				MobileNum.focus();
				return false;
			}
		}
		return true;
	}

