/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     LIDP_CArrayTemplate.h

  Author:        LiJia

  Version:       v1.0

  Date:          2003/06/15

  Description:   A Container Template For Array. Only Head file, without CPP file.

  Others:

  Function List:

  History:
    1. Date:           2003/06/15
       Author:         LiJia
       Modification:   First Created

 *****************************************************************************/





// LIDP_CArrayTemplate.h: interface for the LIDP_CArrayTemplate class.
//
//////////////////////////////////////////////////////////////////////




#if !defined(LIDP_CARRAYTEMPLATE_H__DCF98042_C8D0_462A_9FD3_90E157845FD9__INCLUDED_)
#define LIDP_CARRAYTEMPLATE_H__DCF98042_C8D0_462A_9FD3_90E157845FD9__INCLUDED_

#include "smm.h"
#include "stdlib.h"


template<typename DataType>
struct LIDP_CArrayTemplate_Node
{
	DataType data;
	LIDP_CArrayTemplate_Node<DataType>* pstNext;
};

template<typename Element, typename pstElement>
//Element is the element type in array
//pstElement is the pointer of Element
class LIDP_CArrayTemplate
{
public:
	SMM_INT32 Count;
	LIDP_CArrayTemplate_Node<Element>* pstHead;

public:
	LIDP_CArrayTemplate();
	virtual ~LIDP_CArrayTemplate();

	SMM_INT32 Add(Element e);
	SMM_INT32 GetCount();
	//������������Ԫ�ص����ã������ڸ��Ľ������
	Element& operator[](SMM_INT32 i);
	//����������Ԫ�أ�����Ԫ��Ϊ������Ԫ�صĿ���
	Element GetAt(SMM_INT32 i);
	void RemoveAll();
	SMM_BOOL SetAt(SMM_INT32 i, Element e);
	SMM_BOOL IsEmpty();
	SMM_INT32 RemoveAt(SMM_INT32 i, SMM_INT32 n);
	SMM_INT32 Append(LIDP_CArrayTemplate<Element, pstElement>& newArray);
	SMM_BOOL InsertAt(SMM_INT32 i, Element e);
	SMM_BOOL InsertAt(SMM_INT32 i, LIDP_CArrayTemplate<Element, pstElement>& newArray);
};






//���캯��
template<typename Element, typename pstElement>
LIDP_CArrayTemplate<Element, pstElement>::LIDP_CArrayTemplate()
{
	//��ʼ������������Ϣ
	pstHead = NULL;
	Count = 0;
}

//��������
template<typename Element, typename pstElement>
LIDP_CArrayTemplate<Element, pstElement>::~LIDP_CArrayTemplate()
{
	RemoveAll();
}

//ɾ�����нڵ�
template<typename Element, typename pstElement>
void LIDP_CArrayTemplate<Element, pstElement>::RemoveAll()
{
	LIDP_CArrayTemplate_Node<Element> *p_pre = NULL, *p = pstHead;
/*	for(int i = 0; i < Count; i++)
	{
		printf("unit:%d\n", p->data);
		p = p->pstNext;
	}
*/
	//ɾ�����з���Ŀռ䣬�����ڴ�
	while(p != NULL)
	{
//		printf("delete.\n");
		p_pre = p;
		p = p->pstNext;
		free(p_pre);
	}
	pstHead = NULL;
	Count = 0;
}


//�Ƴ�ָ������ֵ���Count���ڵ�
//����ʵ���Ƴ��Ľڵ���Ŀ��0��ʾû���Ƴ��κνڵ�
template<typename Element, typename pstElement>
SMM_INT32 LIDP_CArrayTemplate<Element, pstElement>::RemoveAt(SMM_INT32 i, SMM_INT32 n)
{
	if(i > Count - 1 || i < 0)
	{
		printf("ERROR: cursor of array overflow.\n");
		return 0;
	}

	LIDP_CArrayTemplate_Node<Element>* p = pstHead;
	SMM_INT32 t = Count - 1 - i - 1;
	//�鵽��ӳ������Ҫɾ���Ľڵ��ǰһ���ڵ�
	for(i = 0; i < t; i++)
		p = p->pstNext;

	LIDP_CArrayTemplate_Node<Element>* pre_p = p;
	for(i = 0; i < n; i++)
	{
		p = pre_p->pstNext;
		if(p == NULL)
			break;
		pre_p->pstNext = p->pstNext;
//		printf("to delete : %d\n", p->data);
		free(p);
		Count--;
	}
	return i;
}

//�������ͷ�������µĽڵ㣬�������������Ч��
//����ֵΪ0��ʾ��ӽڵ�ʧ�ܣ�������������ʾ�ɹ�����ֵΪ�ڵ�����
template<typename Element, typename pstElement>
SMM_INT32 LIDP_CArrayTemplate<Element, pstElement>::Add(Element e)
{
	//�����µĿռ����ڴ洢�ڵ�����
	LIDP_CArrayTemplate_Node<Element>* p = (LIDP_CArrayTemplate_Node<Element>*)malloc(sizeof(LIDP_CArrayTemplate_Node<Element>));
	if(p == NULL)
		return 0;
	//�������ݵ������Ľڵ���
	SMM_INT32 e_size = sizeof(Element);
	for(SMM_INT32 i = 0; i < e_size; i++)
	{
		((unsigned char*)(&(p->data)))[i] = ((unsigned char*)&e)[i];
	}
//	printf("add : %d\n", p->data);
	//��Ϊ����ĵ�һ���ڵ�
	if(Count == 0)
	{
		pstHead = p;
		pstHead->pstNext = NULL;
	}
	else
	{
		p->pstNext = pstHead;
		pstHead = p;
	}
	Count++;
	//���ص�ǰ�ڵ�����
	return Count;
}


