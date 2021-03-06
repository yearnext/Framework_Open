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
 * @file       hal_pin.h                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-06-28                                                      *
 * @brief      hal gpio driver component head file                             *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2018-06-28 从“hal_device.h”分离出GPIO驱动                                *
 * 2. 2018-07-29 修改文件名“hal_gpio.h”为“hal_pin.h”                           *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DRIVER_PIN_H__
#define __HAL_DRIVER_PIN_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal_def.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL GPIO PORT
 *******************************************************************************
 */
typedef struct
{
    uint16_t Pin;
    uint16_t Port;
    uint16_t Mode;
    uint16_t Flag;
}HAL_Port_t;

typedef struct
{
    void (*Init)(HAL_Device_t *dev, uint32_t pin, uint16_t mode);
    void (*Write)(HAL_Device_t *dev, uint32_t pin, uint32_t value);
    void (*Toggle)(HAL_Device_t *dev, uint32_t pin);
    uint32_t (*Read)(HAL_Device_t *dev, uint32_t pin);
}HAL_Port_Interface_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief      GPIO COMPONENT API FOR HAL LIBRARY
 *******************************************************************************
 */
extern void     HAL_Pin_Register(HAL_Port_Interface_t *ops, void *userData);

extern void     HAL_Pin_Init(uint32_t pin, uint16_t mode);
extern void     HAL_Pin_Input(uint32_t pin);
extern void     HAL_Pin_Output(uint32_t pin);

extern void     HAL_Pin_Set(uint32_t pin);
extern void     HAL_Pin_Clr(uint32_t pin);
extern void     HAL_Pin_Toggle(uint32_t pin);
extern uint32_t HAL_Pin_Get(uint32_t pin);

extern void     HAL_Port_Init(uint32_t port, uint32_t pos, uint32_t len, uint32_t mode);
extern void     HAL_Port_Write(uint32_t port, uint32_t pos, uint32_t len, uint32_t wr);
extern void     HAL_Port_Xor(uint32_t port, uint32_t pos, uint32_t len, uint32_t wr);
extern uint32_t HAL_Port_Read(uint32_t port, uint32_t pos, uint32_t len);
extern void     HAL_Port_Get(uint32_t port, uint32_t pos, uint32_t len);
    
/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
