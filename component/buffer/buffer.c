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
 * @file       buffer.c                                                        *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2016-06-06                                                      *
 * @brief      buffer component source file                                    *
 * @par        work platform                                                   * 
 *                 Windows                                                     *
 * @par        compiler                                                        *
 * 				   GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 5. 2018-02-27 更名为buffer.c                                                *
 * 4. 2018-02-26 移除断言                                                      *
 * 3. 2018-02-26 独立组件更名为utility_buffer.c                                *
 * 2. 2017-01-16 加入YSF框架组件内容更名为fw_buffer.c                          *
 * 1. 2016-06-06 创建文件ringbuffer.c                                          *
 *******************************************************************************
 */
 
/**
 * @defgroup buffer component
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include "buffer.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ring buffer init
 * @param       [in/out]  *rb            ring buff control block
 * @param       [in/out]  *buffer        buffer
 * @param       [in/out]  size           buffer size
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void RingBufferInit(struct RingBuffer *rb, void *buf, uint16_t len)
{
    rb->Buffer = (uint8_t *)buf;
    rb->Size   = 0;
    rb->Head   = 0;
    rb->Tail   = 0;
    rb->Len    = len;
}

/**
 *******************************************************************************
 * @brief       empty ring buffer
 * @param       [in/out]  *rb            ring buff control block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void RingBufferSetEmpty(struct RingBuffer *rb)
{
    rb->Head   = 0;
    rb->Tail   = 0;
    rb->Size   = 0;
}

/**
 *******************************************************************************
 * @brief       deinit ring buffer
 * @param       [in/out]  *rb            ring buff control block
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
__INLINE
void RingBufferFini(struct RingBuffer *rb)
{
    rb->Buffer = NULL;
    rb->Size   = 0;
    rb->Head   = 0;
    rb->Tail   = 0;
    rb->Len    = 0;
}

/**
 *******************************************************************************
 * @brief       get ring buffer length
 * @param       [in/out]  *rb                 ring buff control block
 * @param       [in/out]  *size               return data point
 * @return      [in/out]  uint16_t            ring buffer length
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t RingBufferLen(struct RingBuffer *rb)
{
    return rb->Len;
}

/**
 *******************************************************************************
 * @brief       get ring buffer can read data size
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  uint16_t            ring buffer can read data size
 * @note        None
 *******************************************************************************
 */
__INLINE 
uint16_t RingBufferUse(struct RingBuffer *rb)
{
    return rb->Size;
}

/**
 *******************************************************************************
 * @brief       get ring buffer can write data size
 * @param       [in/out]  *rb                 ring buffer control block
 * @return      [in/out]  uint16_t            ring buffer can write data size
 * @note        one byte in the ring buffer is occupied by the control system
 *******************************************************************************
 */
__INLINE 
uint16_t RingBufferFree(struct RingBuffer *rb)
{
    return rb->Len - rb->Size - 1;
}

