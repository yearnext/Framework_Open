/**
 *******************************************************************************
 *                 Copyright (C) 2017 - 2018  Accumulate Team                  *
 *                                                                             *
 *      Licensed under the Apache License, Version 2.0 (the "License");        *
 *      you may not use this file except in compliance with the License.       *
 *      You may obtain a copy of the License at                                *
 *                 http://www.apache.org/licenses/LICENSE-2.0                  *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************
 * @file       linklist.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      link list component source files                                *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
 * @defgroup framework link list component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "linklist.h"

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        single link list
 *******************************************************************************
 */
__INLINE
void SLinkListInit(SLinkList_t *l)
{
    l->Next = NULL;
}

__INLINE
void SLinkListAppend(SLinkList_t *l, SLinkList_t *n)
{
	SLinkList_t *node = l;

	while (node->Next != NULL)
	{
		node = node->Next;
	}

	node->Next = n;
	n->Next = NULL;
}

__INLINE
void SLinkListInsert(SLinkList_t *l, SLinkList_t *n)
{
	n->Next = l->Next;
	l->Next = n;
}

__INLINE
SLinkList_t *SLinkListRemove(SLinkList_t *l, SLinkList_t *n)
{
    SLinkList_t *p = l;

	while (p->Next != NULL && p->Next != n)
	{
		p = p->Next;
	}

	if (p->Next != NULL)
	{
		p->Next = n->Next->Next;
	}

    return l;
}

__INLINE
SLinkList_t *SLinkList_Head(SLinkList_t *l)
{
	return l->Next;
}

__INLINE
SLinkList_t *SLinkList_Tail(SLinkList_t *l)
{
	while (l->Next)
	{
		l = l->Next;
	}

	return l;
}

__INLINE
SLinkList_t *SLinkList_Next(SLinkList_t *n)
{
	return n->Next;
}

__INLINE
uint8_t SLinkListIsEmpty(SLinkList_t *head)
{
	return (head->Next == NULL);
}

__INLINE
int SLinkListLen(SLinkList_t *head)
{
    int len = 0;
    SLinkList_t *p = head->Next;

	for (; p->Next != NULL; p = p->Next, len++);

    return len;
}

/**
 *******************************************************************************
 * @brief       link list interface
 *******************************************************************************
 */
__INLINE
void LinkListInit(LinkList_t *l)
{
	l->Next = l;
	l->Prev = l;
}

__INLINE
void LinkListInsertAfter(LinkList_t *l, LinkList_t *n)
{
	//! N插入在L之后
	l->Next->Prev = n;
	n->Next = l->Next;

	l->Next = n;
	n->Prev = l;
}

__INLINE
void LinkListInsertBefore(LinkList_t *l, LinkList_t *n)
{
	//! N插入在L之前
	l->Prev->Next = n;
	n->Prev = l->Prev;

	l->Prev = n;
	n->Next = l;
}

__INLINE
LinkList_t *LinkListDeleteAfter(LinkList_t *l)
{
	LinkList_t *result = l->Next;

	LinkListRemove(result);

	return (result == l) ? (NULL) : (result);
}

__INLINE
void LinkListRemove(LinkList_t *list)
{
	list->Next->Prev = list->Prev;
	list->Prev->Next = list->Next;

	list->Prev = list;
	list->Next = list;
}

__INLINE
uint8_t LinkListIsEmpty(LinkList_t *list)
{
	return (list->Next == list);
}

__INLINE
uint8_t LinkListIsLife(LinkList_t *head, LinkList_t *list)
{
	if (head == NULL)
	{
		return 0;
	}

	while (head->Next != head)
	{
		if (head->Next == list)
		{
			return 1;
		}

		head = head->Next;
	}

	return 0;
}

__INLINE
int LinkListLen(LinkList_t *head)
{
	int num = 0;
	const LinkList_t *p = head;

	while (p->Next != head)
	{
		num++;
		p = p->Next;
	}

	return num;
}

/** @}*/     /** link list component */

/**********************************END OF FILE*********************************/
