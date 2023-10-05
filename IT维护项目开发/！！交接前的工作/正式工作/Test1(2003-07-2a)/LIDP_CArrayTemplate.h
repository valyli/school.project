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
	//按按索引返回元素的引用，可用于更改结点内容
	Element& operator[](SMM_INT32 i);
	//按索引返回元素，返回元素为数组中元素的拷贝
	Element GetAt(SMM_INT32 i);
	void RemoveAll();
	SMM_BOOL SetAt(SMM_INT32 i, Element e);
	SMM_BOOL IsEmpty();
	SMM_INT32 RemoveAt(SMM_INT32 i, SMM_INT32 n);
	SMM_INT32 Append(LIDP_CArrayTemplate<Element, pstElement>& newArray);
	SMM_BOOL InsertAt(SMM_INT32 i, Element e);
	SMM_BOOL InsertAt(SMM_INT32 i, LIDP_CArrayTemplate<Element, pstElement>& newArray);
};






//构造函数
template<typename Element, typename pstElement>
LIDP_CArrayTemplate<Element, pstElement>::LIDP_CArrayTemplate()
{
	//初始化数组描述信息
	pstHead = NULL;
	Count = 0;
}

//析构函数
template<typename Element, typename pstElement>
LIDP_CArrayTemplate<Element, pstElement>::~LIDP_CArrayTemplate()
{
	RemoveAll();
}

//删除所有节点
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
	//删除所有分配的空间，回收内存
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


//移除指定索引值后的Count个节点
//返回实际移除的节点数目，0表示没有移除任何节点
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
	//查到对映索引的要删除的节点的前一个节点
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

//在链表的头部插入新的节点，这样做可以提高效率
//返回值为0表示添加节点失败，返回正整数表示成功，其值为节点总数
template<typename Element, typename pstElement>
SMM_INT32 LIDP_CArrayTemplate<Element, pstElement>::Add(Element e)
{
	//分配新的空间用于存储节点数据
	LIDP_CArrayTemplate_Node<Element>* p = (LIDP_CArrayTemplate_Node<Element>*)malloc(sizeof(LIDP_CArrayTemplate_Node<Element>));
	if(p == NULL)
		return 0;
	//复制数据到创建的节点中
	SMM_INT32 e_size = sizeof(Element);
	for(SMM_INT32 i = 0; i < e_size; i++)
	{
		((unsigned char*)(&(p->data)))[i] = ((unsigned char*)&e)[i];
	}
//	printf("add : %d\n", p->data);
	//若为插入的第一个节点
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
	//返回当前节点数量
	return Count;
}


//返回节点总数
template<typename Element, typename pstElement>
SMM_INT32 LIDP_CArrayTemplate<Element, pstElement>::GetCount()
{
	return Count;
}

//判断数组是否为空
template<typename Element, typename pstElement>
SMM_BOOL LIDP_CArrayTemplate<Element, pstElement>::IsEmpty()
{
	if(Count == 0)
		return SMM_TRUE;
	else
		return SMM_FALSE;
}


//返回索引所指定的节点的引用，用户可以通过这个引用修改容器中的值
//当索引值溢出时，会报错，但返回值永远是最后一个节点
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
	//查到对映索引的节点
	for(i = 0; i < n; i++)
		p = p->pstNext;

	return p->data;
}

//返回索引所指定的节点的复本
//当索引值溢出时，会报错，但返回值永远是最后一个节点
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
	//查到对映索引的节点
	for(i = 0; i < n; i++)
		p = p->pstNext;

	return p->data;
}

//按索引设置相应的元素的值
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
	//查到对映索引的节点
	for(i = 0; i < n; i++)
		p = p->pstNext;

	//复制数据到创建的节点中
	SMM_INT32 e_size = sizeof(Element);
	for(i = 0; i < e_size; i++)
	{
		((unsigned char*)(&(p->data)))[i] = ((unsigned char*)&e)[i];
	}
	return TRUE;
}

//将另一个数组追加到此数组之后，返回值为追加的数组的开始位置的索引值
//不删除用于追加的数组
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




//在索引值指定的节点之前插入一个节点，返回插入成功或失败
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
	//查到对映索引的节点
	for(i = 0; i < n; i++)
		p = p->pstNext;

	//分配新的空间用于存储节点数据
	LIDP_CArrayTemplate_Node<Element>* pt = (LIDP_CArrayTemplate_Node<Element>*)malloc(sizeof(LIDP_CArrayTemplate_Node<Element>));
	if(pt == NULL)
		return FALSE;
	//复制数据到创建的节点中
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
