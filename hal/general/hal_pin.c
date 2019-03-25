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
 * @file       hal_pin.c                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-07-29                                                      *
 * @brief      hal port component source file                                  *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.XXXXX                                                                     *
 *******************************************************************************
 */
 
/**
* @defgroup hal port component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
#ifdef ENABLE_HAL_GPIO_DRIVER
struct
{
    HAL_Device_t         Parent;
    
    HAL_Port_Interface_t Ops;
}DevicePin;
#endif

/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef ENABLE_HAL_GPIO_DRIVER
void HAL_Pin_Register(HAL_Port_Interface_t *ops, void *userData)
{
    memset(&DevicePin, 0, sizeof(DevicePin));

    DevicePin.Ops.Init   = ops->Init;
    DevicePin.Ops.Read   = ops->Read;
    DevicePin.Ops.Write  = ops->Write;
    DevicePin.Ops.Toggle = ops->Toggle;
    
#ifdef ENABLE_HAL_DRIVER_COMPONENT
    HAL_Interface_t halDevOps;
    
    halDevOps.Control    = NULL;
    halDevOps.Fini       = NULL;
    halDevOps.Init       = NULL;
    halDevOps.Read       = NULL;
    halDevOps.Write      = NULL;
    halDevOps.Open       = NULL;
    halDevOps.Close      = NULL;
    
    HAL_Device_Register(&DevicePin.Parent, HAL_PIN_STR, &halDevOps, HAL_Flag_Encode(HAL_DEVICE_PIN, HAL_READ_FLAG | HAL_WRITE_FLAG));
#endif
}

void HAL_Pin_Init(uint32_t pin, uint16_t mode)
{
    if (!IS_PTR_NULL(DevicePin.Ops.Init))
    {
        DevicePin.Ops.Init(NULL, pin, mode);
    }
}

void HAL_Pin_Input(uint32_t pin)
{
    if (!IS_PTR_NULL(DevicePin.Ops.Init))
    {
        DevicePin.Ops.Init(NULL, pin, HAL_PIN_INPUT);
    }
}

void HAL_Pin_Output(uint32_t pin)
{
    if (!IS_PTR_NULL(DevicePin.Ops.Init))
    {
        DevicePin.Ops.Init(NULL, pin, HAL_PIN_OUTPUT);
    }
}

void HAL_Pin_Set(uint32_t pin)
{
    if (!IS_PTR_NULL(DevicePin.Ops.Write))
    {
        DevicePin.Ops.Write(NULL, pin, 1);
    }
}

void HAL_Pin_Clr(uint32_t pin)
{
    if (!IS_PTR_NULL(DevicePin.Ops.Write))
    {
        DevicePin.Ops.Write(NULL, pin, 0);
    }
}

void HAL_Pin_Toggle(uint32_t pin)
{
    if (!IS_PTR_NULL(DevicePin.Ops.Toggle))
    {
        DevicePin.Ops.Toggle(NULL, pin);
    }
}

uint32_t HAL_Pin_Get(uint32_t pin)
{
    if (!IS_PTR_NULL(DevicePin.Ops.Read))
    {
        if (DevicePin.Ops.Read(NULL, pin))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    return 0;
}

void HAL_Port_Init(uint32_t port, uint32_t pos, uint32_t len, uint32_t mode)
{
    //! todo: wait complete
}

void HAL_Port_Write(uint32_t port, uint32_t pos, uint32_t len, uint32_t wr)
{
    //! todo: wait complete
}

void HAL_Port_Xor(uint32_t port, uint32_t pos, uint32_t len, uint32_t wr)
{
    //! todo: wait complete
}

void HAL_Port_Toggle(uint32_t port, uint32_t pos, uint32_t len)
{
    //! todo: wait complete
}

uint32_t HAL_Port_Read(uint32_t port, uint32_t pos, uint32_t len)
{
    //! todo: wait complete
    
    return 0;
}

void HAL_Port_Get(uint32_t port, uint32_t pos, uint32_t len)
{
    //! todo: wait complete
}

#endif

/** @}*/     /** hal port component */

/**********************************END OF FILE*********************************/
