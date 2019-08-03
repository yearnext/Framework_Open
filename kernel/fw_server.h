/**
 *******************************************************************************
 *                 Copyright (C) 2017 - 2019  Accumulate Team                  *
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
 * @file       fw_server.h                                                     *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2019-03-22                                                      *
 * @brief      framework server component head file                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2019-03-22    Create File                                                *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FRAMEWORK_SERVER_H__
#define __FRAMEWORK_SERVER_H__

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
#define FwListEntry(node, type, member) \
               ((type *)((uint8_t *)(node) - (uint8_t *)(&((type *)0)->member)))

#define FwListFirstEntry(ptr, type, member) \
                                          FwListEntry((ptr)->Next, type, member)

/**
 *******************************************************************************
 * @brief       Link List For Each
 *******************************************************************************
 */ 
#define FwListForEach(pos, head) \
                        for (pos = (head)->Next; pos != (head); pos = pos->Next)

#define FwListForEachSafe(pos, n, head) \
						for (pos = (head)->Next, n = pos->Next; pos != (head); \
							pos = n, n = pos->Next)

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework buffer type
 *******************************************************************************
 */
typedef struct
{
    uint8_t  *Buffer;
    uint16_t Head;
    uint16_t Tail;
    uint16_t Size;
    uint16_t Len;
}FwBuf_t;

/**
 *******************************************************************************
 * @brief       define framework queue type
 *******************************************************************************
 */
typedef struct
{
    uint8_t  *Buffer;
    uint16_t Tail;
	uint16_t Head;
    uint16_t Len;
}FwQueue_t;

/**
 *******************************************************************************
 * @brief       single link list structure
 *******************************************************************************
 */
typedef struct FW_S_LINK_LIST
{
    struct FW_S_LINK_LIST *Next;
}FwSList_t;

/**
 *******************************************************************************
 * @brief       single link list queue structure
 *******************************************************************************
 */
typedef struct
{
    FwSList_t *Head;
    FwSList_t *Tail;
}FwSListQueue_t;

/**
 *******************************************************************************
 * @brief       link list structure
 *******************************************************************************
 */
typedef struct FW_LINK_LIST
{
    struct FW_LINK_LIST *Next;
    struct FW_LINK_LIST *Prev;
}FwList_t;

/**
 *******************************************************************************
 * @brief       link list queue structure
 *******************************************************************************
 */
typedef struct
{
    FwList_t *Head;
    FwList_t *Tail;
}FwListQueue_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       初始化函数
 *******************************************************************************
 */
extern void Fw_Server_Init(void);

/**
 *******************************************************************************
 * @brief       进入临界点函数
 *******************************************************************************
 */
extern void Fw_Enter_Critical(void);
extern void Fw_Exit_Critical(void);

/**
 *******************************************************************************
 * @brief       ring buffer function api
 *******************************************************************************
 */
extern void     FwBufInit(FwBuf_t *fifo, void *buf, uint16_t len);
extern void     FwBufFini(FwBuf_t *fifo);
extern void     FwBufSetEmpty(FwBuf_t *fifo);
extern uint16_t FwBufLen(FwBuf_t *fifo);
extern uint16_t FwBufUsed(FwBuf_t *fifo);
extern uint16_t FwBufFree(FwBuf_t *fifo);
extern uint16_t FwBufWrite(FwBuf_t *fifo, uint8_t *buf, uint16_t len);
extern uint16_t FwBufWriteByte(FwBuf_t *fifo, uint8_t wrByte);
extern uint16_t FwBufRead(FwBuf_t *fifo, uint8_t *buf, uint16_t len);
extern uint16_t FwBufReadByte(FwBuf_t *fifo);
extern uint16_t FwBufReadMirror(FwBuf_t *fifo, uint8_t *buf, uint16_t len);
extern uint16_t FwBufReadMirrorByte(FwBuf_t *fifo, uint16_t cursor);

/**
 *******************************************************************************
 * @brief       queue function api
 *******************************************************************************
 */
extern void     FwQueueInit(FwQueue_t *queue, uint8_t *buf, uint16_t len);
extern void     FwQueueFini(FwQueue_t *queue);
extern uint16_t FwQueueWrite(FwQueue_t *queue, uint8_t *buf, uint16_t len);
extern uint16_t FwQueueRead(FwQueue_t *queue, uint8_t *buf, uint16_t len);
extern uint16_t FwQueueFree(FwQueue_t *queue);
extern uint16_t FwQueueUsed(FwQueue_t *queue);

/**
 *******************************************************************************
 * @brief       single link list interface
 *******************************************************************************
 */
extern void       FwSListInit(FwSList_t *list);
extern void       FwSListAppend(FwSList_t *list, FwSList_t *node);
extern void       FwSListInsert(FwSList_t *list, FwSList_t *node);
extern void       FwSListRemove(FwSList_t *list, FwSList_t *node);
extern FwSList_t* FwSListTail(FwSList_t *list);
extern uint8_t    FwSListIsEmpty(FwSList_t *list);
extern int        FwSListLen(FwSList_t *list);

/**
 *******************************************************************************
 * @brief       link list interface
 *******************************************************************************
 */
extern void       FwListInit(FwList_t *list);
extern void       FwListInsertAfter(FwList_t *list, FwList_t *node);
extern void       FwListInsertBefore(FwList_t *list, FwList_t *node);
extern void       FwListRemove(FwList_t *list);
extern FwList_t*  FwListDeleteAfter(FwList_t *list);
extern uint8_t    FwListIsEmpty(FwList_t *list);
extern uint8_t    FwListIsLife(FwList_t *list, FwList_t *node);
extern int        FwListLen(FwList_t *list);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
