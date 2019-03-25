/**
 *******************************************************************************
 *                       Copyright (C) 2017  yearnext                          *
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
 * @brief       link list interface
 *******************************************************************************
 */
__INLINE
void LinkListInit(LinkList_t *list)
{
    list->Next = NULL;
    list->Prev = NULL;
}

__INLINE
int8_t LinkListAdd(LinkList_t *head, LinkList_t *list)
{
    if (head->Next != NULL)
    {
        head->Next->Prev = list;
    }
    
    list->Next = head->Next;
    head->Next = list;
    list->Prev = head;

    return 0;
}

__INLINE
int8_t LinkListTraverseAdd(LinkList_t *head, LinkList_t *list)
{
    LinkList_t *next = head;

	while (next->Next != NULL)
    {
        if(next->Next == list)
        {
            return -1;
        }

		next = next->Next;
    }

	next->Next = list;
    list->Prev = next;
	list->Next = NULL;

    return 0;
}

__INLINE
int8_t LinkListTraverseRemove(LinkList_t *head, LinkList_t *list)
{
    LinkList_t *next = head;

	while (next->Next != NULL)
    {
        if(next->Next == list)
        {
            next->Next = list->Next;
            list->Next = NULL;
            list->Prev = NULL;

            return 0;
        }

		next = next->Next;
    }

    return -1;
}

__INLINE
void LinkListRemove(LinkList_t *list)
{
    if (list->Prev != NULL)
    {
        list->Prev->Next = list->Next;
    }
    
    if (list->Next != NULL)
    {
        list->Next->Prev = list->Prev;
    }
    
    list->Next = NULL;
    list->Prev = NULL;
}

__INLINE
bool LinkListIsEmpty(LinkList_t *head)
{
    if(head->Next != NULL)
    {
        return true;
    }

    return false;
}

__INLINE
bool LinkListIsLife(LinkList_t *head, LinkList_t *list)
{
    if (head == NULL || head->Next == NULL)
    {
        return false;
    }

    while(head->Next != NULL)
    {
        if (head->Next == list)
        {
            return true;
        }

        head = head->Next;
    }
    
    return false;
}

__INLINE
uint16_t LinkListLen(LinkList_t *head)
{
    uint16_t num = 0;
    LinkList_t *tail = head;

    while(tail->Next != NULL)
    {
        num++;
        tail = tail->Next;
    }

    return num;
}

/**
 *******************************************************************************
 * @brief       link list queue interface
 *******************************************************************************
 */
__INLINE
void LinkQueueInit(LinkListQueue_t *mgr)
{
    mgr->Head = NULL;
    mgr->Tail = NULL;
}

__INLINE
void LinkQueueTraverseRemove(LinkListQueue_t *mgr, LinkList_t *list)
{
    if (mgr->Head == list && mgr->Tail == list)
    {
        mgr->Head = NULL;
        mgr->Tail = NULL;
    }
    else if (mgr->Head == list)
    {
        mgr->Head = list->Next;

        mgr->Tail->Prev = NULL;
    }
    else if (mgr->Tail == list)
    {
        mgr->Tail = list->Prev;

        mgr->Tail->Next = NULL;
    }
    else
    {
        list->Next->Prev = list->Prev;
        list->Prev->Next = list->Next;
    }
    
    list->Next = NULL;
    list->Prev = NULL;
}

__INLINE
void LinkQueuePut(LinkListQueue_t *mgr, LinkList_t *list)
{
    list->Next = NULL;

    if(mgr->Head == NULL && mgr->Tail == NULL)
    {
        list->Prev = NULL;
        mgr->Tail  = list;
        mgr->Head  = list;
    }
    else
    {
        mgr->Tail->Next = list;
        list->Prev      = mgr->Tail;
        mgr->Tail       = list;
    }
}

