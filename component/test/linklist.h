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
 * @brief       link list interface
 *******************************************************************************
 */
extern void         LinkListInit(LinkList_t *list);
extern int8_t       LinkListAdd(LinkList_t *head, LinkList_t *list);
extern int8_t       LinkListTraverseAdd(LinkList_t *head, LinkList_t *list);
extern int8_t       LinkListTraverseRemove(LinkList_t *head, LinkList_t *list);
extern void         LinkListRemove(LinkList_t *list);
extern bool         LinkListIsEmpty(LinkList_t *head);
extern bool         LinkListIsLife(LinkList_t *head, LinkList_t *list);
extern uint16_t     LinkListLen(LinkList_t *head);

/**
 *******************************************************************************
 * @brief       link list queue interface
 *******************************************************************************
 */
extern void         LinkQueueInit(LinkListQueue_t *mgr);
extern void         LinkQueueTraverseRemove(LinkListQueue_t *mgr, LinkList_t *list);
extern void         LinkQueuePut(LinkListQueue_t *mgr, LinkList_t *list);
extern LinkList_t*  LinkQueueGet(LinkListQueue_t *mgr);
extern bool         LinkQueueIsEmpty(LinkListQueue_t *mgr);
extern bool         LinkQueueIsLife(LinkListQueue_t *mgr, LinkList_t *list);
extern void         LinkQueueCpy(LinkListQueue_t *dst, LinkListQueue_t *src);
extern uint16_t     LinkQueueLen(LinkListQueue_t *mgr);

/**
 *******************************************************************************
 * @brief       single link list interface
 *******************************************************************************
 */
extern void         SLinkListInit(SLinkList_t *head);
extern int8_t       SLinkListAdd(SLinkList_t *head, SLinkList_t *list);
extern int8_t       SLinkListRemove(SLinkList_t *head, SLinkList_t *list);
extern bool         SLinkListIsEmpty(SLinkList_t *head);
extern uint16_t     SLinkListLen(SLinkList_t *head);

/**
 *******************************************************************************
 * @brief       single link list queue structure
 *******************************************************************************
 */
extern void         SLinkQueueInit(SLinkListQueue_t *mgr);
extern void         SLinkQueuePut(SLinkListQueue_t *mgr, SLinkList_t *list);
extern SLinkList_t* SLinkQueueGet(SLinkListQueue_t *mgr);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** link list component */

/**********************************END OF FILE*********************************/
