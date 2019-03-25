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
 * @file       checksum.h                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2016-08-21                                                      *
 * @brief      checksum component head file                                    *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20160821    创建文件                                                      *
 * 2.20181022    修改文件结构                                                  *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CHECK_SUM_COMPONENT_H__
#define __CHECK_SUM_COMPONENT_H__

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
 * @brief       计算校验和-计算结果为1字节数据
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  checkSum     
 * @note        None
 *******************************************************************************
 */
extern uint8_t CheckSum_U8_Cal(uint8_t *buf, uint16_t len);

/**
 *******************************************************************************
 * @brief       计算校验和-计算结果为2字节数据
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  checkSum     
 * @note        None
 *******************************************************************************
 */
extern uint16_t CheckSum_U16_Cal(uint8_t *buf, uint16_t len);

/**
 *******************************************************************************
 * @brief       计算校验和-计算结果为4字节数据
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  checkSum     
 * @note        None
 *******************************************************************************
 */
extern uint32_t CheckSum_U32_Cal(uint8_t *buf, uint16_t len);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
