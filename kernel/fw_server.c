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
 * @file       fw_server.c                                                     *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2019-03-22                                                      *
 * @brief      framework server component source file                          *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2019-03-22    创建文件，合并buffer组件和linklist组件内容                 *
 *******************************************************************************
 */
 
/**
* @defgroup framework server component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "fw_server.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        Framework Buffer Component
 *******************************************************************************
 */
/**
 *******************************************************************************
 * @brief       fifo component init
 * @param       [in/out]  *fifo          fifo control block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwBuf_Init(FwBuf_t *fifo, void *buf, uint16_t len)
{
    fifo->Buffer = (uint8_t *)buf;
    fifo->Len    = len;

    fifo->Size   = 0;
    fifo->Head   = 0;
    fifo->Tail   = 0;
}

/**
 *******************************************************************************
 * @brief       deinit fifo
 * @param       [in/out]  *fifo          fifo control block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwBuf_Fini(FwBuf_t *fifo)
{
    fifo->Buffer = NULL;
    fifo->Size   = 0;
    fifo->Head   = 0;
    fifo->Tail   = 0;
    fifo->Len    = 0;
}

/**
 *******************************************************************************
 * @brief       empty fifo control block
 * @param       [in/out]  *fifo          fifo control block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwBuf_SetEmpty(FwBuf_t *fifo)
{
    fifo->Head   = 0;
    fifo->Tail   = 0;
    fifo->Size   = 0;
}

/**
 *******************************************************************************
 * @brief       get fifo length
 * @param       [in/out]  *fifo           fifo control block
 * @param       [in/out]  *size           return data point
 * @return      [in/out]  uint16_t        fifo length
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t FwBuf_Len(FwBuf_t *fifo)
{
    return fifo->Len;
}

/**
 *******************************************************************************
 * @brief       get fifo can read data size
 * @param       [in/out]  *fifo           fifo control block
 * @return      [in/out]  uint16_t        fifo can read data size
 * @note        None
 *******************************************************************************
 */
#define BUFFER_USED(b) ((b)->Size)

__INLINE 
uint16_t FwBuf_Used(FwBuf_t *fifo)
{
    return BUFFER_USED(fifo);
}

/**
 *******************************************************************************
 * @brief       get fifo can write data size
 * @param       [in/out]  *fifo            fifo control block
 * @return      [in/out]  uint16_t         fifo can write data size
 * @note        one byte in the fifo is occupied by the control system
 *******************************************************************************
 */
#define BUFFER_FREE(b) ((b)->Len - (b)->Size - 1)

__INLINE 
uint16_t FwBuf_Free(FwBuf_t *fifo)
{
    return BUFFER_FREE(fifo);
}