__INLINE
LinkList_t *LinkQueueGet(LinkListQueue_t *mgr)
{
    LinkList_t *list = mgr->Head;

    if(mgr->Head == mgr->Tail)
    {
        mgr->Tail = NULL;
        mgr->Head = NULL;
    }
    else
    {
        mgr->Head  = list->Next;
    }

    if (list != NULL)
    {
        list->Next = NULL;
    }

    return list;
}

__INLINE
bool LinkQueueIsEmpty(LinkListQueue_t *mgr)
{
    if(mgr->Head == NULL && mgr->Tail == NULL)
    {
        return true;
    }

    return false;
}

__INLINE
bool LinkQueueIsLife(LinkListQueue_t *mgr, LinkList_t *list)
{
    LinkList_t *head = mgr->Head;

    while(head != NULL)
    {
        if (head == list)
        {
            return true;
        }

        head = head->Next;
    }

    return false;
}

__INLINE
void LinkQueueCpy(LinkListQueue_t *dst, LinkListQueue_t *src)
{
    LinkList_t *node = LinkQueueGet(src);

    while(node != NULL)
    {
        LinkQueuePut(dst, node);

        node = LinkQueueGet(src);
    }
}

__INLINE
uint16_t LinkQueueLen(LinkListQueue_t *mgr)
{
    LinkList_t *node = mgr->Tail;
    uint16_t cnt = 0;

    while(node != NULL)
    {
        cnt++;

        node = node->Next;
    }

    return cnt;
}

/**
 *******************************************************************************
 * @brief        single link list
 *******************************************************************************
 */
__INLINE
void SLinkListInit(SLinkList_t *list)
{
    list->Next = NULL;
}

__INLINE
int8_t SLinkListAdd(SLinkList_t *head, SLinkList_t *list)
{
    SLinkList_t *next = head;

	while (next->Next != NULL)
    {
        if(next->Next == list)
        {
            return -1;
        }

		next = next->Next;
    }

	next->Next = list;
	list->Next = NULL;

    return 0;
}

__INLINE
int8_t SLinkListRemove(SLinkList_t *head, SLinkList_t *list)
{
    SLinkList_t *next = head;

	while (next->Next != NULL)
    {
        if(next->Next == list)
        {
            next->Next = list->Next;
            list->Next = NULL;

            return 0;
        }

		next = next->Next;
    }

    return -1;
}

__INLINE
bool SLinkListIsEmpty(SLinkList_t *head)
{
    if(head->Next != NULL)
    {
        return true;
    }

    return false;
}

__INLINE
uint16_t SLinkListLen(SLinkList_t *head)
{
    uint16_t num = 0;
    SLinkList_t *next = head->Next;

    while(next->Next != NULL)
    {
        num++;
        next = next->Next;
    }

    return num;
}

/**
 *******************************************************************************
 * @brief       single link list queue structure
 *******************************************************************************
 */
__INLINE
void SLinkQueueInit(SLinkListQueue_t *mgr)
{
    mgr->Head = NULL;
    mgr->Tail = NULL;
}

__INLINE
void SLinkQueuePut(SLinkListQueue_t *mgr, SLinkList_t *list)
{
    list->Next = NULL;

    if(mgr->Head == NULL && mgr->Tail == NULL)
    {
        mgr->Tail = list;
        mgr->Head = list;
    }
    else
    {
        mgr->Tail->Next = list;
        mgr->Tail       = list;
    }
}

__INLINE
SLinkList_t *SLinkQueueGet(SLinkListQueue_t *mgr)
{
    SLinkList_t *list = mgr->Head;

    if(mgr->Head == NULL)
    {
        return NULL;
    }

    if(mgr->Head == mgr->Tail)
    {
        mgr->Head = NULL;
        mgr->Tail = NULL;
    }
    else
    {
        mgr->Head = list->Next;
    }

    list->Next = NULL;

    return list;
}

/** @}*/     /** link list component */

/**********************************END OF FILE*********************************/
