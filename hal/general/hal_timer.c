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
 * @file       hal_timer.c                                                     *
 * @author     Accumulate Team                                                 *
 * @version    1.0.0                                                           *
 * @date       2017-08-16                                                      *
 * @brief      hal timer driver component source file                          *
 * @par        work platform                                                   *
 *                 Windows                                                     *
 * @par        compiler                                                        *
 *                 GCC                                                         *
 *******************************************************************************
 * @note                                                                       *
 * 1.20170816    创建文件                                                      *
 *******************************************************************************
 */
 
/**
* @defgroup hal timer driver component
* @{
*/

/* Includes ------------------------------------------------------------------*/
#include "hal_device.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#ifdef ENABLE_HAL_TIMER_DRIVER
struct HAL_DRIVER_TIMER
{
    HAL_Device_t          Parent;
    HAL_Timer_Interface_t Ops;
}DeviceTimer;
#endif

/* Exported variables --------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
#ifdef ENABLE_HAL_TIMER_DRIVER
void HAL_Timer_Register(HAL_Timer_Interface_t *ops, void *userData)
{
    HAL_Interface_t halDevOps;
    
    memset(&DeviceTimer, 0, sizeof(DeviceTimer));

    halDevOps.Close   = NULL;
    halDevOps.Control = NULL;
    halDevOps.Fini    = NULL;
    halDevOps.Init    = NULL;
    halDevOps.Open    = NULL;
    halDevOps.Read    = NULL;
    halDevOps.Write   = NULL;

    DeviceTimer.Ops.Config      = ops->Config;
    DeviceTimer.Ops.Control     = ops->Control;
    DeviceTimer.Ops.GetCount    = ops->GetCount;
    DeviceTimer.Ops.Start       = ops->Start;
    DeviceTimer.Ops.Stop        = ops->Stop;

    DeviceTimer.Parent.UserData = userData;
    
    HAL_Device_Register(&DeviceTimer.Parent, HAL_TIMER_STR, &halDevOps, HAL_Flag_Encode(HAL_DEVICE_TIMER, HAL_READ_FLAG | HAL_WRITE_FLAG));
}

void HAL_Timer_Init(HAL_Timer_t *timer, HAL_Timer_Config_t *config)
{
    memset(timer, 0, sizeof(HAL_Timer_t));
    
    Timer_Callback callback = {.Callback = config->Callback, .Param = (void *)config->Param};
    
    //! 设置端口信息
    timer->Attribute.Flag  = *((uint16_t *)&config->Flag);
    timer->Attribute.Port  = config->Attribute.Port;
    timer->Attribute.State = 0;
    timer->Attribute.Event = 0;

    timer->Tick            = config->Attribute.Tick;

    timer->Dev             = &DeviceTimer.Parent;
    
    //! 初始化设备
    if (!IS_PTR_NULL(DeviceTimer.Ops.Config))
    {
        DeviceTimer.Ops.Config(timer, config);
    }
    
    if (!IS_PTR_NULL(DeviceTimer.Ops.Control))
    {
        DeviceTimer.Ops.Control(timer, HAL_SET_CALLBACK_CMD, (void *)&callback);
    }
    
//    HAL_Timer_Start(timer);
}

void HAL_Timer_Start(HAL_Timer_t *timer)
{
    if (!IS_PTR_NULL(DeviceTimer.Ops.Start))
    {
        DeviceTimer.Ops.Start(timer);
    }
}

void HAL_Timer_Stop(HAL_Timer_t *timer)
{
    if (!IS_PTR_NULL(DeviceTimer.Ops.Stop))
    {
        DeviceTimer.Ops.Stop(timer);
    }
}

uint32_t HAL_Timer_GetCount(HAL_Timer_t *timer)
{
    if (!IS_PTR_NULL(DeviceTimer.Ops.GetCount))
    {
        return DeviceTimer.Ops.GetCount(timer);
    }
    
    return 0;
}
#endif

/** @}*/     /** hal timer driver component */

/**********************************END OF FILE*********************************/
