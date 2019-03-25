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
 * @file       hal_pwm.c                                                       *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2018-08-23                                                      *
 * @brief      hal pwm driver component source file                            *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20180823    创建文件                                                      *
 *******************************************************************************
 */
 
/**
* @defgroup hal pwm driver component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef ENABLE_HAL_PWM_DRIVER
struct
{
    HAL_Device_t        Parent;
    
    HAL_PWM_Interface_t Ops;
}DevicePWM;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef ENABLE_HAL_PWM_DRIVER
void HAL_PWM_Register(HAL_PWM_Interface_t *ops, void *userData)
{
    HAL_Interface_t halDevOps;
    
    memset(&DevicePWM, 0, sizeof(DevicePWM));

    halDevOps.Close   = NULL;
    halDevOps.Control = NULL;
    halDevOps.Fini    = NULL;
    halDevOps.Init    = NULL;
    halDevOps.Open    = NULL;
    halDevOps.Read    = NULL;
    halDevOps.Write   = NULL;

    DevicePWM.Ops.Config         = ops->Config;
    DevicePWM.Ops.Control        = ops->Control;
    DevicePWM.Ops.Open           = ops->Open;
    DevicePWM.Ops.Close          = ops->Close;
    DevicePWM.Ops.GetPeriod      = ops->GetPeriod;
    DevicePWM.Ops.SetPeriod      = ops->SetPeriod;
    DevicePWM.Ops.GetDuty        = ops->GetDuty;
    DevicePWM.Ops.SetDuty        = ops->SetDuty;
    
    DevicePWM.Parent.UserData    = userData;
    
    HAL_Device_Register(&DevicePWM.Parent, HAL_PWM_STR, &halDevOps, HAL_Flag_Encode(HAL_DEVICE_PWM, HAL_READ_FLAG | HAL_WRITE_FLAG));
}

void HAL_PWM_Init(uint32_t ch, uint32_t period, uint32_t duty)
{
    if (!IS_PTR_NULL(DevicePWM.Ops.Config))
    {
        DevicePWM.Ops.Config(NULL, ch, period, duty);
    }
}

void HAL_PWM_Open(uint32_t ch)
{
    if (!IS_PTR_NULL(DevicePWM.Ops.Open))
    {
        DevicePWM.Ops.Open(NULL, ch);
    }
}

void HAL_PWM_Close(uint32_t ch)
{
    if (!IS_PTR_NULL(DevicePWM.Ops.Close))
    {
        DevicePWM.Ops.Close(NULL, ch);
    }
}

uint32_t HAL_PWM_GetDuty(uint32_t ch)
{
    if (!IS_PTR_NULL(DevicePWM.Ops.GetDuty))
    {
        return DevicePWM.Ops.GetDuty(NULL, ch);
    }
    
    return 0;
}

void HAL_PWM_SetDuty(uint32_t ch, uint32_t duty)
{
    if (!IS_PTR_NULL(DevicePWM.Ops.SetDuty))
    {
        DevicePWM.Ops.SetDuty(NULL, ch, duty);
    }
}

uint32_t HAL_PWM_GetPeriod(uint32_t ch)
{
    if (!IS_PTR_NULL(DevicePWM.Ops.GetDuty))
    {
        return DevicePWM.Ops.GetDuty(NULL, ch);
    }
    
    return 0;
}

void HAL_PWM_SetPeriod(uint32_t ch, uint32_t period)
{
    if (!IS_PTR_NULL(DevicePWM.Ops.SetPeriod))
    {
        DevicePWM.Ops.SetPeriod(NULL, ch, period);
    }
}

void HAL_PWM_SetNeg(uint32_t ch)
{
    if (!IS_PTR_NULL(DevicePWM.Ops.Control))
    {
        DevicePWM.Ops.Control(NULL, ch, HAL_PWM_CHANNEL_NEGATION, NULL);
    }
}

void HAL_PWM_SetNormal(uint32_t ch)
{
    if (!IS_PTR_NULL(DevicePWM.Ops.Control))
    {
        DevicePWM.Ops.Control(NULL, ch, HAL_PWM_CHANNEL_NORMAL, NULL);
    }
}

#endif

/** @}*/     /** hal pwm driver component */

/**********************************END OF FILE*********************************/
