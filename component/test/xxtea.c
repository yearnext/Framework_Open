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
 * @file       xxtea.c                                                         *
 * @author     yearnext                                                        *
 * @version    1.0.0                                                           *
 * @date       2018-10-20                                                      *
 * @brief      xxtea encryption component source file                          *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20181020    创建文件                                                      *
 *******************************************************************************
 */
 
/**
* @defgroup xxtea encryption component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "xxtea.h"

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
 * @brief       xxtea数据加密函数
 * @param       [in/out]  *buf         输入数据
 * @param       [in/out]  len          数据长度
 * @param       [in/out]  *key         加密密钥
 * @param       [in/out]  rounds       加密轮数
 * @return      [in/out]  void
 * @note        输入数据强制要求4字节对齐
 *******************************************************************************
 */
__INLINE
void xxTea_Data_Encrypt(uint32_t *buf, uint16_t len, uint32_t *key, uint32_t rounds)
{
	uint32_t p, q;
	uint32_t e, sum = 0;
	uint32_t n;
	uint32_t z, y;

#ifdef ENABLE_FRAMEWORK_DEBUG
    if (IS_PARAM_ZERO(len) || IS_PTR_NULL(buf) || IS_PTR_NULL(key) || IS_PARAM_ZERO(rounds) || (len & 3))
    {
        return ;
    }
#endif

	/* Coding Part */
    n = len >> 2;
    z = buf[n - 1];
    y = buf[0];
    
	q = rounds + 52 / n;

	while(q--)
	{
		sum += XXTEA_DELTA;

		e = (sum >> 2) & 3;

		for (p = 0; p < n - 1; p++)
		{
			y = buf[p + 1];

			buf[p] += XXTEA_MX;
			z = buf[p];
		}

		y = buf[0];

		buf[n - 1] += XXTEA_MX;
		z = buf[n - 1];
	}
}

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
__INLINE
void xxTea_Data_Decrypt(uint32_t *buf, uint16_t len, uint32_t *key, uint32_t rounds)
{
	uint32_t p, q;
	uint32_t e, sum;
	uint32_t n;
	uint32_t z, y;

#ifdef ENABLE_FRAMEWORK_DEBUG
    if (IS_PARAM_ZERO(len) || IS_PTR_NULL(buf) || IS_PTR_NULL(key) || IS_PARAM_ZERO(rounds) || (len & 3))
    {
        return ;
    }
#endif
    
	/* Decoding Part */
    n = len >> 2;
    z = buf[n - 1];
    y = buf[0];
    
	q = rounds + 52 / n;

	sum = q * XXTEA_DELTA;

	while (sum != 0)
	{
		e = (sum >> 2) & 3;

		for (p = n - 1; p > 0; p--)
		{
			z = buf[p - 1];

			buf[p] -= XXTEA_MX;
			y = buf[p];
		}

		z = buf[n - 1];
		buf[0] -= XXTEA_MX;
		y = buf[0];

		sum -= XXTEA_DELTA;
	}
}

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
__INLINE
void xxTea_Init(xxTea_Handle_t *handle, uint16_t *key, uint32_t rounds)
{
    memset(handle, 0, sizeof(xxTea_Handle_t));
    
    memcpy(&handle->Key[0], &key[0], sizeof(handle->Key));
    
    handle->Rounds = rounds;
}

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
__INLINE
void xxTea_Encrypt(xxTea_Handle_t *handle, uint32_t *buf, uint16_t len)
{
#ifdef ENABLE_FRAMEWORK_DEBUG
    if (IS_PTR_NULL(handle))
    {
        return ;
    }
#endif
    
	xxTea_Data_Encrypt(buf, len, (uint32_t *)&handle->Key[0], handle->Rounds);
}

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
__INLINE
void xxTea_Decrypt(xxTea_Handle_t *handle, uint32_t *buf, uint16_t len)
{
#ifdef ENABLE_FRAMEWORK_DEBUG
    if (IS_PTR_NULL(handle))
    {
        return ;
    }
#endif
    
	xxTea_Data_Decrypt(buf, len, (uint32_t *)&handle->Key[0], handle->Rounds);
}

/** @}*/     /** xxtea encryption component */

/**********************************END OF FILE*********************************/
