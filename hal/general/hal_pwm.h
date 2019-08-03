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
 * @file       hal_pwm.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-06-28                                                      *
 * @brief      hal pwm driver component head file                              *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2018-06-28 从“hal_device.h”分离出PWM驱动                                 *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DRIVER_PWM_H__
#define __HAL_DRIVER_PWM_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal_def.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
{
    struct
    {
        uint32_t Period;
        uint32_t InitDuty;
        
        uint32_t Port;
    }Attribute;
    
    struct
    {
        uint8_t Dir : 1;
    }Flag;
}HAL_PWM_Config_t;

typedef struct
{
    HAL_Atrribute_t Attribute;
    
    uint32_t Period;
    uint32_t Duty;
    
    //! 底层设备句柄
    void *Param;
}HAL_PWM_t;

typedef struct
{
    uint32_t (*Config)(HAL_Device_t *dev, uint32_t ch, uint32_t period, uint32_t duty);
    
    void     (*Open)(HAL_Device_t *dev, uint32_t ch);
    void     (*Close)(HAL_Device_t *dev, uint32_t ch);
    
    void     (*SetPeriod)(HAL_Device_t *dev, uint32_t ch, uint32_t period);
    uint32_t (*GetPeriod)(HAL_Device_t *dev, uint32_t ch);
    void     (*SetDuty)(HAL_Device_t *dev, uint32_t ch, uint32_t duty);
    uint32_t (*GetDuty)(HAL_Device_t *dev, uint32_t ch);

    uint32_t (*Control)(HAL_Device_t *dev, uint32_t ch, uint32_t cmd, void *arg);
}HAL_PWM_Interface_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
extern void HAL_PWM_Register(HAL_PWM_Interface_t *ops, void *userData);

extern void     HAL_PWM_Init(uint32_t ch, uint32_t period, uint32_t duty);
extern void     HAL_PWM_Open(uint32_t ch);
extern void     HAL_PWM_Close(uint32_t ch);
extern uint32_t HAL_PWM_GetDuty(uint32_t ch);
extern void     HAL_PWM_SetDuty(uint32_t ch, uint32_t duty);
extern uint32_t HAL_PWM_GetPeriod(uint32_t ch);
extern void     HAL_PWM_SetPeriod(uint32_t ch, uint32_t period);
extern void     HAL_PWM_SetNeg(uint32_t ch);
extern void     HAL_PWM_SetNormal(uint32_t ch);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
