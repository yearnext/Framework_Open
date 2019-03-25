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
 * @brief       ring buffer function api
 *******************************************************************************
 */
extern void     FwBuf_Init(FwBuf_t *fifo, void *buf, uint16_t len);
extern void     FwBuf_Fini(FwBuf_t *fifo);
extern void     FwBuf_SetEmpty(FwBuf_t *fifo);
extern uint16_t FwBuf_Len(FwBuf_t *fifo);
extern uint16_t FwBuf_Used(FwBuf_t *fifo);
extern uint16_t FwBuf_Free(FwBuf_t *fifo);
extern uint16_t FwBuf_Write(FwBuf_t *fifo, uint8_t *buf, uint16_t len);
extern uint16_t FwBuf_WriteByte(FwBuf_t *fifo, uint8_t wrByte);
extern uint16_t FwBuf_Read(FwBuf_t *fifo, uint8_t *buf, uint16_t len);
extern uint16_t FwBuf_ReadByte(FwBuf_t *fifo);
extern uint16_t FwBuf_ReadMirror(FwBuf_t *fifo, uint8_t *buf, uint16_t len);
extern uint16_t FwBuf_ReadMirrorByte(FwBuf_t *fifo, uint16_t cursor);

/**
 *******************************************************************************
 * @brief       queue function api
 *******************************************************************************
 */
extern void     FwQueue_Init(FwQueue_t *queue, uint8_t *buf, uint16_t len);
extern void     FwQueue_Fini(FwQueue_t *queue);
extern uint16_t FwQueue_Write(FwQueue_t *queue, uint8_t *buf, uint16_t len);
extern uint16_t FwQueue_Read(FwQueue_t *queue, uint8_t *buf, uint16_t len);
extern uint16_t FwQueue_Free(FwQueue_t *queue);
extern uint16_t FwQueue_Used(FwQueue_t *queue);

/**
 *******************************************************************************
 * @brief       single link list interface
 *******************************************************************************
 */
extern void       FwSList_Init(FwSList_t *list);
extern void       FwSList_Append(FwSList_t *list, FwSList_t *node);
extern void       FwSList_Insert(FwSList_t *list, FwSList_t *node);
extern void       FwSList_Remove(FwSList_t *list, FwSList_t *node);
extern FwSList_t* FwSList_Tail(FwSList_t *list);
extern uint8_t    FwSList_IsEmpty(FwSList_t *list);
extern int        FwSList_Len(FwSList_t *list);

/**
 *******************************************************************************
 * @brief       link list interface
 *******************************************************************************
 */
extern void       FwList_Init(FwList_t *list);
extern void       FwList_InsertAfter(FwList_t *list, FwList_t *node);
extern void       FwList_InsertBefore(FwList_t *list, FwList_t *node);
extern void       FwList_Remove(FwList_t *list);
extern FwList_t*  FwList_DeleteAfter(FwList_t *list);
extern uint8_t    FwList_IsEmpty(FwList_t *list);
extern uint8_t    FwList_IsLife(FwList_t *list, FwList_t *node);
extern int        FwList_Len(FwList_t *list);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
