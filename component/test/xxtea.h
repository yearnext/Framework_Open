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
 * @file       xxtea.h                                                         *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-10-20                                                      *
 * @brief      xxtea encryption component head file                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20181020    创建文件                                                      *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __XXTEA_DECRYPTION_COMPONENT_H__
#define __XXTEA_DECRYPTION_COMPONENT_H__

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
 * @brief      定义加密相关属性
 *******************************************************************************
 */
#define XXTEA_DELTA                                                   0x9E3779B9
#define XXTEA_MX  (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	//! 128 bit 加密密钥
	uint8_t Key[16];
	//! 加密轮数
	uint32_t Rounds;
}xxTea_Handle_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief       xxtea数据加密函数
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @param       [in/out]  *key         加密密钥
 * @param       [in/out]  rounds       加密轮数
 * @return      [in/out]  void
 * @note        输入数据强制要求4字节对齐
 *******************************************************************************
 */
extern void xxTea_Data_Encrypt(uint32_t *buf, uint16_t len, uint32_t *key, uint32_t rounds);

/**
 *******************************************************************************
 * @brief       xxtea数据解密函数
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @param       [in/out]  *key         加密密钥
 * @param       [in/out]  rounds       加密轮数
 * @return      [in/out]  void
 * @note        输入数据强制要求4字节对齐
 *******************************************************************************
 */
extern void xxTea_Data_Decrypt(uint32_t *buf, uint16_t len, uint32_t *key, uint32_t rounds);

/**
 *******************************************************************************
 * @brief       xxtea组件初始化函数
 * @param       [in/out]  *handle      组件句柄
 * @param       [in/out]  *key         加密密钥
 * @param       [in/out]  rounds       加密轮数
 * @return      [in/out]  void
 * @note        None
 *******************************************************************************
 */
extern void xxTea_Init(xxTea_Handle_t *handle, uint16_t *key, uint32_t rounds);

/**
 *******************************************************************************
 * @brief       xxtea组件加密函数
 * @param       [in/out]  *handle      组件句柄
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  void
 * @note        输入数据强制要求4字节对齐
 *******************************************************************************
 */
extern void xxTea_Encrypt(xxTea_Handle_t *handle, uint32_t *buf, uint16_t len);

/**
 *******************************************************************************
 * @brief       xxtea组件解密函数
 * @param       [in/out]  *handle      组件句柄
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @return      [in/out]  void
 * @note        输入数据强制要求4字节对齐
 *******************************************************************************
 */
extern void xxTea_Decrypt(xxTea_Handle_t *handle, uint32_t *buf, uint16_t len);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
