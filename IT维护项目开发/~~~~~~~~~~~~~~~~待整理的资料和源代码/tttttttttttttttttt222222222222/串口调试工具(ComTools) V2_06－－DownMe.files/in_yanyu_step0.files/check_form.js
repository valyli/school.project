/*
written by deminy on 2001/07/26
last modified by deminy on 2001/08/07

function is_only_space(str);
�ú������ж�ĳһ�����Ƿ�Ϊ���ַ���
�ú�����������is_textbox_null����
str:�����Ե��ַ�������

function is_item_not_null(Item, ItemCaption);
�ú������жϱ���Ԫ��ֵ�Ƿ�Ϊ��
�ú���������is_only_space
Item:  ��Ԫ������
ItemCaption:  Item��˵��

function check_multiple_item (objForm , Item , ItemCaption, AllowNum);
�ú������ڼ���ĳЩ��ѡ��Ԫ��
objForm:  ������
Item:  ��������Ķ�ѡ��Ԫ������
ItemCaption:  Item��˵��
AllowNum:  Item����ѡ���Ԫ�ظ���


function is_digital(Item, ItemCaption)
�ú������ڼ���ĳһItem�Ƿ�Ϊ����
Item: ����Ԫ�����ƣ����߱�����
isObj:ȷ������Email����һ��Item������һ������������if true,Item��һ������Ԫ�����ƣ����򡭡�
ItemCaption:����IsObj = tureʱ��Ч,���ڳ�����ʾ

function check_length(Item, MinLength, MaxLength, ItemCaption)
�ú������ڼ���ĳһItem�Ƿ񳤶ȷ���Ҫ��
Item: ����Ԫ�����ƣ����߱�����
MinLength:��̳���
MaxLength:��󳤶�
ItemCaption:����IsObj = tureʱ��Ч,���ڳ�����ʾ

function backup1(objForm)
���ú����������޶���Ԫ�ص�ȡֵ��Χ�ͳ���

##############################################################################
##############################################################################
##############################################################################
���º���ֱ�����ڱ���֤
function check_email(Email)
�ú������ڼ���Email
Email: ����EmailԪ�����ƣ�����Email������

function check_postcode(PostCode)
�ú������ڼ�����������

function check_password(Pass1, Pass2, MinLength, MaxLength)
�ú������ڼ�������

function check_idcard(IDCard)
�ú������ڼ������֤

function check_text(Item, MinLength, MaxLength, ItemCaption)
�ú������ڼ����ı���

function check_radio(Item, ItemCaption)
�ú������ڼ���Radio��
Item:��Ԫ���������� objForm.username
ItemCaption:��Ԫ����ʾ���û����������������� "�û���"
��ItemԪ�ز����ڻ�����δѡ����Ӧѡ���ʱ�򣬽�������������Ϣ���û���
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
				alert(ItemCaption + "����ѡ��\����ѡ��\��");
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
				alert(ItemCaption + "ѡ�����Ŀ����");
				objForm.elements[i].focus();
				return false;
			}
			if (!is_selected)
			{
				alert(ItemCaption + "����Ϊ��");
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
		alert(ItemCaption + "����Ϊ�գ�");
		Item.focus();
		return false;
	}
	return true;
}

function check_email(Email)
{
	if (!is_item_not_null(Email, "Email��ַ"))
		return false;

	var pattern = /^([.a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(\.[a-zA-Z0-9_-])+/; 
	flag = pattern.test(Email.value); 
	if(!flag)
	{
		alert("����Email��ַ��д���ԡ�"); 
		Email.focus();
		return false;
	}
	else
		return true;
}

function check_name(UserName)
{
	if (!is_item_not_null(UserName, "�û���"))
		return false;

	var pattern = /^([.a-zA-Z0-9_-])+@([a-zA-Z0-9_-])+(\.[a-zA-Z0-9_-])+/; 
	flag = pattern.test(UserName.value); 
	if(!flag)
	{
		alert("�����û�����д���ԡ�"); 
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
		alert(ItemCaption + "�������֡�"); 
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
		alert("\"check_length\"�������ô���");
		return false;
	}

	if ((Item.value.length < MinLength) || (Item.value.length > MaxLength))
	{
		alert(ItemCaption + "���Ȳ�����Ҫ��"); 
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
	  alert("�ı�����!"); 
	  objForm.text1.focus();
	  return false;
	}
}

function check_postcode(PostCode)
{
	if (!check_length(PostCode, 6, 6, "��������"))
		return false;

	if (!is_digital(PostCode, "��������"))
		return false;
	return true;
}

function check_password(Pass1, Pass2, MinLength, MaxLength)
{
	if (!check_text(Pass1, MinLength, MaxLength, "����"))
		return false;

	if (!check_text(Pass2, MinLength, MaxLength, "�ڶ������������"))
		return false;

	if (Pass1.value != Pass2.value)
	{
		alert("������������벻һ�¡�");
		Pass1.value = "";
		Pass2.value = "";
		Pass1.focus();
		return false;
	}
	return true;

}

function check_idcard(IDCard)
{
	if (!is_item_not_null(IDCard, "���֤����"))
		return false;

	if (!is_digital(IDCard, "���֤����"))
		return false;

	if ((IDCard.value.length != 15) && (IDCard.value.length != 18))
	{
		alert("���֤���볤�Ȳ��ԡ�");
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
		alert(ItemCaption + "����Ϊ��");
		Item[0].focus();
		return false;
	}
	else
	{
		alert("��Ԫ��\"" + ItemCaption + "\"������");
		return false;
	}
}

	/*�ֻ������ж�*/
	function check_code(MobileNum)
	{ 
		var arr_num = new Array();
		arr_num = MobileNum.value.split(";");
		if(arr_num.length > 2)
		{
			alert("�����д2���ֻ����룡");
			MobileNum.focus();
			return false;
		}
		for(var i=0; i<arr_num.length;i++)
		{
			var pattern = /^13([0-9]){1}([0-9]){8}/;
			flag = pattern.test(arr_num[i]); 
			if(!flag)
			{
				alert("�ֻ�������д����ȷ��"); 
				MobileNum.focus();
				return false;
			}
		}
		return true;
	}

