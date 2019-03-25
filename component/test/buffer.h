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
 * @file       utility_buffer.h                                                *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2016-06-06                                                      *
 * @brief      buffer component head files                                     *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 3. 2018-02-26 独立组件更名为utility_buffer.h                                *
 * 2. 2017-01-16 加入YSF框架组件内容更名为fw_buffer.h                          *
 * 1. 2016-06-06 创建文件ringbuffer.h                                          *
 *******************************************************************************
 */
 
/**
 * @defgroup buffer component
 * @{
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUFFER_COMPONENT_H__
#define __BUFFER_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "..\compiler\compiler.h"
    
/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       define framework buffer type
 *******************************************************************************
 */
struct RingBuffer
{
    uint8_t  *Buffer;
    uint16_t Head;
    uint16_t Tail;
    uint16_t Size;
    uint16_t Len;
};

typedef struct RingBuffer SimpleFifo_t;

/**
 *******************************************************************************
 * @brief       define framework queue type
 *******************************************************************************
 */
struct SimpleQueue
{
    uint8_t  *Buffer;
    uint16_t Tail;
	uint16_t Head;
    uint16_t Len;
};

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       ring buffer function api
 *******************************************************************************
 */
extern void     RingBufferInit(struct RingBuffer*, uint8_t*, uint16_t);
extern void     RingBufferSetEmpty(struct RingBuffer *rb);
extern void     RingBufferFini(struct RingBuffer*);
extern uint16_t RingBufferLen(struct RingBuffer*);
extern uint16_t RingBufferUse(struct RingBuffer *rb);
extern uint16_t RingBufferFree(struct RingBuffer *rb);
extern uint16_t RingBufferWrite(struct RingBuffer*, uint8_t*, uint16_t);
extern uint16_t RingBufferWriteByte(struct RingBuffer*, uint8_t);
extern uint16_t RingBufferRead(struct RingBuffer*, uint8_t*, uint16_t);
extern uint16_t RingBufferReadMirror(struct RingBuffer*, uint8_t*, uint16_t);
extern uint16_t RingBufferReadByte(struct RingBuffer*);
extern uint16_t RingBufferReadMirrorByte(struct RingBuffer*, uint16_t);

/**
 *******************************************************************************
 * @brief       queue function api
 *******************************************************************************
 */
extern void SimpleQueueInit(struct SimpleQueue*, uint8_t*, uint16_t);
extern void SimpleQueueFini(struct SimpleQueue*);
extern uint16_t SimpleQueueWrite(struct SimpleQueue*, uint8_t*, uint16_t);
extern uint16_t SimpleQueueRead(struct SimpleQueue*, uint8_t*, uint16_t);
extern uint16_t SimpleQueueFree(struct SimpleQueue*);
extern uint16_t SimpleQueueUse(struct SimpleQueue*);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
	
#endif       /** end include define */

/** @}*/     /** buffer component */

/**********************************END OF FILE*********************************/
