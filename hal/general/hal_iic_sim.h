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
 * @file       hal_iic_sim.h                                                   *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-10-31                                                      *
 * @brief      hal iic simulation driver component head file                   *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1. 2018-06-28 从“hal_device.h”分离出IIC驱动                                 *
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_DRIVER_IIC_SIMULATION_H__
#define __HAL_DRIVER_IIC_SIMULATION_H__

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct 
{
    void *Handle;
	
	void (*SDA)(void *handle, uint8_t state);
	void (*SCL)(void *handle, uint8_t state);
	
	uint8_t (*GetSDA)(void *handle);
	uint8_t (*GetSCL)(void *handle);
	
	void (*Delay)(uint32_t us);
	uint8_t (*Wait)(uint32_t us);
	
    uint32_t DelayTick;  /* scl and sda line delay */
    uint32_t Timeout;    /* in tick */
}HAL_IIC_SimDevice_t;

/* Exported constants --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/* Add c++ compatibility------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif      /** prevent recursive inclusion */

/**********************************END OF FILE*********************************/