/**
 *******************************************************************************
 * @brief       write data to fifo
 * @param       [in/out]  *fifo             fifo control block
 * @param       [in/out]  *buf              write data buffer
 * @param       [in/out]  len               write data buffer length
 * @return      [in/out]  readSize          read data num
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t FwBuf_Write(FwBuf_t *fifo, uint8_t *buf, uint16_t len)
{
    uint16_t free = 0;
    uint16_t i = 0;
    uint16_t canWriteSize = BUFFER_FREE(fifo);
    uint16_t writeSize = 0;
    
    if (len == 0 || IS_PTR_NULL(fifo) || IS_PTR_NULL(fifo->Buffer))
    {
        return 0;
    }
    else if (len <= canWriteSize)
    {
        writeSize = len;
    }
    else
    {
        return 0;
    }

    if((fifo->Tail + writeSize) >= fifo->Len)
    {
        free = fifo->Len - fifo->Tail;

        for(i=0; i<free; i++)
        {
            fifo->Buffer[fifo->Tail++] = buf[i];
        }

        for(fifo->Tail=0; i<writeSize; i++)
        {
            fifo->Buffer[fifo->Tail++] = buf[i];
        }
    }
    else
    {
        for(i=0; i<writeSize; i++)
        {
            fifo->Buffer[fifo->Tail++] = buf[i];
        }
    }

    fifo->Size += writeSize;
        
    return writeSize;
}

/**
 *******************************************************************************
 * @brief       write byte to fifo
 * @param       [in/out]  *fifo              fifo control block
 * @param       [in/out]  wrByte             write byte data
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE 
uint16_t FwBuf_WriteByte(FwBuf_t *fifo, uint8_t wrByte)
{
    if (IS_PTR_NULL(fifo) || IS_PTR_NULL(fifo->Buffer))
    {
        return 0;
    }
    
    if(fifo->Size < fifo->Len - 1)
    {
        fifo->Buffer[fifo->Tail++] = wrByte;

        if(fifo->Tail >= fifo->Len)
        {
            fifo->Tail = 0;
        }

        fifo->Size ++;
    }
    else
    {
        return 0;
    }

    return 1;
}

/**
 *******************************************************************************
 * @brief       read data from fifo
 * @param       [in/out]  *fifo              fifo control block
 * @param       [in/out]  *buf               read data buffer
 * @param       [in/out]  len                read data length
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t FwBuf_Read(FwBuf_t *fifo, uint8_t *buf, uint16_t len)
{
    uint16_t free;
    uint16_t i;
    uint16_t readSize;

    if (len == 0 || IS_PTR_NULL(fifo) || IS_PTR_NULL(fifo->Buffer))
    {
        return 0;
    }
    
    if (len <= fifo->Size)
    {
        readSize = len;
    }
    else
    {
        readSize = fifo->Size;
    }

    if ((fifo->Head + readSize) >= fifo->Len)
    {
        free = fifo->Len - fifo->Head;

        for (i=0; i<free; i++)
        {
             buf[i] = fifo->Buffer[fifo->Head++];
        }

        for (fifo->Head=0; i<readSize; i++)
        {
            buf[i] = fifo->Buffer[fifo->Head++];
        }
    }
    else
    {
        for (i=0; i<readSize; i++)
        {
            buf[i] = fifo->Buffer[fifo->Head++];
        }
    }
    
    fifo->Size -= readSize;
    
    return readSize;
}

/**
 *******************************************************************************
 * @brief       read byte from fifo
 * @param       [in/out]  *fifo              fifo control block
 * @param       [in/out]  *rData             read data buffer
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE 
uint16_t FwBuf_ReadByte(FwBuf_t *fifo)
{
    uint8_t retData;
    
    if(fifo->Size > 0 && !IS_PTR_NULL(fifo) && !IS_PTR_NULL(fifo->Buffer))
    {
        retData = fifo->Buffer[fifo->Head++];

        if(fifo->Head >= fifo->Len)
        {
            fifo->Head = 0;
        }

        fifo->Size--;
    }
    else
    {
        return 0xFFFF;
    }

    return retData;
}

/**
 *******************************************************************************
 * @brief       read data from fifo mirror
 * @param       [in/out]  *fifo              fifo control block
 * @param       [in/out]  *buf               read data buffer
 * @param       [in/out]  len                read data length
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE 
uint16_t FwBuf_ReadMirror(FwBuf_t *fifo, uint8_t *buf, uint16_t len)
{
    uint16_t free = 0;
    uint16_t i = 0;
    uint16_t readSize = 0;
    uint16_t head = fifo->Head;
 
    if (len == 0 || IS_PTR_NULL(fifo) || IS_PTR_NULL(fifo->Buffer))
    {
        return 0;
    }
    
    if (len <= fifo->Size)
    {
        readSize = len;
    }
    else
    {
        readSize = fifo->Size;
    }
    
    if ((head + readSize) >= fifo->Len)
    {
        free = fifo->Len - head;

        for (i=0; i<free; i++)
        {
             buf[i] = fifo->Buffer[head++];
        }

        for (head=0; i<readSize; i++)
        {
            buf[i] = fifo->Buffer[head++];
        }
    }
    else
    {
        for (i=0; i<readSize; i++)
        {
            buf[i] = fifo->Buffer[head++];
        }
    }

    return readSize;
}

/**
 *******************************************************************************
 * @brief       read byte from fifo mirror
 * @param       [in/out]  *fifo              fifo control block
 * @param       [in/out]  *rData             read data buffer
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t FwBuf_ReadMirrorByte(FwBuf_t *fifo, uint16_t cursor)
{
    uint16_t max = BUFFER_USED(fifo);
    uint16_t pos = fifo->Head + cursor;
    
    if(IS_PTR_NULL(fifo) || IS_PTR_NULL(fifo->Buffer))
    {
        return 0; 
    }
    
    if(cursor >= max)
    {
        return 0xFFFF;
    }

    if(pos >= fifo->Len)
    {
        pos -= fifo->Len;
    }
    
    return fifo->Buffer[pos];
}

/**
 *******************************************************************************
 * @brief        Framework Queue Component
 *******************************************************************************
 */
