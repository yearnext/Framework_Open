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
 * @file       hal_device.h                                                    *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-08-28                                                      *
 * @brief      hal device component                                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 20170828    创建文件"hal_device.h"                                       *
 * 2. 20180127    修改HAL层架构                                                *
 *******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DEVICE_H__
#define __HAL_DEVICE_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal_def.h"

/**
 *******************************************************************************
 * @brief        HAL通用设备操作接口
 *******************************************************************************
 */
#include "general/hal_pin.h"
#include "general/hal_key.h"
#include "general/hal_timer.h"
#include "general/hal_pwm.h"
#include "general/hal_adc.h"
#include "general/hal_serial.h"
#include "general/hal_spi.h"
#include "general/hal_iic.h"
#include "general/hal_flash.h"
#include "general/hal_veeprom.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 *******************************************************************************
 * @brief        HAL原子操作API
 *******************************************************************************
 */
extern void HAL_Atom_Begin(void);
extern void HAL_Atom_End(void);

/**
 *******************************************************************************
 * @brief        HAL设备组件操作API
 *******************************************************************************
 */
//! 初始化HAL层驱动
extern int HAL_Component_Init(void);

//! 注册设备
extern uint16_t HAL_Device_Register(HAL_Device_t *dev, char *name, HAL_Interface_t *ops, uint32_t flag);
//! 注销设备
extern uint16_t HAL_Device_Unregister(HAL_Device_t *dev);
//! 查找设备
extern HAL_Device_t *HAL_Device_Find(uint16_t type);

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