/**
 *******************************************************************************
 * @brief       write data to ring buffer
 * @param       [in/out]  *rb                ring buffer control block
 * @param       [in/out]  *buf               write data buffer
 * @param       [in/out]  len                write data buffer length
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t RingBufferWrite(struct RingBuffer *rb, uint8_t *buf, uint16_t len)
{
    uint16_t free = 0;
    uint16_t i = 0;
    uint16_t canWriteSize = RingBufferFree(rb);
    uint16_t writeSize = 0;
    
    if (len == 0 || IS_PTR_NULL(rb) || IS_PTR_NULL(rb->Buffer))
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

    if((rb->Tail + writeSize) >= rb->Len)
    {
        free = rb->Len - rb->Tail;

        for(i=0; i<free; i++)
        {
            rb->Buffer[rb->Tail++] = buf[i];
        }

        for(rb->Tail=0; i<writeSize; i++)
        {
            rb->Buffer[rb->Tail++] = buf[i];
        }
    }
    else
    {
        for(i=0; i<writeSize; i++)
        {
            rb->Buffer[rb->Tail++] = buf[i];
        }
    }

    rb->Size += writeSize;
        
    return writeSize;
}

/**
 *******************************************************************************
 * @brief       write byte to ring buffer
 * @param       [in/out]  *rb                ring buffer control block
 * @param       [in/out]  wrByte             write byte data
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE 
uint16_t RingBufferWriteByte(struct RingBuffer *rb, uint8_t wrByte)
{
    if (IS_PTR_NULL(rb) || IS_PTR_NULL(rb->Buffer))
    {
        return 0;
    }
    
    if(rb->Size < rb->Len - 1)
    {
        rb->Buffer[rb->Tail++] = wrByte;

        if(rb->Tail >= rb->Len)
        {
            rb->Tail = 0;
        }

        rb->Size ++;
    }
    else
    {
        return 0;
    }

    return 1;
}

/**
 *******************************************************************************
 * @brief       read data from ring buffer
 * @param       [in/out]  *rb                ring buffer control block
 * @param       [in/out]  *buf               read data buffer
 * @param       [in/out]  len                read data length
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t RingBufferRead(struct RingBuffer *rb, uint8_t *buf, uint16_t len)
{
    uint16_t free;
    uint16_t i;
    uint16_t readSize;

    if (len == 0 || IS_PTR_NULL(rb) || IS_PTR_NULL(rb->Buffer))
    {
        return 0;
    }
    
    if (len <= rb->Size)
    {
        readSize = len;
    }
    else
    {
        readSize = rb->Size;
    }

    if ((rb->Head + readSize) >= rb->Len)
    {
        free = rb->Len - rb->Head;

        for (i=0; i<free; i++)
        {
             buf[i] = rb->Buffer[rb->Head++];
        }

        for (rb->Head=0; i<readSize; i++)
        {
            buf[i] = rb->Buffer[rb->Head++];
        }
    }
    else
    {
        for (i=0; i<readSize; i++)
        {
            buf[i] = rb->Buffer[rb->Head++];
        }
    }
    
    rb->Size -= readSize;
    
    return readSize;
}

/**
 *******************************************************************************
 * @brief       read data from ring buffer mirror
 * @param       [in/out]  *rb                ring buffer control block
 * @param       [in/out]  *buf               read data buffer
 * @param       [in/out]  len                read data length
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE 
uint16_t RingBufferReadMirror(struct RingBuffer *rb, uint8_t *buf, uint16_t len)
{
    uint16_t free = 0;
    uint16_t i = 0;
    uint16_t readSize = 0;
    uint16_t head = rb->Head;
 
    if (len == 0 || IS_PTR_NULL(rb) || IS_PTR_NULL(rb->Buffer))
    {
        return 0;
    }
    
    if (len <= rb->Size)
    {
        readSize = len;
    }
    else
    {
        readSize = rb->Size;
    }
    
    if ((head + readSize) >= rb->Len)
    {
        free = rb->Len - head;

        for (i=0; i<free; i++)
        {
             buf[i] = rb->Buffer[head++];
        }

        for (head=0; i<readSize; i++)
        {
            buf[i] = rb->Buffer[head++];
        }
    }
    else
    {
        for (i=0; i<readSize; i++)
        {
            buf[i] = rb->Buffer[head++];
        }
    }

    return readSize;
}

/**
 *******************************************************************************
 * @brief       read byte from ring buffer
 * @param       [in/out]  *rb                ring buffer control block
 * @param       [in/out]  *rData             read data buffer
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE 
uint16_t RingBufferReadByte(struct RingBuffer *rb)
{
    uint8_t retData;
    
    if(rb->Size > 0 && !IS_PTR_NULL(rb) && !IS_PTR_NULL(rb->Buffer))
    {
        retData = rb->Buffer[rb->Head++];

        if(rb->Head >= rb->Len)
        {
            rb->Head = 0;
        }

        rb->Size--;
    }
    else
    {
        return 0xFFFF;
    }

    return retData;
}

/**
 *******************************************************************************
 * @brief       read byte from ring buffer mirror
 * @param       [in/out]  *rb                ring buffer control block
 * @param       [in/out]  *rData             read data buffer
 * @return      [in/out]  readSize           read data num
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t RingBufferReadMirrorByte(struct RingBuffer *rb, uint16_t cursor)
{
    uint16_t max = RingBufferUse(rb);
    uint16_t pos = rb->Head + cursor;
    
    if(IS_PTR_NULL(rb) || IS_PTR_NULL(rb->Buffer))
    {
        return 0; 
    }
    
    if(cursor >= max)
    {
        return 0xFFFF;
    }

    if(pos >= rb->Len)
    {
        pos -= rb->Len;
    }
    
    return rb->Buffer[pos];
}

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
void SimpleQueueInit(struct SimpleQueue *queue, uint8_t *buf, uint16_t len)
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
void SimpleQueueFini(struct SimpleQueue *queue)
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
uint16_t SimpleQueueWrite(struct SimpleQueue *queue, uint8_t *buf, uint16_t len)
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
uint16_t SimpleQueueRead(struct SimpleQueue *queue, uint8_t *buf, uint16_t len)
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
__INLINE uint16_t SimpleQueueFree(struct SimpleQueue *queue)
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
uint16_t SimpleQueueUse(struct SimpleQueue *queue)
{
	return queue->Tail - queue->Head;
}

/** @}*/     /** framework buffer component */

/**********************************END OF FILE*********************************/