//���ؽڵ�����
template<typename Element, typename pstElement>
SMM_INT32 LIDP_CArrayTemplate<Element, pstElement>::GetCount()
{
	return Count;
}

//�ж������Ƿ�Ϊ��
template<typename Element, typename pstElement>
SMM_BOOL LIDP_CArrayTemplate<Element, pstElement>::IsEmpty()
{
	if(Count == 0)
		return SMM_TRUE;
	else
		return SMM_FALSE;
}


//����������ָ���Ľڵ�����ã��û�����ͨ����������޸������е�ֵ
//������ֵ���ʱ���ᱨ��������ֵ��Զ�����һ���ڵ�
template<typename Element, typename pstElement>
Element& LIDP_CArrayTemplate<Element, pstElement>::operator[](SMM_INT32 i)
{
	if(i > Count - 1 || i < 0)
	{
		printf("ERROR: cursor of array overflow.\n");
		return pstHead->data;
	}
	LIDP_CArrayTemplate_Node<Element>* p = pstHead;
	SMM_INT32 n = Count - 1 - i;
	//�鵽��ӳ�����Ľڵ�
	for(i = 0; i < n; i++)
		p = p->pstNext;

	return p->data;
}

//����������ָ���Ľڵ�ĸ���
//������ֵ���ʱ���ᱨ��������ֵ��Զ�����һ���ڵ�
template<typename Element, typename pstElement>
Element LIDP_CArrayTemplate<Element, pstElement>::GetAt(SMM_INT32 i)
{
	if(i > Count - 1 || i < 0)
	{
		printf("ERROR: cursor of array overflow.\n");
		return pstHead->data;
	}
	LIDP_CArrayTemplate_Node<Element>* p = pstHead;
	SMM_INT32 n = Count - 1 - i;
	//�鵽��ӳ�����Ľڵ�
	for(i = 0; i < n; i++)
		p = p->pstNext;

	return p->data;
}

//������������Ӧ��Ԫ�ص�ֵ
template<typename Element, typename pstElement>
SMM_BOOL LIDP_CArrayTemplate<Element, pstElement>::SetAt(SMM_INT32 i, Element e)
{
	if(i > Count - 1 || i < 0)
	{
		printf("ERROR: cursor of array overflow.\n");
		return FALSE;
	}
	LIDP_CArrayTemplate_Node<Element>* p = pstHead;
	SMM_INT32 n = Count - 1 - i;
	//�鵽��ӳ�����Ľڵ�
	for(i = 0; i < n; i++)
		p = p->pstNext;

	//�������ݵ������Ľڵ���
	SMM_INT32 e_size = sizeof(Element);
	for(i = 0; i < e_size; i++)
	{
		((unsigned char*)(&(p->data)))[i] = ((unsigned char*)&e)[i];
	}
	return TRUE;
}

//����һ������׷�ӵ�������֮�󣬷���ֵΪ׷�ӵ�����Ŀ�ʼλ�õ�����ֵ
//��ɾ������׷�ӵ�����
template<typename Element, typename pstElement>
SMM_INT32 LIDP_CArrayTemplate<Element, pstElement>::Append(LIDP_CArrayTemplate<Element, pstElement>& newArray)
{
	SMM_INT32 start_index = Count;
	SMM_INT32 n = newArray.GetCount();
	for(SMM_INT32 i = 0; i < n; i++)
		Add(newArray[i]);

	return start_index;
}


template<typename Element, typename pstElement>
SMM_BOOL LIDP_CArrayTemplate<Element, pstElement>::InsertAt(SMM_INT32 i, LIDP_CArrayTemplate<Element, pstElement>& newArray)
{
	SMM_INT32 n = newArray.GetCount();
	for(SMM_INT32 t = 0; t < n; t++)
		if(InsertAt(i+t, newArray[t]) == FALSE)
			return FALSE;
	return TRUE;
}




//������ֵָ���Ľڵ�֮ǰ����һ���ڵ㣬���ز���ɹ���ʧ��
template<typename Element, typename pstElement>
SMM_BOOL LIDP_CArrayTemplate<Element, pstElement>::InsertAt(SMM_INT32 i, Element e)
{
	if(i > Count - 1 || i < 0)
	{
		printf("ERROR: cursor of array overflow.\n");
		return FALSE;
	}
	LIDP_CArrayTemplate_Node<Element>* p = pstHead;
	SMM_INT32 n = Count - 1 - i;
	//�鵽��ӳ�����Ľڵ�
	for(i = 0; i < n; i++)
		p = p->pstNext;

	//�����µĿռ����ڴ洢�ڵ�����
	LIDP_CArrayTemplate_Node<Element>* pt = (LIDP_CArrayTemplate_Node<Element>*)malloc(sizeof(LIDP_CArrayTemplate_Node<Element>));
	if(pt == NULL)
		return FALSE;
	//�������ݵ������Ľڵ���
	SMM_INT32 e_size = sizeof(Element);
	for(i = 0; i < e_size; i++)
	{
		((unsigned char*)(&(pt->data)))[i] = ((unsigned char*)&e)[i];
	}

	pt->pstNext = p->pstNext;
	p->pstNext = pt;

	Count++;

	return TRUE;
}

#endif // !defined(LIDP_CARRAYTEMPLATE_H__DCF98042_C8D0_462A_9FD3_90E157845FD9__INCLUDED_)
