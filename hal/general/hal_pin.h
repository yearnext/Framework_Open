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
/**
 *******************************************************************************
 * @brief        HAL GPIO PORT ID Conversion
 *******************************************************************************
 */
#define HAL_PIN_ID(port, pin)                             ((port) << 16 | (pin))
#define HAL_PORT(id)                                                ((id) >> 16)
#define HAL_PIN(id)                                        ((id) & 0x0000FFFFUL)

//! 定义引脚状态
#define HAL_PIN_INIT                                                        0x00
#define HAL_PIN_ACTIVE                                                      0x01
#define HAL_PIN_INACTIVE                                                    0x02

//! 定义引脚配置参数
#define HAL_PIN_ACTIVE_HIGH                                                 0x01
#define HAL_PIN_ACTIVE_LOW                                                  0x00
#define HAL_PIN_IS_HIGH_ACTIVE(x)        (Fw_Flag_Get((x), HAL_PIN_ACTIVE_HIGH))

/* Exported types ------------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL GPIO PORT
 *******************************************************************************
 */
enum HAL_GPIO_PORT
{
    HAL_PORT_A = 0,
    HAL_PORT_B,
    HAL_PORT_C,
    HAL_PORT_D,
    HAL_PORT_E,
    HAL_PORT_F,
    HAL_PORT_G,
    HAL_PORT_H,
    HAL_PORT_I,
    HAL_PORT_J,
    HAL_PORT_K,
    HAL_PORT_L,
    HAL_PORT_M,
    HAL_PORT_N,
                            
    HAL_PORT_MAX,
};

enum HAL_GPIO_PIN
{
    HAL_PIN_0 = 0,
    HAL_PIN_1,
    HAL_PIN_2,
    HAL_PIN_3,
    HAL_PIN_4,
    HAL_PIN_5,
    HAL_PIN_6,
    HAL_PIN_7,
    HAL_PIN_8,
    HAL_PIN_9,
    HAL_PIN_10,
    HAL_PIN_11,
    HAL_PIN_12,
    HAL_PIN_13,
    HAL_PIN_14,
    HAL_PIN_15,
    HAL_PIN_16,
    HAL_PIN_17,
    HAL_PIN_18,
    HAL_PIN_19,
    HAL_PIN_20,
    HAL_PIN_21,    
    HAL_PIN_22,
    HAL_PIN_23,
    HAL_PIN_24,
    HAL_PIN_25,
    HAL_PIN_26,
    HAL_PIN_27,   
    HAL_PIN_28,
    HAL_PIN_29,
    HAL_PIN_30,
    HAL_PIN_31,

    HAL_PIN_MAX,
};

enum HAL_PIN_MODE
{
    HAL_PIN_INPUT = 0,
    HAL_PIN_OUTPUT,
    HAL_PIN_FLOAT,
    HAL_PIN_QUASI,
    HAL_PIN_ANALOG,

    HAL_PIN_MODE_MAX,
};

enum HAL_PORT_CMD
{
    GPIO_SET_CMD = HAL_SPECIAL_CMD,
    GPIO_CLR_CMD,
    GPIO_TOGGLE_CMD,
    GPIO_INPUT_MODE_CMD,
    GPIO_OUTPUT_MODE_CMD,
    GPIO_GET_OUTPUT_CMD,
    GPIO_GET_INPUT_CMD,
};

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