/**
 *******************************************************************************
 * @brief       init queue
 * @param       [in/out]  *queue             queue block
 * @param       [in/out]  *buf               buffer
 * @param       [in/out]  len                buffer size
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE 
void FwQueue_Init(FwQueue_t *queue, uint8_t *buf, uint16_t len)
{
    queue->Buffer = buf;
	queue->Len    = len;
	queue->Head   = 0;
    queue->Tail   = 0;
}

/**
 *******************************************************************************
 * @brief       deinit queue
 * @param       [in/out]  *queue             queue block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE 
void FwQueue_Fini(FwQueue_t *queue)
{
    queue->Buffer = NULL;
	queue->Len    = 0;
	queue->Head   = 0;
    queue->Tail   = 0;
}

/**
 *******************************************************************************
 * @brief       write data to data queue
 * @param       [in/out]  *queue             queue block
 * @param       [in/out]  *buf               buffer
 * @param       [in/out]  len                buffer size
 * @return      [in/out]  len                write size
 * @note        None
 *******************************************************************************
 */
__INLINE 
uint16_t FwQueue_Write(FwQueue_t *queue, uint8_t *buf, uint16_t len)
{
	uint16_t freeSize = queue->Len - queue->Tail - 1;

	if(len > freeSize)
	{
		return 0;
	}
	
	memcpy(&queue->Buffer[queue->Tail], buf, len);

	queue->Tail += len;

	return len;
}

/**
 *******************************************************************************
 * @brief       read data from data queue
 * @param       [in/out]  *queue             queue block
 * @param       [in/out]  *buf               buffer
 * @param       [in/out]  len                buffer size
 * @return      [in/out]  len                read size
 * @note        None
 *******************************************************************************
 */
__INLINE 
uint16_t FwQueue_Read(FwQueue_t *queue, uint8_t *buf, uint16_t len)
{
	uint16_t useSize = queue->Tail - queue->Head;

	if(len > useSize)
	{
		return 0;
	}
	
	memcpy(buf, &queue->Buffer[queue->Head], len);

	queue->Head += len;

	return len;
}

/**
 *******************************************************************************
 * @brief       get queue free size
 * @param       [in/out]  *queue             queue block
 * @return      [in/out]  uint16_t           free size
 * @note        None
 *******************************************************************************
 */
__INLINE uint16_t FwQueue_Free(FwQueue_t *queue)
{
	return queue->Len - queue->Tail - 1;
}

/**
 *******************************************************************************
 * @brief       get queue use size
 * @param       [in/out]  *queue             queue block
 * @return      [in/out]  uint16_t           queue use size
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t FwQueue_Used(FwQueue_t *queue)
{
	return queue->Tail - queue->Head;
}

/**
 *******************************************************************************
 * @brief        Framework Single Link List Component
 *******************************************************************************
 */

/**
 *******************************************************************************
 * @brief       init single link list
 * @param       [in/out]  *list             single link list
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwSList_Init(FwSList_t *list)
{
    list->Next = NULL;
}

/**
 *******************************************************************************
 * @brief       append single link list
 * @param       [in/out]  *list             single link list head
 * @param       [in/out]  *node             single link list node
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwSList_Append(FwSList_t *list, FwSList_t *node)
{
	FwSList_t *cur = list;

	while (cur->Next != NULL)
	{
		cur = cur->Next;
	}

	cur->Next  = node;
	node->Next = NULL;
}

/**
 *******************************************************************************
 * @brief       insert single link list
 * @param       [in/out]  *list             single link list head
 * @param       [in/out]  *node             single link list node
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwSList_Insert(FwSList_t *list, FwSList_t *node)
{
	node->Next = list->Next;
	list->Next = node;
}

/**
 *******************************************************************************
 * @brief       remove single link list
 * @param       [in/out]  *list             single link list head
 * @param       [in/out]  *node             single link list node
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwSList_Remove(FwSList_t *list, FwSList_t *node)
{
    FwSList_t *cur = list;

	while (cur->Next != NULL && cur->Next != node)
	{
		cur = cur->Next;
	}

	if (cur->Next != NULL)
	{
		cur->Next  = node->Next;
		node->Next = NULL;
	}
}

/**
 *******************************************************************************
 * @brief       get single link list tail
 * @param       [in/out]  *list             single link list head
 * @return      [in/out]  *list             single link list tail
 * @note        None
 *******************************************************************************
 */
