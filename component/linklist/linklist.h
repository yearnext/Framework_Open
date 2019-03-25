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
 * @file       linklist.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2017-02-18                                                      *
 * @brief      link list component head files                                  *
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
 * @defgroup link list component
 * @{
 */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LINK_LIST_COMPONENT_H__
#define __LINK_LIST_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"

/* Exported macro ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       cal link list data area address
 *******************************************************************************
 */ 
#define LinkListEntry(node, type, member) \
   ((type *)((uint8_t *)(node) - (uint8_t *)(&((type *)0)->member)))

#define LinkList_First_Entry(ptr, type, member) \
    LinkListEntry((ptr)->Next, type, member)

/**
 *******************************************************************************
 * @brief       Link List For Each
 *******************************************************************************
 */ 
#define LinkListForEach(pos, head) \
    for (pos = (head)->Next; pos != (head); pos = pos->Next)

#define LinkListForEachSafe(pos, n, head) \
	for (pos = (head)->Next, n = pos->Next; pos != (head); \
		pos = n, n = pos->Next)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       link list structure
 *******************************************************************************
 */
typedef struct LinkList
{
    struct LinkList *Next;
    struct LinkList *Prev;
}LinkList_t;

/**
 *******************************************************************************
 * @brief       link list queue structure
 *******************************************************************************
 */
typedef struct LinkListQueue
{
    LinkList_t *Head;
    LinkList_t *Tail;
}LinkListQueue_t;

/**
 *******************************************************************************
 * @brief       single link list structure
 *******************************************************************************
 */
typedef struct SLinkList
{
    struct SLinkList *Next;
}SLinkList_t;

/**
 *******************************************************************************
 * @brief       single link list queue structure
 *******************************************************************************
 */
typedef struct SLinkListQueue
{
    SLinkList_t *Head;
    SLinkList_t *Tail;
}SLinkListQueue_t;

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       single link list interface
 *******************************************************************************
 */
extern void         SLinkListInit(SLinkList_t *l);
extern void         SLinkListAppend(SLinkList_t *l, SLinkList_t *n);
extern void         SLinkListInsert(SLinkList_t *l, SLinkList_t *n);
extern SLinkList_t* SLinkListRemove(SLinkList_t *l, SLinkList_t *n);
extern SLinkList_t* SLinkList_Head(SLinkList_t *l);
extern SLinkList_t* SLinkList_Tail(SLinkList_t *l);
extern SLinkList_t* SLinkList_Next(SLinkList_t *n);
extern uint8_t      SLinkListIsEmpty(SLinkList_t *head);
extern int          SLinkListLen(SLinkList_t *head);

/**
 *******************************************************************************
 * @brief       link list interface
 *******************************************************************************
 */
extern void         LinkListInit(LinkList_t *list);
extern void         LinkListInsertAfter(LinkList_t *l, LinkList_t *n);
extern void         LinkListInsertBefore(LinkList_t *l, LinkList_t *n);
extern LinkList_t*  LinkListDeleteAfter(LinkList_t *l);
extern void         LinkListRemove(LinkList_t *list);
extern uint8_t      LinkListIsEmpty(LinkList_t *list);
extern uint8_t      LinkListIsLife(LinkList_t *head, LinkList_t *list);
extern int          LinkListLen(LinkList_t *head);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** link list component */

/**********************************END OF FILE*********************************/
