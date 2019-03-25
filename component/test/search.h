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
 * @file       serach.h                                                        *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-10-24                                                      *
 * @brief      serach component head file                                      *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20181024    创建文件                                                      *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SERACH_COMPONENT_H__
#define __SERACH_COMPONENT_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       正常查表
 * @param       [in/out]  in          输入数据
 * @param       [in/out]  *tab        数据表
 * @param       [in/out]  len         数据表长度
 * @return      [in/out]  uint16_t    结果
 * @note        None
 *******************************************************************************
 */
extern uint16_t NormalSearchU8(uint8_t in,   const uint8_t *tab,  uint16_t len);
extern uint16_t NormalSearchU16(uint16_t in, const uint16_t *tab, uint16_t len);
extern uint16_t NormalSearchU32(uint32_t in, const uint32_t *tab, uint16_t len);
extern uint16_t NormalSearchS8(int8_t in,    const int8_t *tab,   uint16_t len);
extern uint16_t NormalSearchS16(int16_t in,  const int16_t *tab,  uint16_t len);
extern uint16_t NormalSearchS32(int32_t in,  const int32_t *tab,  uint16_t len);

/**
 *******************************************************************************
 * @brief       二分法查表
 * @param       [in/out]  in          输入数据
 * @param       [in/out]  *tab        数据表
 * @param       [in/out]  len         数据表长度
 * @return      [in/out]  uint16_t    结果
 * @note        None
 *******************************************************************************
 */
extern uint16_t BinarySearchU8(uint8_t in,   const uint8_t *tab,  uint16_t len);
extern uint16_t BinarySearchU16(uint16_t in, const uint16_t *tab, uint16_t len);
extern uint16_t BinarySearchU32(uint32_t in, const uint32_t *tab, uint16_t len);
extern uint16_t BinarySearchS8(int8_t in,    const int8_t *tab,   uint16_t len);
extern uint16_t BinarySearchS16(int16_t in,  const int16_t *tab,  uint16_t len);
extern uint16_t BinarySearchS32(int32_t in,  const int32_t *tab,  uint16_t len);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