__INLINE
FwSList_t *FwSList_Tail(FwSList_t *list)
{
	for (; list->Next != NULL; list = list->Next);

	return list;
}

/**
 *******************************************************************************
 * @brief       check single link list is empty
 * @param       [in/out]  *list             single link list head
 * @return      [in/out]  0                 not empty
 * @return      [in/out]  1                 is empty
 * @note        None
 *******************************************************************************
 */
__INLINE
uint8_t FwSList_IsEmpty(FwSList_t *list)
{
	return (list->Next == NULL);
}

/**
 *******************************************************************************
 * @brief       get single link list tail
 * @param       [in/out]  *list             single link list head
 * @return      [in/out]  len               single link list length
 * @note        None
 *******************************************************************************
 */
__INLINE
int FwSList_Len(FwSList_t *list)
{
    int len = 0;

	for (; list->Next != NULL; list = list->Next, len ++);

    return len;
}

/**
 *******************************************************************************
 * @brief        Framework Link List Component
 *******************************************************************************
 */
/**
 *******************************************************************************
 * @brief       init link list
 * @param       [in/out]  *list             link list head
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwList_Init(FwList_t *list)
{
	list->Next = list;
	list->Prev = list;
}

/**
 *******************************************************************************
 * @brief       insert link list
 * @param       [in/out]  *list             link list head
 * @param       [in/out]  *list             insert link list node
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwList_InsertAfter(FwList_t *list, FwList_t *node)
{
	//! N插入在L之后
	list->Next->Prev = node;
	node->Next = list->Next;

	list->Next = node;
	node->Prev = list;
}

/**
 *******************************************************************************
 * @brief       insert link list
 * @param       [in/out]  *list             link list head
 * @param       [in/out]  *list             insert link list node
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwList_InsertBefore(FwList_t *list, FwList_t *node)
{
	//! N插入在L之前
	list->Prev->Next = node;
	node->Prev       = list->Prev;

	list->Prev       = node;
	node->Next       = list;
}

/**
 *******************************************************************************
 * @brief       remove link list
 * @param       [in/out]  *list             link list head
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
void FwList_Remove(FwList_t *list)
{
	list->Next->Prev = list->Prev;
	list->Prev->Next = list->Next;

	list->Prev = list;
	list->Next = list;
}

/**
 *******************************************************************************
 * @brief       remove link list
 * @param       [in/out]  *list             link list head
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
FwList_t *FwList_DeleteAfter(FwList_t *list)
{
	FwList_t *result = list->Next;

	FwList_Remove(result);

	return (result == list) ? (NULL) : (result);
}

/**
 *******************************************************************************
 * @brief       check link list is empty
 * @param       [in/out]  *list             link list head
 * @return      [in/out]  0                 not empty
 * @return      [in/out]  1                 is empty
 * @note        None
 *******************************************************************************
 */
__INLINE
uint8_t FwList_IsEmpty(FwList_t *list)
{
	return (list->Next == list);
}

/**
 *******************************************************************************
 * @brief       check link list is life
 * @param       [in/out]  *list             link list head
 * @param       [in/out]  *list             link list node
 * @return      [in/out]  0                 not empty
 * @return      [in/out]  1                 is empty
 * @note        None
 *******************************************************************************
 */
__INLINE
uint8_t FwList_IsLife(FwList_t *list, FwList_t *node)
{
    FwList_t *p = list;
    
	while (p->Next != list)
	{
		if (p->Next == node)
		{
			return 1;
		}

		p = p->Next;
	}

	return 0;
}

/**
 *******************************************************************************
 * @brief       get link list len
 * @param       [in/out]  *list             link list head
 * @return      void
 * @note        None
 *******************************************************************************
 */
__INLINE
int FwList_Len(FwList_t *list)
{
	int len = 0;
	FwList_t *p = list;

	for (; p->Next != list; p = p->Next, len ++);

	return len;
}

/** @}*/     /** framework server component */

/**********************************END OF FILE*********************************/
