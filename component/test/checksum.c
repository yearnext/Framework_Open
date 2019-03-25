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
 * @file       checksum.c                                                      *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2016-08-21                                                      *
 * @brief      checksum component source file                                  *
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
 
/**
* @defgroup checksum component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "checksum.h"

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
 * @brief       计算校验和-计算结果为4字节数据
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  checkSum     
 * @note        私有
 *******************************************************************************
 */
__INLINE
uint32_t CheckSum_Default_Cal(uint8_t *buf, uint16_t len)
{
	uint32_t checkSum = 0;
	
	//! 针对32位硬件系统进行优化
	uint32_t r = len >> 2;
	uint32_t m = len & 0x03;
	
	uint32_t *bufWord = (uint32_t *)buf;
	uint8_t  *bufByte = buf + len - m;
	
	while(r --)
	{
		checkSum += *bufWord++;
	}
	
	while(m --)
	{
		checkSum += *bufByte++;
	}
	
	return checkSum;
}

/**
 *******************************************************************************
 * @brief       计算校验和-计算结果为1字节数据
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  checkSum     
 * @note        None
 *******************************************************************************
 */
__INLINE
uint8_t CheckSum_Byte_Cal(uint8_t *buf, uint16_t len)
{
	return (uint8_t)CheckSum_Default_Cal(buf, len);
}

/**
 *******************************************************************************
 * @brief       计算校验和-计算结果为2字节数据
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  checkSum     
 * @note        None
 *******************************************************************************
 */
__INLINE
uint16_t CheckSum_HalfWord_Cal(uint8_t *buf, uint16_t len)
{
	return (uint16_t)CheckSum_Default_Cal(buf, len);
}

/**
 *******************************************************************************
 * @brief       计算校验和-计算结果为4字节数据
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  checkSum     
 * @note        None
 *******************************************************************************
 */
__INLINE
uint32_t CheckSum_Word_Cal(uint8_t *buf, uint16_t len)
{
	return CheckSum_Default_Cal(buf, len);
}

/**
 *******************************************************************************
 * @brief       计算校验和-计算结果为8字节数据
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  checkSum     
 * @note        None
 *******************************************************************************
 */
__INLINE
uint64_t CheckSum_DoubleWord_Cal(uint8_t *buf, uint16_t len)
{
	uint64_t checkSum = 0;
	
	//! 针对64位硬件系统进行优化
	uint64_t r = len >> 3;
	uint64_t m = len & 0x07;
	
	uint64_t *bufLongWord = (uint64_t *)buf;
	uint8_t  *bufByte = buf + len - m;
	
	while(r --)
	{
		checkSum += *bufLongWord++;
	}
	
	while(m --)
	{
		checkSum += *bufByte++;
	}
	
	return checkSum;
}

/** @}*/     /** checksum component */

/**********************************END OF FILE*********************************/
