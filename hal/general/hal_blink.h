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
 * @file       hal_blink.h                                                     *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-01-16                                                      *
 * @brief      blink driver component                                          *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.2018-01-16 创建文件，增加LED闪烁功能                                      *
 * 1.2018-06-28 修改文件名为“hal_blink.c”，整合框架，统一HAL层                 *
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_BLINK_H__
#define __HAL_BLINK_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif


/* Includes ------------------------------------------------------------------*/
#include "hal_def.h"

/* Exported macro ------------------------------------------------------------*/    
/* Exported types ------------------------------------------------------------*/
typedef int (__CODE* HALBlinkCallback)(void *handle, uint8_t cmd);

typedef struct HAL_BLINK
{
    //! 定时器句柄
    HalDevTim_t Timer;
    
    //! 设置回调函数
    HALBlinkCallback Callback;
    
    //! 回调参数
    void *Param;
    
    //! 设备名称
    char *Name;
    
    //! 当前状态
    uint8_t State;
    //! 闪烁次数
    int16_t Count;
    //! 闪烁超时时间
    uint16_t Timeout;
}HAL_Blink_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern void HAL_Blink_Init(HAL_Blink_t *blink, char *name, HALBlinkCallback callback, void *param);
extern void HAL_Blink_On(HAL_Blink_t *blink);
extern void HAL_Blink_Off(HAL_Blink_t *blink);
extern void HAL_Blink_Control(HAL_Blink_t *blink, int16_t count, uint16_t tick);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
